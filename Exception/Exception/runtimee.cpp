#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw runtime_error("Division by zero");
    }

    return a / b;
}

int main() {
    try {
        cout << divide(10, 0);
    }
    catch (const runtime_error& e) {
        cout << "Runtime error: "
             << e.what() << endl;
    }

    return 0;
}