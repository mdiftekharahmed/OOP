#include <iostream>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw "Division by zero";
    }

    return a / b;
}

int main() {
    try {
        cout << divide(10, 0) << endl;
    }
    catch (const char* message) {
        cout << "Error: " << message <<  endl;
        

    }

    return 0;
}