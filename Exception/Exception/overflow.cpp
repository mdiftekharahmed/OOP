#include <iostream>
#include <stdexcept>
#include <climits>
using namespace std;

int add(int a, int b) {
    if (b > 0 && a > INT_MAX - b) {
        throw overflow_error(
            "Integer overflow occurred."
        );
    }

    return a + b;
}

int main() {
    try {
        cout << "Result: "<<INT_MAX;
        cout << add(INT_MAX, 10);
    }
    catch (const overflow_error& e) {
        cout << "Overflow error: "
             << e.what() << endl;
    }

    return 0;
}