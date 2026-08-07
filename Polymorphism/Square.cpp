#include <iostream>
using namespace std;

class Square {

public:

    int operator()(int x) {
        return x*x;
    }
};

int main() {

    Square sq;

    cout << sq(6) << endl;
}