#include <iostream>
#include <fstream> // inlcude this for file handing
#include <string>

using namespace std;

int main() {

    ofstream file("students.csv"); //if file not there, it'll create one

    if (!file) { //if failed to open file
        cout << "Error opening file!" << endl;
        return 1;
    }


    file << "ID,Name,CGPA" << endl; //same insertion operator << is used in file writing also


    for (int i = 0; i < 3; i++) {

        int id;
        string name;
        double cgpa;

        cout << "\nEnter Student " << i + 1 << endl;

        cout << "ID: ";
        cin >> id;

        cout << "Name: ";
        cin >> name;

        cout << "CGPA: ";
        cin >> cgpa;


        file << id << ","
             << name << ","
             << cgpa << endl;
    }


    file.close();

    cout << "\nCSV file created successfully." << endl;

    return 0;
}