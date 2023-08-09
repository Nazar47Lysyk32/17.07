#include <iostream>
#include <string>

using namespace std;

class Client {
private:
    string name;
    int accountNumber;
    double balance;
    Client* next;

public:
    Client(const string& n, int accNum, double initBalance)
        : name(n), accountNumber(accNum), balance(initBalance), next(nullptr) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " to account " << accountNumber << endl;
        }
        else {
            cout << "Invalid deposit amount" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn $" << amount << " from account " << accountNumber << endl;
        }
        else {
            cout << "Invalid withdrawal amount" << endl;
        }
    }

    void displayBalance() {
        cout << "Account " << accountNumber << " balance: $" << balance << endl;
    }

    friend class Bank;
};

class Bank {
private:
    string bankName;
    Client* clients;
    double totalBalance;

public:
    Bank(const string& name) : bankName(name), clients(nullptr), totalBalance(0) {}

    void addClient(const string& name, int accNum, double initBalance) {
        Client* newClient = new Client(name, accNum, initBalance);
        newClient->next = clients;
        clients = newClient;
        totalBalance += initBalance;
        cout << "Added new client: " << name << endl;
    }

    void removeClient(int accNum) {
        Client* prev = nullptr;
        Client* current = clients;

        while (current != nullptr) {
            if (current->accountNumber == accNum) {
                totalBalance -= current->balance;
                if (prev == nullptr) {
                    clients = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Removed client with account number " << accNum << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Client with account number " << accNum << " not found" << endl;
    }

    void displayTotalBalance() {
        cout << "Total bank balance: $" << totalBalance << endl;
    }
};

int main() {
    Bank bank("MyBank");

    bank.addClient("Client 1", 101, 1000);
    bank.addClient("Client 2", 102, 2000);
    bank.addClient("Client 3", 103, 1500);

    bank.displayTotalBalance();

    // Perform some operations
    bank.removeClient(102);
    bank.addClient("Client 4", 104, 3000);

    bank.displayTotalBalance();

    return 0;
}
