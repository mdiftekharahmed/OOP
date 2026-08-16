
//Consider a bank account where a transaction-processing fee is charged before the withdrawal is completed.
//The original state was not restored, but the account is still valid and usable.
//If an exception occurs, the object may change, but it remains in a valid state and resources are not leaked.
#include <iostream>
#include <stdexcept>
using namespace std;

class BankAccount {
private:
    double balance;
public:
    BankAccount(double b) : balance(b) {}
    void withdraw(double amount) {
        // Transaction processing has started
        double fee = 10;
        if (balance >= fee)
            balance -= fee;
        // Withdrawal cannot be completed
        if (amount > balance) {
            throw runtime_error(
                "Insufficient balance for withdrawal"
            );
        }
        balance -= amount;
    }
    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount account(1000);
    cout << "Before transaction: " << account.getBalance() << endl;
    try {
        account.withdraw(1500);
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    cout << "After failed transaction: " << account.getBalance() << endl;
    return 0;
}