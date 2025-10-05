#pragma once
#include <string>
using namespace std;

class BankAccount
{
private:
    string accountHolder;
    int accountNumber;
    double balance;

    static int totalAccounts;
    static int nextAccountNumber;

public:
    BankAccount();
    BankAccount(const string &name, double initialBalance);
    ~BankAccount();

    string getAccountHolder() const;
    int getAccountNumber() const;
    double getBalance() const;

    void deposit(double amount);
    void withdraw(double amount);
    void transfer(BankAccount &toAccount, double amount);
    void printAccountInfo() const;

    static int getTotalAccounts();
};
