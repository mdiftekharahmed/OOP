
//Experiment: Develop a Payment Processing System using Polymorphism
//CSV
#include <iostream>
#include <fstream>
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

    // Pure virtual function for writing CSV data
    virtual void writeToCSV(ofstream& file) const = 0;

    // Virtual destructor
    virtual ~Payment() = default;
};


// ----------------------------
// Credit Card Payment
// ----------------------------
class CreditCardPayment : public Payment {
private:
    string cardHolder;
    string cardNumber;

public:
    CreditCardPayment(double amt,
                      string holder,
                      string number)
        : Payment(amt),
          cardHolder(holder),
          cardNumber(number) {}

    void pay() const override {
        cout << "Credit Card Payment Successful!" << endl;
    }

    void writeToCSV(ofstream& file) const override {
        file << "Credit Card,"
             << cardHolder << ","
             << cardNumber << ","
             << amount << ","
             << "Successful"
             << endl;
    }
};


// ----------------------------
// Mobile Banking Payment
// ----------------------------
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
        cout << "Mobile Banking Payment Successful!" << endl;
    }

    void writeToCSV(ofstream& file) const override {
        file << "Mobile Banking,"
             << provider << ","
             << mobileNumber << ","
             << amount << ","
             << "Successful"
             << endl;
    }
};


// ----------------------------
// Bank Transfer Payment
// ----------------------------
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
        cout << "Bank Transfer Successful!" << endl;
    }

    void writeToCSV(ofstream& file) const override {
        file << "Bank Transfer,"
             << bankName << ","
             << accountNumber << ","
             << amount << ","
             << "Successful"
             << endl;
    }
};


// ----------------------------
// Cash Payment
// ----------------------------
class CashPayment : public Payment {

public:
    CashPayment(double amt)
        : Payment(amt) {}

    void pay() const override {
        cout << "Cash Payment Successful!" << endl;
    }

    void writeToCSV(ofstream& file) const override {
        file << "Cash,"
             << "N/A" << ","
             << "N/A" << ","
             << amount << ","
             << "Successful"
             << endl;
    }
};


// ----------------------------
// Main Function
// ----------------------------
int main() {

    vector<unique_ptr<Payment>> payments;

    payments.push_back(
        make_unique<CreditCardPayment>(
            6000,
            "Rahim Ahmed2",
            "1234-5678-9012"
        )
    );

    payments.push_back(
        make_unique<MobileBankingPayment>(
            3500,
            "01712345678",
            "bKash2"
        )
    );

    payments.push_back(
        make_unique<BankTransferPayment>(
            20000,
            "AC-987654",
            "Sonali Bank2"
        )
    );

    payments.push_back(
        make_unique<CashPayment>(
            25002
        )
    );


    // Create CSV file
    ofstream file("payment_output.csv");
    //ofstream file("payment_output.csv", ios::app);

    // Check whether file opened successfully
    if (!file.is_open()) {
        cout << "Error opening CSV file!" << endl;
        return 1;
    }


    // CSV Header
    file << "Payment_Type,Provider_or_Name,"
         << "Account_or_Number,Amount,Status"
         << endl;


    // Runtime Polymorphism
    for (const auto& payment : payments) {

        payment->pay();

        payment->writeToCSV(file);
    }


    // Close file
    file.close();

    cout << "\nPayment information successfully written to "
         << "payment_output.csv" << endl;

    return 0;
}