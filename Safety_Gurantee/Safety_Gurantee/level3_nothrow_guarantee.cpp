/*
 * ============================================================================
 *  LEVEL 3 : NOTHROW / NO-FAIL GUARANTEE  (noexcept)
 * ============================================================================
 *  The operation is GUARANTEED to never throw at all -- it always succeeds.
 *  Typically applies to: destructors, swap(), move constructors/assignment,
 *  and simple getters.
 *
 *  This demo shows TWO practical payoffs of marking operations noexcept:
 *
 *   (A) std::vector<T> only uses T's move constructor during reallocation
 *       if that move constructor is noexcept (via std::move_if_noexcept).
 *       Otherwise it falls back to the (safe but expensive) COPY
 *       constructor, to preserve the vector's own strong guarantee.
 *       We compare a THROWING-move type vs a NOEXCEPT-move type.
 *
 *   (B) A destructor that throws during stack unwinding causes
 *       std::terminate() -- which is why destructors must never throw.
 *       (Demonstrated via explanation + a compile-time static_assert,
 *       since actually invoking it would abort the whole program.)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>

// ----------------------------------------------------------------------------
// (A1) A resource-owning type whose move constructor is allowed to throw
//      (not marked noexcept). std::vector cannot safely move these during
//      reallocation, so it will COPY them instead.
// ----------------------------------------------------------------------------
class ThrowingMoveResource {
    int* data;
    int id;
public:
    explicit ThrowingMoveResource(int value) : data(new int(value)), id(value) {
        std::cout << "    construct #" << id << "\n";
    }
    ThrowingMoveResource(const ThrowingMoveResource& other)
        : data(new int(*other.data)), id(other.id) {
        std::cout << "    COPY #" << id << "   <-- expensive deep copy\n";
    }
    // Deliberately NOT noexcept (even though this particular implementation
    // happens not to throw) -- the compiler cannot assume it's safe, so
    // std::vector treats it as a possibly-throwing move.
    ThrowingMoveResource(ThrowingMoveResource&& other) : data(other.data), id(other.id) {
        std::cout << "    move #" << id << "   (but NOT marked noexcept)\n";
        other.data = nullptr;
    }
    ~ThrowingMoveResource() { delete data; }
};

// ----------------------------------------------------------------------------
// (A2) A resource-owning type whose move constructor IS noexcept.
//      std::vector can safely move these during reallocation.
// ----------------------------------------------------------------------------
class NothrowMoveResource {
    int* data;
    int id;
public:
    explicit NothrowMoveResource(int value) : data(new int(value)), id(value) {
        std::cout << "    construct #" << id << "\n";
    }
    NothrowMoveResource(const NothrowMoveResource& other)
        : data(new int(*other.data)), id(other.id) {
        std::cout << "    COPY #" << id << "   <-- expensive deep copy\n";
    }
    // noexcept: promises this move can NEVER throw. Enables std::vector
    // (and other standard containers/algorithms) to use it safely.
    NothrowMoveResource(NothrowMoveResource&& other) noexcept : data(other.data), id(other.id) {
        std::cout << "    MOVE #" << id << "   <-- cheap pointer steal, noexcept\n";
        other.data = nullptr;
    }
    NothrowMoveResource& operator=(NothrowMoveResource&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            id = other.id;
            other.data = nullptr;
        }
        return *this;
    }
    void swap(NothrowMoveResource& other) noexcept {
        std::swap(data, other.data);
        std::swap(id, other.id);
    }
    ~NothrowMoveResource() { delete data; }
};

// Compile-time proof of the guarantee: these assertions would fail to
// compile if the promises above were broken.
static_assert(!std::is_nothrow_move_constructible<ThrowingMoveResource>::value,
              "ThrowingMoveResource's move ctor is (deliberately) not noexcept");
static_assert(std::is_nothrow_move_constructible<NothrowMoveResource>::value,
              "NothrowMoveResource's move ctor must be noexcept");
static_assert(std::is_nothrow_swappable<NothrowMoveResource>::value,
              "NothrowMoveResource::swap must be noexcept");

template <typename T>
void demoVectorGrowth(const char* label) {
    std::cout << "--- " << label << " ---\n";
    std::vector<T> v;
    v.reserve(1); // start tiny so we are guaranteed to see at least one growth/reallocation
    std::cout << "  constructing 4 elements (will force a reallocation):\n";
    for (int i = 1; i <= 4; ++i) {
        std::cout << "  push_back(" << i << "):\n";
        v.emplace_back(i);
    }
    std::cout << "\n";
}

int main() {
    std::cout << "=== LEVEL 3: NOTHROW / NO-FAIL GUARANTEE (noexcept) ===\n\n";

    std::cout << "is_nothrow_move_constructible<ThrowingMoveResource> = "
              << std::boolalpha << std::is_nothrow_move_constructible<ThrowingMoveResource>::value << "\n";
    std::cout << "is_nothrow_move_constructible<NothrowMoveResource>  = "
              << std::boolalpha << std::is_nothrow_move_constructible<NothrowMoveResource>::value << "\n\n";

    demoVectorGrowth<ThrowingMoveResource>("Type WITHOUT noexcept move -> vector falls back to COPY");
    demoVectorGrowth<NothrowMoveResource>("Type WITH noexcept move -> vector safely uses MOVE");

    std::cout << "Notice: for ThrowingMoveResource, growth reallocation triggered COPY\n"
              << "operations (expensive, allocates new memory for every element). For\n"
              << "NothrowMoveResource, growth triggered cheap MOVE operations instead,\n"
              << "because std::vector can only rely on a move that is guaranteed never\n"
              << "to throw (otherwise a failed move mid-reallocation could leave the\n"
              << "vector's own strong guarantee broken).\n\n";

    std::cout << "Reminder (not demonstrated live, since it would abort the process):\n"
              << "  A destructor that throws WHILE another exception is already\n"
              << "  propagating (stack unwinding) causes std::terminate() to be called\n"
              << "  immediately. This is why destructors, swap(), and move operations\n"
              << "  are expected to satisfy the No-throw Guarantee and are marked\n"
              << "  'noexcept' whenever possible.\n";

    return 0;
}
