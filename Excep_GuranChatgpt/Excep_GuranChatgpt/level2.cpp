//Commit-or-Rollback
//Now modify the previous example so that a failed operation changes nothing.
#include <iostream>
#include <stdexcept>
using namespace std;
class BankAccount {
private:
    double balance;
public:
    BankAccount(double b)
        : balance(b) {
    }

    void withdraw(double amount) {

        if (amount <= 0) {
            throw invalid_argument(
                "Withdrawal amount must be positive"
            );
        }

        if (amount > balance) {
            throw runtime_error(
                "Insufficient balance"
            );
        }

        // Commit only after all checks succeed
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }
};

int main() {

    BankAccount account(1000);

    cout << "Before transaction: "
         << account.getBalance() << endl;

    try {
        account.withdraw(1500);
    }
    catch (const exception& e) {
        cout << "Exception: "
             << e.what() << endl;
    }

    cout << "After failed transaction: "
         << account.getBalance() << endl;

    return 0;
}