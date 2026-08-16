#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers = {10, 20, 30};

    try {
        cout << numbers.at(2)<< endl; // Valid access
    }
    catch (const out_of_range& e) {
        cout << "Index error: "
             << e.what() << endl;
    }
}