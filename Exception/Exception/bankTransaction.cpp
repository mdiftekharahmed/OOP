#include <iostream>
#include <stdexcept>
using namespace std;

class InsufficientBalanceException : public exception {
public:
    const char* what() const noexcept override {
        return "Insufficient account balance.";
    }
};
class BankAccount {
private:
    double balance;

public:
    BankAccount(double b)
        : balance(b) {
    }

    void withdraw(double amount) {
        if (amount > balance) {
            throw InsufficientBalanceException();
        }

        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }
};
int main() {
    BankAccount account(1000.0);

    try {
        account.withdraw(500.0);
        cout<<"balance: "<<account.getBalance()<<endl;
    }
    catch (const InsufficientBalanceException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}