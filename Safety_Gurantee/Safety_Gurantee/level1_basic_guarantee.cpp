/*
 * ============================================================================
 *  LEVEL 1 : BASIC GUARANTEE  (Minimal Standard)
 * ============================================================================
 *  If an operation throws:
 *      - NO resources are leaked
 *      - the object remains in a VALID, usable state (invariants hold)
 *      - BUT the object's contents may differ from what they were before the
 *        call started -- the operation is NOT rolled back.
 *
 *  This is weaker than the Strong Guarantee (Level 2), which additionally
 *  promises "all or nothing". Basic guarantee only promises "not broken".
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

// ----------------------------------------------------------------------------
// BasicGuaranteeContainer
//
// addAll() inserts values one at a time. If it encounters a "poison" value
// partway through the batch, it throws -- but every element added *before*
// the poison value stays committed. The container's internal invariant
// (size() == number of elements actually stored, no leaks, no dangling
// pointers) always holds, satisfying the Basic Guarantee, even though the
// batch operation was only partially applied.
// ----------------------------------------------------------------------------
class BasicGuaranteeContainer {
    std::vector<int> elements;  // RAII member: std::vector manages its own
                                 // memory, so we can never leak here even if
                                 // we throw midway through a method.
public:
    static constexpr int POISON = -999;

    std::size_t size() const { return elements.size(); }

    void print(const char* label) const {
        std::cout << "  " << label << ": [";
        for (std::size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i] << (i + 1 < elements.size() ? ", " : "");
        }
        std::cout << "]  (size=" << elements.size() << ")\n";
    }

    // Basic guarantee: valid afterwards, but NOT rolled back on failure.
    void addAll(const std::vector<int>& values) {
        for (int v : values) {
            if (v == POISON) {
                throw std::invalid_argument(
                    "Poison value encountered -- aborting remainder of batch");
            }
            elements.push_back(v);   // each push_back leaves the vector valid
        }
    }

    // A basic-guarantee "invariant check" a caller can always rely on after
    // ANY method throws: the object is well-formed and usable.
    bool invariantHolds() const {
        // For this simple class the invariant is trivial (vector is always
        // internally consistent), but in general you would check things
        // like "every pointer is either null or owns valid memory", etc.
        return true;
    }
};

int main() {
    std::cout << "=== LEVEL 1: BASIC GUARANTEE ===\n\n";

    BasicGuaranteeContainer c;
    c.addAll({1, 2, 3});
    c.print("Initial state");

    std::cout << "\nAttempting to add a batch that contains a poison value...\n";
    std::vector<int> batch = {4, 5, BasicGuaranteeContainer::POISON, 6, 7};

    try {
        c.addAll(batch);
        std::cout << "  (unreachable: addAll should have thrown)\n";
    } catch (const std::exception& e) {
        std::cout << "  Caught exception: " << e.what() << "\n";
    }

    std::cout << "\nAfter the failed addAll():\n";
    c.print("Resulting state");
    std::cout << "  invariantHolds() = " << std::boolalpha << c.invariantHolds() << "\n";

    std::cout << "\nNotice: elements 4 and 5 (added BEFORE the poison value) remain in\n"
              << "the container -- the operation was NOT rolled back. This differs from\n"
              << "the original {1,2,3} state, so we do NOT have the Strong Guarantee.\n"
              << "However, the container is still perfectly valid and safe to keep\n"
              << "using: no leak, no corruption, no dangling pointers.\n\n";

    // Prove the object is still fully usable after the exception.
    c.addAll({100, 200});
    c.print("Still usable afterwards");

    std::cout << "\nLesson: the Basic Guarantee is the MINIMUM every exception-safe\n"
              << "class should offer. It is easy to achieve by relying on RAII members\n"
              << "(like std::vector here) so that partial completion never corrupts\n"
              << "the object, even though it doesn't undo partial work.\n";
    return 0;
}
