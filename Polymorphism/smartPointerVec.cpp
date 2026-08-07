#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;


class Student {
private:
    int id;
    string name;
    double cgpa;

public:

    Student(int i, string n, double c) {
        id = i;
        name = n;
        cgpa = c;

        cout << "Created: " << name << endl;
    }


    void display() const {
        cout << "ID   : " << id << endl;
        cout << "Name : " << name << endl;
        cout << "CGPA : " << cgpa << endl;
        cout << "------------------------" << endl;
    }


    ~Student() {
        cout << "Destroyed: " << name << endl;
    }
};


int main() {

    // Vector of unique_ptr<Student>
    vector<unique_ptr<Student>> students;


    // Create Student objects
    // and transfer ownership to vector

    students.push_back(
        make_unique<Student>(
            101,
            "Rahim",
            3.75
        )
    );


    students.push_back(
        make_unique<Student>(
            102,
            "Karim",
            3.82
        )
    );


    students.push_back(
        make_unique<Student>(
            103,
            "Nadia",
            3.91
        )
    );


    students.push_back(
        make_unique<Student>(
            104,
            "Hasan",
            3.65
        )
    );


    cout << "\nStudent Information\n";
    cout << "========================\n";


    // Access all objects
    for (const auto& student : students) {

        student->display();

    }


    cout << "\nTotal Students: "
         << students.size()
         << endl;


    cout << "\nEnd of program.\n";

    // We do not have to delete any object.
    // vector destroys its unique_ptr elements.
    // Each unique_ptr automatically destroys
    // its Student object.

    return 0;
}