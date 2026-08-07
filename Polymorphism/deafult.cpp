#include <iostream>
#include <string>
using namespace std;

void greet(string name, string title = "Mr./Ms.", string greeting = "Hello") {
    cout << greeting << ", " << title << " " << name << "!\n";
}

int main() {
    cout << "=== Default Parameters ===\n";
    greet("Alice");                            // Hello, Mr./Ms. Alice!
    greet("Bob", "Dr.");                       // Hello, Dr. Bob!
    greet("Carol", "Prof.", "Good morning");   // Good morning, Prof. Carol!
    return 0;
}