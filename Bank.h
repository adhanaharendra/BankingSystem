#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <unordered_map>


class Bank
{

private:
    vector<Account> accounts;
    unordered_map<int, int> accountMap;

public:
    Bank();

    // FILE HANDLING
    void saveAccounts();

    void loadAccounts();

    // SEARCH

    void rebuildMap();
    int findAccount(int accNo);

    // LOGIN
    int login();

    // ACCOUNT OPS
    void createAccount();

    void userMenu(int userIndex);

    // ADMIN
    void adminPanel();

    // MAIN MENU
    void run();
};

#endif