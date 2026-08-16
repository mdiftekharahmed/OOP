/*
 * ============================================================================
 *  LEVEL 2 : STRONG GUARANTEE  ("Commit-or-Rollback")
 * ============================================================================
 *  If an operation throws, the object is left EXACTLY as it was before the
 *  operation started -- as if the call had never happened at all.
 *
 *  The classic technique for achieving this is the COPY-AND-SWAP IDIOM:
 *      1. Build the new state completely in a temporary / local object.
 *         If building it throws, the original object was never touched.
 *      2. Only once step 1 has fully succeeded, swap the new state into
 *         place using a non-throwing swap().
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <utility>

// ----------------------------------------------------------------------------
// A helper that simulates an allocation/copy failure at a chosen point,
// e.g. representing std::bad_alloc, a corrupt source, disk failure, etc.
// ----------------------------------------------------------------------------
int* copy_ints(const int* src, std::size_t n, bool simulateFailure) {
    if (simulateFailure) {
        throw std::runtime_error("Simulated failure while copying buffer contents");
    }
    int* dst = new int[n];
    std::copy(src, src + n, dst);
    return dst;
}

// ----------------------------------------------------------------------------
// StrongBuffer: owns a dynamically allocated int array and offers the
// Strong Guarantee on assignment via copy-and-swap.
// ----------------------------------------------------------------------------
class StrongBuffer {
    int* data;
    std::size_t size;
    bool failNextCopy; // test hook: forces the NEXT copy made from this
                        // object to simulate failure (used to demo rollback)
public:
    StrongBuffer(std::size_t n, int fillValue)
        : data(new int[n]), size(n), failNextCopy(false) {
        std::fill(data, data + n, fillValue);
    }

    // Copy constructor: either fully succeeds, or leaves *this untouched
    // (it isn't even alive yet if this throws -- standard C++ semantics).
    StrongBuffer(const StrongBuffer& other)
        : data(copy_ints(other.data, other.size, other.failNextCopy)),
          size(other.size),
          failNextCopy(false) {}

    ~StrongBuffer() { delete[] data; }

    // Non-throwing swap: just exchanges pointers/POD members.
    void swap(StrongBuffer& other) noexcept {
        std::swap(data, other.data);
        std::swap(size, other.size);
    }

    // COPY-AND-SWAP assignment operator -> Strong Guarantee.
    // `other` is taken BY VALUE, so the copy constructor already ran (and
    // could already have thrown) BEFORE we touch *this* at all.
    StrongBuffer& operator=(StrongBuffer other) {
        std::cout << "  [operator=] temporary copy built successfully; committing via swap()\n";
        swap(other);                 // no-throw: commit point
        return *this;
        // `other` (holding our OLD data) is destroyed here, cleanly freeing
        // the old buffer -- no leak, no manual delete needed.
    }

    void setFailNextCopy(bool v) { failNextCopy = v; }

    void print(const char* label) const {
        std::cout << "  " << label << ": [";
        for (std::size_t i = 0; i < size; ++i) std::cout << data[i] << (i + 1 < size ? ", " : "");
        std::cout << "]  (size=" << size << ", address=" << static_cast<const void*>(data) << ")\n";
    }
};

int main() {
    std::cout << "=== LEVEL 2: STRONG GUARANTEE (copy-and-swap) ===\n\n";

    StrongBuffer original(3, 7);     // {7, 7, 7}
    StrongBuffer replacement(5, 42); // {42, 42, 42, 42, 42}

    original.print("original (before)");
    replacement.print("replacement");

    std::cout << "\n--- Attempt 1: assignment that FAILS mid-copy ---\n";
    replacement.setFailNextCopy(true); // force the copy ctor inside operator= to throw
    try {
        original = replacement;   // operator=(StrongBuffer other) -- copy happens on entry
        std::cout << "  (unreachable: assignment should have thrown)\n";
    } catch (const std::exception& e) {
        std::cout << "  Caught exception: " << e.what() << "\n";
    }

    std::cout << "\nAfter the FAILED assignment:\n";
    original.print("original (unchanged!)");
    std::cout << "  >>> STRONG GUARANTEE CONFIRMED: 'original' still holds {7, 7, 7},\n"
              << "      exactly as it did before the failed assignment was attempted.\n";

    std::cout << "\n--- Attempt 2: assignment that SUCCEEDS ---\n";
    replacement.setFailNextCopy(false);
    original = replacement;
    original.print("original (after successful assignment)");
    std::cout << "  >>> Commit succeeded: 'original' now equals 'replacement'.\n";

    std::cout << "\nLesson: by building the new state in a temporary first and only\n"
              << "swapping it in with a noexcept swap(), operator= is either fully\n"
              << "applied or has no effect at all -- true commit-or-rollback semantics.\n";
    return 0;
}
