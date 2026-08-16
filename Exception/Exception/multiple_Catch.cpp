#include <iostream>
using namespace std;

int main() {
    int choice;

    cout << "Enter 1, 2, or 3: ";
    cin >> choice;

    try {
        if (choice == 1)
            throw 100;

        if (choice == 2)
            throw 5.5;

        if (choice == 3)
            throw 'X';
    }
    catch (int e) {
        cout << "Integer exception: " << e << endl;
    }
    catch (double e) {
        cout << "Double exception: " << e << endl;
    }
    catch (char e) {
        cout << "Character exception: " << e << endl;
    }

    return 0;
}