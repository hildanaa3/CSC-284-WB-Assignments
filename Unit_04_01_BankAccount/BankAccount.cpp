#include "BankAccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

int BankAccount::totalAccounts = 0;
int BankAccount::nextAccountNumber = 1001;

BankAccount::BankAccount()
    : accountHolder("Unknown"), accountNumber(nextAccountNumber++), balance(0.0)
{
    ++totalAccounts;
}

BankAccount::BankAccount(const string &name, double initialBalance)
    : accountHolder(name), accountNumber(nextAccountNumber++), balance(initialBalance)
{
    ++totalAccounts;
}

BankAccount::~BankAccount()
{
    cout << "Destructor called for account " << accountNumber << endl;
    --totalAccounts;
}

string BankAccount::getAccountHolder() const { return accountHolder; }
int BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }

void BankAccount::deposit(double amount)
{
    if (amount <= 0)
    {
        cout << "Deposit amount must be positive.\n";
        return;
    }
    balance += amount;
}

void BankAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        cout << "Withdrawal amount must be positive.\n";
        return;
    }
    if (amount > balance)
    {
        cout << "Insufficient funds.\n";
        return;
    }
    balance -= amount;
}

void BankAccount::transfer(BankAccount &toAccount, double amount)
{
    if (amount <= 0)
    {
        cout << "Transfer amount must be positive.\n";
        return;
    }
    if (amount > balance)
    {
        cout << "Transfer failed. Check amount or balance.\n";
        return;
    }
    balance -= amount;
    toAccount.balance += amount;
    cout << "Transferred $" << amount << " from " << accountHolder
         << " to " << toAccount.accountHolder << endl;
}

void BankAccount::printAccountInfo() const
{
    cout << "Account Holder: " << accountHolder << endl
         << "Account Number: " << accountNumber << endl
         << fixed << setprecision(2)
         << "Balance: $" << balance << "\n\n";
}

int BankAccount::getTotalAccounts() { return totalAccounts; }
