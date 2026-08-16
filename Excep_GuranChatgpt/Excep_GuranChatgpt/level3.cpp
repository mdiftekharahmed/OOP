//This is the strongest guarantee.

//The operation promises: It will not throw an exception.

#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance;

public:
    BankAccount(double b)
        : balance(b) {
    }

    double getBalance() const noexcept {
        return balance;
    }

    void reset() noexcept {
        balance = 0;
    }
};

int main() {

    BankAccount account(5000);

    cout << "Before reset: "
         << account.getBalance() << endl;

    account.reset();

    cout << "After reset: "
         << account.getBalance() << endl;

    return 0;
}