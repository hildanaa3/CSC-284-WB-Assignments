#include <iostream>
#include "BankAccount.h"
using namespace std;

int main() {
    cout << "Creating accounts...\n\n";

    BankAccount alice("Alice", 1000.00);
    BankAccount bob("Bob", 500.00);

    cout << "Initial account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    cout << "Alice deposits $200\n";
    alice.deposit(200.00);

    cout << "Bob withdraws $100\n";
    bob.withdraw(100.00);

    cout << "\nUpdated account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    cout << "Total active accounts: " << BankAccount::getTotalAccounts() << endl;

    cout << "\nEntering block scope...\n";
    {
        BankAccount temp("Charlie", 310.00);
        cout << "Total active accounts: " << BankAccount::getTotalAccounts() << endl;
    }
    cout << "Leaving block scope...\n";
    cout << "Total active accounts after block: " << BankAccount::getTotalAccounts() << endl;

    cout << "\nAlice transfers $250 to Bob...\n";
    alice.transfer(bob, 10.00);

    cout << "\nFinal account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    cout << "Exiting program...\n";
    return 0;
}
