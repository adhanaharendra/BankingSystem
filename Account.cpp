#include "Account.h"
#include <fstream>

// CONSTRUCTOR
Account::Account(string n,
                 int accNo,
                 double bal,
                 string pass)
{

    name = n;
    accountNumber = accNo;
    balance = bal;
    password = pass;

    frozen = false;
}

// GETTERS
int Account::getAccountNumber()
{

    return accountNumber;
}

string Account::getName()
{

    return name;
}

double Account::getBalance()
{

    return balance;
}

string Account::getPassword()
{

    return password;
}

bool Account::isFrozen()
{

    return frozen;
}

// FREEZE
void Account::freezeAccount()
{

    frozen = true;
}
// UNFREEZE
void Account::unfreezeAccount()
{

    frozen = false;
}

// DISPLAY
void Account::display()
{

    cout << "\n----- ACCOUNT DETAILS -----\n";

    cout << "Name : "
         << name << endl;

    cout << "Account Number : "
         << accountNumber << endl;

    cout << "Balance : ₹"
         << balance << endl;

    cout << "Status : ";

    if (frozen)
        cout << "Frozen\n";
    else
        cout << "Active\n";
}

// HISTORY
void Account::addHistory(string entry)
{

    history.push_back(entry);
}

void Account::showHistory()
{

    cout << "\n--- TRANSACTION HISTORY ---\n";

    if (history.empty())
    {

        cout << "No Transactions Yet.\n";
        return;
    }

    for (string entry : history)
    {

        cout << entry << endl;
    }
}

// DEPOSIT
void Account::deposit(double amount)
{

    if (frozen)
    {

        cout << "Account Frozen!\n";
        return;
    }

    balance += amount;

    string entry =
        "Deposited ₹" +
        to_string((int)amount);

    addHistory(entry);

    cout << "₹" << amount
         << " deposited successfully.\n";
}

// WITHDRAW
void Account::withdraw(double amount)
{

    if (frozen)
    {

        cout << "Account Frozen!\n";
        return;
    }

    if (amount > balance)
    {

        cout << "Insufficient Balance!\n";
    }
    else
    {

        balance -= amount;

        string entry =
            "Withdrawn ₹" +
            to_string((int)amount);

        addHistory(entry);

        cout << "₹" << amount
             << " withdrawn successfully.\n";
    }
}

// CHECK BALANCE
void Account::checkBalance()
{

    cout << "Current Balance : ₹"
         << balance << endl;
}

// SAVE TO FILE
void Account::saveToFile(ofstream &fout)
{

    fout << name << endl;
    fout << accountNumber << endl;
    fout << balance << endl;
    fout << password << endl;
    fout << frozen << endl;

    fout << history.size() << endl;

    for (string entry : history)
    {

        fout << entry << endl;
    }
}

// TRANSFER
void Account::transfer(Account &receiver,
                       double amount)
{

    if (frozen)
    {

        cout << "Account Frozen!\n";
        return;
    }

    if (amount > balance)
    {

        cout << "Insufficient Balance!\n";
        return;
    }

    balance -= amount;

    receiver.balance += amount;

    string sentEntry =
        "Transferred ₹" +
        to_string((int)amount) +
        " to Acc No " +
        to_string(receiver.accountNumber);

    string receiveEntry =
        "Received ₹" +
        to_string((int)amount) +
        " from Acc No " +
        to_string(accountNumber);

    addHistory(sentEntry);

    receiver.addHistory(receiveEntry);

    cout << "Transfer Successful!\n";
}

// LOAD FROM FILE
void Account::loadFromFile(ifstream &fin)
{

    getline(fin, name);

    fin >> accountNumber;
    fin >> balance;

    fin.ignore();

    getline(fin, password);

    fin >> frozen;

    int historySize;

    fin >> historySize;

    if (fin.fail() ||
        historySize < 0 ||
        historySize > 1000)
    {

        historySize = 0;
    }

    fin.ignore();

    history.clear();

    for (int i = 0; i < historySize; i++)
    {

        string entry;

        getline(fin, entry);

        history.push_back(entry);
    }
}