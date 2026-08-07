#include <iostream>
using namespace std;

class Student {
public:
    int id;

    Student(int i) {
        id = i;
    }

    bool operator==(const Student& s) {
        return id == s.id;
    }
};

int main() {

    Student s1(100);
    Student s2(100);

    if (s1 == s2)
        cout << "Equal"<<endl;
    else
        cout << "Not Equal"<<endl;
        ;
    return 0;
}