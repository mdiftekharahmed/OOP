
//Experiment: Develop a Payment Processing System using Polymorphism
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Abstract Base Class
class Payment {
protected:
    double amount;

public:
    Payment(double amt) : amount(amt) {}

    // Pure virtual function
    virtual void pay() const = 0;

    // Virtual function
    virtual void displayPaymentInfo() const {
        cout << "Payment Amount: " << amount << " Taka" << endl;
    }

    // Virtual destructor
    virtual ~Payment() = default;
};


// Derived Class 1
class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string cardHolder;

public:
    CreditCardPayment(double amt,
                      string holder,
                      string number)
        : Payment(amt),
          cardHolder(holder),
          cardNumber(number) {}

    void pay() const override {
        cout << "\nProcessing Credit Card Payment..." << endl;
        cout << "Card Holder: " << cardHolder << endl;
        cout << "Card Number: " << cardNumber << endl;
        cout << "Amount Paid: " << amount << " Taka" << endl;
        cout << "Payment Successful!" << endl;
    }
};


// Derived Class 2
class MobileBankingPayment : public Payment {
private:
    string mobileNumber;
    string provider;

public:
    MobileBankingPayment(double amt,
                         string number,
                         string service)
        : Payment(amt),
          mobileNumber(number),
          provider(service) {}

    void pay() const override {
        cout << "\nProcessing Mobile Banking Payment..." << endl;
        cout << "Provider: " << provider << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Amount Paid: " << amount << " Taka" << endl;
        cout << "Payment Successful!" << endl;
    }
};


// Derived Class 3
class BankTransferPayment : public Payment {
private:
    string accountNumber;
    string bankName;

public:
    BankTransferPayment(double amt,
                        string account,
                        string bank)
        : Payment(amt),
          accountNumber(account),
          bankName(bank) {}

    void pay() const override {
        cout << "\nProcessing Bank Transfer..." << endl;
        cout << "Bank Name: " << bankName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Amount Paid: " << amount << " Taka" << endl;
        cout << "Payment Successful!" << endl;
    }
};


// Derived Class 4
class CashPayment : public Payment {

public:
    CashPayment(double amt)
        : Payment(amt) {}

    void pay() const override {
        cout << "\nProcessing Cash Payment..." << endl;
        cout << "Amount Paid: " << amount << " Taka" << endl;
        cout << "Cash Payment Successful!" << endl;
    }
};


// Common polymorphic function
void processPayment(const Payment& payment) {
    payment.pay();
}


int main() {

    CreditCardPayment creditCard(
        5000,
        "Rahim Ahmed",
        "1234-5678-9012"
    );

    MobileBankingPayment mobileBanking(
        2500,
        "01712345678",
        "bKash"
    );

    BankTransferPayment bankTransfer(
        10000,
        "AC-987654",
        "Sonali Bank"
    );

    CashPayment cash(
        1500
    );


    // Runtime Polymorphism
    processPayment(creditCard);
    processPayment(mobileBanking);
    processPayment(bankTransfer);
    processPayment(cash);

    return 0;
}