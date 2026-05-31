#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>

using namespace std;

class Account
{

private:
    string name;
    int accountNumber;
    double balance;
    string password;

    bool frozen;

    vector<string> history;

public:
    Account(string n = "",
            int accNo = 0,
            double bal = 0,
            string pass = "");

    // GETTERS
    int getAccountNumber();

    string getName();

    double getBalance();

    string getPassword();

    bool isFrozen();

    // FUNCTIONS
    void freezeAccount();

    void unfreezeAccount();

    void display();

    void transfer(Account &receiver,
                  double amount);

    void deposit(double amount);

    void withdraw(double amount);

    void checkBalance();

    void addHistory(string entry);

    void showHistory();

    // FILE HANDLING
    void saveToFile(ofstream &fout);

    void loadFromFile(ifstream &fin);
};

#endif