#include "Bank.h"

#include <iostream>
#include <fstream>

using namespace std;

Bank::Bank()
{

    loadAccounts();

    rebuildMap();
}

// SAVE ACCOUNTS
void Bank::saveAccounts()
{

    ofstream fout("accounts.txt");

    fout << accounts.size() << endl;

    for (auto &acc : accounts)
    {

        acc.saveToFile(fout);
    }

    fout.close();
}

// LOAD ACCOUNTS
void Bank::loadAccounts()
{

    ifstream fin("accounts.txt");

    if (!fin)
        return;

    int totalAccounts;

    fin >> totalAccounts;

    if (fin.fail() ||
        totalAccounts < 0 ||
        totalAccounts > 10000)
    {

        return;
    }

    fin.ignore();

    for (int i = 0; i < totalAccounts; i++)
    {

        Account temp;

        temp.loadFromFile(fin);

        if (temp.getAccountNumber() != 0)
        {

            accounts.push_back(temp);
        }
    }

    fin.close();
}

// REBUILD MAP
void Bank::rebuildMap()
{
    accountMap.clear();

    for (int i = 0; i < accounts.size(); i++)
    {
        accountMap[accounts[i].getAccountNumber()] = i;
    }
}

// SEARCH
int Bank::findAccount(int accNo)
{
    if (accountMap.find(accNo) == accountMap.end())
    {
        return -1;
    }

    return accountMap[accNo];
}
// LOGIN
int Bank::login()
{

    int accNo;
    string pass;

    cout << "Enter Account Number : ";

    cin >> accNo;

    cout << "Enter Password : ";

    cin >> pass;

    int index =
        findAccount(accNo);

    if (index == -1)
    {

        cout << "Account Not Found!\n";

        return -1;
    }

    if (accounts[index].isFrozen())
    {

        cout << "Account Frozen!\n";

        return -1;
    }

    if (accounts[index]
            .getPassword() != pass)
    {

        cout << "Incorrect Password!\n";

        return -1;
    }

    cout << "Login Successful!\n";

    return index;
}

// CREATE ACCOUNT
void Bank::createAccount()
{

    string name;
    int accNo;
    double balance;
    string password;

    cout << "Enter Name : ";

    cin >> name;

    cout << "Enter Account Number : ";

    cin >> accNo;

    cout << "Enter Initial Balance : ";

    cin >> balance;

    cout << "Create Password : ";

    cin >> password;

    if (findAccount(accNo) != -1)
    {

        cout << "Account Number Already Exists!\n";

        return;
    }

    Account newUser(name,
                    accNo,
                    balance,
                    password);

    accounts.push_back(newUser);
    rebuildMap();

    saveAccounts();

    cout << "Account Created Successfully!\n";
}

// USER MENU
void Bank::userMenu(int userIndex)
{

    int choice;

    while (true)
    {

        cout << "\n===== USER MENU =====\n";

        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer Money\n";
        cout << "4. Display Details\n";
        cout << "5. Transaction History\n";
        cout << "6. Check Balance\n";
        cout << "0. Logout\n";

        cout << "Enter Choice : ";

        cin >> choice;

        if (choice == 1)
        {

            double amount;

            cout << "Enter Amount : ";

            cin >> amount;

            accounts[userIndex]
                .deposit(amount);

            saveAccounts();
        }

        else if (choice == 2)
        {

            double amount;

            cout << "Enter Amount : ";

            cin >> amount;

            accounts[userIndex]
                .withdraw(amount);

            saveAccounts();
        }

        else if (choice == 6)
        {

            accounts[userIndex]
                .checkBalance();
        }
        else if (choice == 3)
        {

            int receiverAcc;
            double amount;

            cout << "Enter Receiver Account No : ";

            cin >> receiverAcc;

            int receiverIndex =
                findAccount(receiverAcc);

            if (receiverIndex == -1)
            {

                cout << "Receiver Account Not Found!\n";
            }
            else
            {

                cout << "Enter Amount : ";

                cin >> amount;

                accounts[userIndex]
                    .transfer(
                        accounts[receiverIndex],
                        amount);

                saveAccounts();
            }
        }
        else if (choice == 4)
        {

            accounts[userIndex]
                .display();
        }

        else if (choice == 5)
        {

            accounts[userIndex]
                .showHistory();
        }

        else if (choice == 0)
        {

            cout << "Logged Out Successfully!\n";

            break;
        }

        else
        {

            cout << "Invalid Choice!\n";
        }
    }
}

// ADMIN PANEL
void Bank::adminPanel()
{

    string adminPass;

    cout << "Enter Admin Password : ";

    cin >> adminPass;

    if (adminPass != "admin123")
    {

        cout << "Wrong Password!\n";

        return;
    }

    int choice;

    while (true)
    {

        cout << "\n===== ADMIN PANEL =====\n";

        cout << "1. View All Accounts\n";
        cout << "2. Freeze Account\n";
        cout << "3. Unfreeze Account\n";
        cout << "4. Delete Account\n";
        cout << "5. Exit\n";

        cout << "Enter Choice : ";

        cin >> choice;

        // VIEW
        if (choice == 1)
        {

            for (auto &acc : accounts)
            {

                acc.display();
            }
        }

        // FREEZE
        else if (choice == 2)
        {

            int accNo;

            cout << "Enter Account Number : ";

            cin >> accNo;

            int index =
                findAccount(accNo);

            if (index == -1)
            {

                cout << "Account Not Found!\n";
            }
            else
            {

                accounts[index]
                    .freezeAccount();

                saveAccounts();

                cout << "Account Frozen!\n";
            }
        }
        else if (choice == 3)
        {

            int accNo;

            cout << "Enter Account Number : ";

            cin >> accNo;

            int index =
                findAccount(accNo);

            if (index == -1)
            {

                cout << "Account Not Found!\n";
            }
            else
            {

                accounts[index]
                    .unfreezeAccount();

                saveAccounts();

                cout << "Account Unfrozen Successfully!\n";
            }
        }
        // DELETE
        else if (choice == 4)
        {

            int accNo;

            cout << "Enter Account Number : ";

            cin >> accNo;

            int index =
                findAccount(accNo);

            if (index == -1)
            {

                cout << "Account Not Found!\n";
            }
            else
            {

                accounts.erase(
                    accounts.begin() + index);
                rebuildMap();

                saveAccounts();

                cout << "Account Deleted!\n";
            }
        }

        else if (choice == 5)
        {

            break;
        }

        else
        {

            cout << "Invalid Choice!\n";
        }
    }
}

// RUN SYSTEM
void Bank::run()
{

    int choice;

    while (true)
    {

        cout << "\n====== BANK SYSTEM ======\n";

        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";

        cout << "Enter Choice : ";

        cin >> choice;

        if (choice == 1)
        {

            createAccount();
        }

        else if (choice == 2)
        {

            int userIndex =
                login();

            if (userIndex != -1)
            {

                userMenu(userIndex);
            }
        }

        else if (choice == 3)
        {

            adminPanel();
        }

        else if (choice == 4)
        {

            saveAccounts();

            cout << "Thank You!\n";

            break;
        }

        else
        {

            cout << "Invalid Choice!\n";
        }
    }
}