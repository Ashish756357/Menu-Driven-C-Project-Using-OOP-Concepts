#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Account {
private:
    string accountNumber;
    string pin;
    double balance;

public:
    Account(string accNum, string pinNum, double initialBalance) {
        accountNumber = accNum;
        pin = pinNum;
        balance = initialBalance;
    }

    void displayBalance() {
        cout << "Account Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit Successful. New Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal Successful. New Balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Insufficient Balance." << endl;
        }
    }

    bool verifyPin(string enteredPin) {
        return pin == enteredPin;
    }
};

class ATM {
private:
    vector<Account> accounts;
    Account* currentAccount;

public:
    ATM() {
        // Initialize accounts (You can add more accounts)
        accounts.push_back(Account("123456", "1234", 1000.00));
        accounts.push_back(Account("789012", "5678", 1500.00));
    }

    void displayMenu() {
        cout << "Welcome to the ATM!" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
    }

    void authenticateAccount() {
        string accNum, pin;
        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Enter PIN: ";
        cin >> pin;

        for (Account& acc : accounts) {
            if (acc.verifyPin(pin) && accNum == acc.accountNumber) {
                currentAccount = &acc;
                return;
            }
        }
        cout << "Authentication failed. Account not found or PIN is incorrect." << endl;
    }

    void run() {
        authenticateAccount();
        if (currentAccount == nullptr) {
            return;
        }

        int choice;
        while (true) {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    currentAccount->displayBalance();
                    break;
                case 2:
                    double depositAmount;
                    cout << "Enter deposit amount: $";
                    cin >> depositAmount;
                    currentAccount->deposit(depositAmount);
                    break;
                case 3:
                    double withdrawAmount;
                    cout << "Enter withdrawal amount: $";
                    cin >> withdrawAmount;
                    currentAccount->withdraw(withdrawAmount);
                    break;
                case 4:
                    cout << "Exiting ATM. Thank you!" << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    ATM atm;
    atm.run();

    return 0;
}
