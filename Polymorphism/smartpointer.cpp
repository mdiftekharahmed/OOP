#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Student {
private:
    string name;

public:
    Student(string n) {
        name = n;
        cout << "Created: " << name << endl;
    }

    void display() {
        cout << "Student: " << name << endl;
    }

    ~Student() {
        cout << "Destroyed: " << name << endl;
    }
};


int main() {

    unique_ptr<Student> p1 =
        make_unique<Student>("Rahim");

    cout << "\n Using p1:" << endl;
    p1->display();


    // This is NOT allowed:
    //
    // unique_ptr<Student> p2 = p1;
    //
    // because a unique_ptr cannot be copied.


    // Ownership can be transferred using move()
    unique_ptr<Student> p2 = std::move(p1);


    cout << "\nAfter transferring ownership:" << endl;

    if (p1 == nullptr)
        cout << "p1 no longer owns the object." << endl;


    if (p2 != nullptr) {
        cout << "p2 now owns the object." << endl;
        p2->display();
    }


    return 0;
}