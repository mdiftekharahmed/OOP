
#include <iostream>
using namespace std;

class Array {

private:
    int data[5];

public:

    Array() {

        for(int i=0;i<5;i++)
            data[i]=0;
    }

    int& operator[](int index) {

        return data[index];
    }
};

int main() {

    Array a;

    a[0]=100;

    cout<<a[4]<<endl;
}