/*
 * ============================================================================
 *  LEVEL 0 : NO GUARANTEE  (Nothrow Violation / Leak Hazard)
 * ============================================================================
 *  If an operation throws, the object/program may be left:
 *      - with leaked resources (memory never freed)
 *      - in a corrupted / inconsistent state (dangling pointers, broken
 *        invariants such as size() no longer matching the real buffer)
 *
 *  This file overloads global operator new/delete to COUNT live allocations,
 *  so we can PROVE a leak happened by comparing counts before and after.
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <new>

// ----------------------------------------------------------------------------
// Tiny allocation tracker (global operator new/delete overloads)
// ----------------------------------------------------------------------------
static long g_liveAllocations = 0;

void* operator new(std::size_t sz) {
    void* p = std::malloc(sz);
    if (!p) throw std::bad_alloc();
    ++g_liveAllocations;
    return p;
}
void operator delete(void* p) noexcept {
    if (p) --g_liveAllocations;
    std::free(p);
}
void* operator new[](std::size_t sz) { return operator new(sz); }
void operator delete[](void* p) noexcept { operator delete(p); }

// ----------------------------------------------------------------------------
// A helper that simulates an allocation failure (e.g. out-of-memory,
// invalid input, disk full, whatever) at a chosen point.
// ----------------------------------------------------------------------------
int* allocate_ints(std::size_t n, bool simulateFailure, const char* label) {
    if (simulateFailure) {
        throw std::runtime_error(std::string("Simulated allocation failure while acquiring ") + label);
    }
    return new int[n];
}

// ----------------------------------------------------------------------------
// BAD CLASS #1: constructor leaks memory if the second allocation throws.
//
// If a constructor throws, the object is considered to have NEVER EXISTED.
// C++ guarantees the destructor of an object that failed to fully construct
// is NEVER called. Any resource already acquired in the constructor body
// (as opposed to a member sub-object with its own destructor) is therefore
// LEAKED unless the constructor cleans up after itself manually.
// ----------------------------------------------------------------------------
class LeakyOnConstruct {
    int* dataA;   // acquired first  -> will leak if dataB's allocation throws
    int* dataB;   // acquired second -> the one that throws
    std::size_t n;
public:
    LeakyOnConstruct(std::size_t count, bool failSecondAllocation) : n(count) {
        std::cout << "  [ctor] acquiring dataA...\n";
        dataA = allocate_ints(n, false, "dataA");           // succeeds

        std::cout << "  [ctor] acquiring dataB...\n";
        dataB = allocate_ints(n, failSecondAllocation, "dataB"); // may throw
        // If we get here, both succeeded.
    }
    ~LeakyOnConstruct() {
        std::cout << "  [dtor] releasing dataA and dataB\n";
        delete[] dataA;
        delete[] dataB;
    }
};

// ----------------------------------------------------------------------------
// BAD CLASS #2: assignment operator corrupts object state on failure.
//
// Old resource is destroyed BEFORE the new one is safely acquired. If the
// new acquisition throws, the object is left with a dangling/null pointer
// while `size` may still claim the old (or new) length -- the invariant
// "size matches allocated buffer" is broken. This is the classic
// "delete-then-throw" anti-pattern.
// ----------------------------------------------------------------------------
class CorruptibleBuffer {
    int* data;
    std::size_t size;
public:
    CorruptibleBuffer(std::size_t n) : data(new int[n]), size(n) {
        for (std::size_t i = 0; i < n; ++i) data[i] = static_cast<int>(i);
    }
    ~CorruptibleBuffer() { delete[] data; }

    // NOT exception safe: violates even the basic guarantee.
    void unsafeAssign(std::size_t newSize, bool simulateFailure) {
        delete[] data;              // (1) old resource destroyed immediately
        data = nullptr;             // object is ALREADY inconsistent here
        size = newSize;             // size updated even though buffer is gone
        data = allocate_ints(newSize, simulateFailure, "new buffer"); // (2) may throw
        for (std::size_t i = 0; i < newSize; ++i) data[i] = static_cast<int>(i * 10);
    }

    bool isCorrupted() const { return data == nullptr && size != 0; }
    std::size_t reportedSize() const { return size; }
};

int main() {
    std::cout << "=== LEVEL 0: NO GUARANTEE ===\n\n";

    // ---- Demo 1: leaked memory when a constructor throws -------------------
    std::cout << "--- Demo 1: constructor leak ---\n";
    long before = g_liveAllocations;
    try {
        LeakyOnConstruct obj(1000, /*failSecondAllocation=*/true);
        std::cout << "  (unreachable: constructor should have thrown)\n";
    } catch (const std::exception& e) {
        std::cout << "  Caught exception: " << e.what() << "\n";
    }
    long after = g_liveAllocations;
    std::cout << "  Live allocations before: " << before << ", after: " << after << "\n";
    if (after > before) {
        std::cout << "  >>> LEAK CONFIRMED: dataA was never freed ("
                  << (after - before) << " block(s) leaked)\n";
    }

    // ---- Demo 2: corrupted object state after a failed assignment ---------
    std::cout << "\n--- Demo 2: corrupted state after failed assignment ---\n";
    CorruptibleBuffer buf(5);
    std::cout << "  Buffer created, reportedSize = " << buf.reportedSize() << "\n";
    try {
        buf.unsafeAssign(10, /*simulateFailure=*/true);
    } catch (const std::exception& e) {
        std::cout << "  Caught exception: " << e.what() << "\n";
    }
    std::cout << "  After failed assign -> reportedSize = " << buf.reportedSize()
              << ", isCorrupted = " << std::boolalpha << buf.isCorrupted() << "\n";
    if (buf.isCorrupted()) {
        std::cout << "  >>> CORRUPTION CONFIRMED: size() says " << buf.reportedSize()
                  << " elements exist, but the underlying buffer is nullptr.\n"
                  << "      Any further access (e.g. buf[0]) would be undefined behavior.\n";
    }

    std::cout << "\nLesson: without any cleanup discipline, a thrown exception can both\n"
              << "leak resources and leave an object's invariants broken. This is the\n"
              << "level all real code should avoid.\n";
    return 0;
}
