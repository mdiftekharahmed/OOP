#include <iostream>
using namespace std;

class Counter {

public:

    int value;

    Counter(int v) {
        value = v;
    }

    Counter operator++() {
        value++;
        return *this;
    }
};

int main() {

    Counter c(5);
    ++c;
    cout << c.value << endl;
}