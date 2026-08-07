#include <iostream>
#include <string>
using namespace std;

// ── Three overloaded functions — same name, different signatures ──
int add(int a, int b) {
    cout << "[int + int]       ";
    return a + b;
}

double add(double a, double b) {
    cout << "[double + double] ";
    return a + b;
}

string add(string a, string b) {
    cout << "[string + string] ";
    return a + b;
}

double add(int a, double b) {       // different ORDER of types
    cout << "[int + double]    ";
    return a + b;
}

int add(int a, int b, int c) {      // different NUMBER of parameters
    cout << "[int+int+int]     ";
    return a + b + c;
}

int main() {
    cout << add(3, 4)              << "\n";  // calls int version
    cout << add(3.5, 2.1)          << "\n";  // calls double version
    cout << add("Hello ", "C++")   << "\n";  // calls string version
    cout << add(3, 4.5)            << "\n";  // calls int+double version
    cout << add(1, 2, 3)           << "\n";  // calls three-param version
}

// Output:
// [int + int]       7
// [double + double] 5.6
// [string + string] Hello C++
// [int + double]    7.5
// [int+int+int]     6
