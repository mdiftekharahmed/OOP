#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Calculator {
private:
    double memory;

public:
    Calculator() : memory(0) {}

    // ── Overloaded compute() — 4 different signatures ────────────
    int compute(int a, int b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return (b != 0) ? a / b : 0;
        }
        return 0;
    }

    double compute(double a, double b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return (b != 0) ? a / b : 0.0;
        }
        return 0;
    }

    double compute(double base, int exponent) {   // power
        return pow(base, exponent);
    }

    double compute(double value) {                // square root
        return (value >= 0) ? sqrt(value) : -1;
    }

    // ── Overloaded print() ────────────────────────────────────────
    void print(int result)    const { cout << "Result (int)   : " << result << "\n"; }
    void print(double result) const { cout << "Result (double): " << result << "\n"; }
    void print(string label, double result) const {
        cout << label << ": " << result << "\n";
    }

    // ── Overloaded store() ────────────────────────────────────────
    void store(double val)  { memory = val; cout << "Stored: " << val << "\n"; }
    void store(int val)     { memory = val; cout << "Stored: " << val << "\n"; }
    double recall()  const  { return memory; }
};

int main() {
    Calculator calc;

    // Compiler picks correct overload automatically
    calc.print( calc.compute(10, 3, '+') );       // int version
    calc.print( calc.compute(3.14, 2.0, '*') );   // double version
    calc.print("2^10", calc.compute(2.0, 10) );   // power version
    calc.print("sqrt(49)", calc.compute(49.0) );  // sqrt version

    calc.store(42);
    cout << "Recalled: " << calc.recall() << "\n";
}

// Output:
// Result (int)   : 13
// Result (double): 6.28
// 2^10: 1024
// sqrt(49): 7
// Stored: 42
// Recalled: 42
