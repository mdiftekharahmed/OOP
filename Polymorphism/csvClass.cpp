#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {

private:
    int id;
    string name;
    double cgpa;

public:

    Student(int i, string n, double c)
        : id(i), name(n), cgpa(c) {
    }


    void writeToCSV(ofstream& file) const {

        file << id << ","
             << name << ","
             << cgpa
             << endl;
    }
};


int main() {

    Student s1(101, "Rahim", 3.75);
    Student s2(102, "Karim", 3.82);
    Student s3(103, "Nadia", 3.91);


    ofstream file("class_students.csv");


    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }


    // CSV header
    file << "ID,Name,CGPA" << endl;


    s1.writeToCSV(file);
    s2.writeToCSV(file);
    s3.writeToCSV(file);


    file.close();

    return 0;
}