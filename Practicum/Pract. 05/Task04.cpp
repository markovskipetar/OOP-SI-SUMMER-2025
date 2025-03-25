#include <iostream>
#include <string.h>
#include <fstream>

#pragma warning (disable:4996)

namespace CONSTANTS {
    constexpr int NAME_CAPACITY = 15;
    constexpr int BANK_ACCOUTN_NUMBER_CAPACITY = 30;
    constexpr int STRINGS_MINIMUM_SIZE = 2;
    constexpr int STARTING_BANK_ACCOUNTS_CAPACITY = 2;

}

class BankAccount {
public:
    BankAccount(const char* name, const char* number, double balance) {
        setClientName(name);
        setBankAccountNumber(number);
        setBalance(balance);
    }

    BankAccount(const char* name) {
        setClientName(name);
        setBankAccountNumber("");
        setBalance(0);
    }

    BankAccount() {
        setClientName("");
        setBankAccountNumber("");
        setBalance(0);
    }

    void readBankAccountFromFile(std::ifstream& ifs) {
        ifs.getline(clientName, CONSTANTS::NAME_CAPACITY, '\n');
        ifs.getline(bankAccountNumber, CONSTANTS::BANK_ACCOUTN_NUMBER_CAPACITY, '\n');
        ifs >> balance;
        ifs.ignore();
    }

    void writeBankAccountToFile(std::ofstream& ofs) {
        ofs << clientName << std::endl;
        ofs << bankAccountNumber << std::endl;
        ofs << balance << std::endl;
    }

    void deposit(double amount) {
        if (amount < 0) {
            std::cerr << "Cannot deposit negative amount" << std::endl;
            return;
        }

        balance += amount;
    }

    void draw(double amount) {
        if (amount < 0) {
            std::cerr << "Cannot draw negative amount" << std::endl;
            return;
        }

        balance -= amount;
    }

    void print(std::ostream& s) const {
        s << "Bank account of " << clientName << " with number " << bankAccountNumber << " and balance: " << balance << "$" << std::endl;
    }

    const char* getBankAccountNumber() const {
        return bankAccountNumber;
    }

    const char* getBankAccountName() const {
        return clientName;
    }

    double getBankAccountBalance() const {
        return balance;
    }

    void setClientName(const char* name) {
        if (!name) {
            std::cerr << "Client name is nullptr" << std::endl;
            strcpy(clientName, "");
            return;
        }

        if (strlen(name) >= CONSTANTS::NAME_CAPACITY) {
            std::cerr << "Client name size is over 30" << std::endl;
            strcpy(clientName, "");
            return;
        }

        strcpy(clientName, name);
    }

    void setBankAccountNumber(const char* number) {
        if (strlen(number) >= CONSTANTS::BANK_ACCOUTN_NUMBER_CAPACITY) {
            std::cerr << "Client number size is over 30" << std::endl;
            strcpy(bankAccountNumber, "");
            return;
        }

        if (!number) {
            std::cerr << "Client number is nullptr" << std::endl;
            strcpy(bankAccountNumber, "");
            return;
        }

        strcpy(bankAccountNumber, number);
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

private:
    char clientName[CONSTANTS::NAME_CAPACITY];
    char bankAccountNumber[CONSTANTS::BANK_ACCOUTN_NUMBER_CAPACITY];
    double balance;
};

class Bank {
public:
    Bank() {
        size = 0;
        capacity = CONSTANTS::STARTING_BANK_ACCOUNTS_CAPACITY;
        bankAccounts = new BankAccount[capacity];
    }

    Bank(std::ifstream& ifs) {
        if (!ifs.is_open()) {
            std::cerr << "Opening file to read bank information was unsuccessfull";
            return;
        }

        size = 0;
        capacity = CONSTANTS::STARTING_BANK_ACCOUNTS_CAPACITY;
        bankAccounts = new BankAccount[capacity];

        while (true) {
            BankAccount bankAccount;
            bankAccount.readBankAccountFromFile(ifs);
            addBankAccount(bankAccount);

            if (ifs.eof()) {
                break;
            }
        }

    }

    void addBankAccount(const BankAccount& bankAccount) {
        if (size == capacity) {
            resize(capacity * 2);
        }

        bankAccounts[size++] = bankAccount;
    }

    void removeBankAccount(const char* number) { // Removes only the first account with this number
        for (int i = 0; i < size; i++) {
            if (strcmp(bankAccounts[i].getBankAccountNumber(), number) == 0) {
                shiftLeft(i);
                size--;
                return;
            }
        }
    }

    double getBankAccountBalance(const char* number) const {
        for (int i = 0; i < size; i++) {
            if (strcmp(bankAccounts[i].getBankAccountNumber(), number) == 0) {
                return bankAccounts[i].getBankAccountBalance();
            }
        }

        std::cerr << "Account was not found";
        return 0;
    }

    double getClientBalance(const char* name) const {
        double res = 0;
        bool found = false;;

        for (int i = 0; i < size; i++) {
            if (strcmp(bankAccounts[i].getBankAccountName(), name) == 0) {
                res += bankAccounts[i].getBankAccountBalance();
                found = true;
            }
        }

        if (!found) {
            std::cerr << "Account was not found";
        }

        return res;
    }

    void saveBankInfoToFile(std::ofstream& ofs) const {
        if (!ofs.is_open()) {
            std::cerr << "Saving bank information to file was unsuccessful";
            return;
        }

        for (int i = 0; i < size; i++) {
            bankAccounts[i].writeBankAccountToFile(ofs);
        }
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            bankAccounts[i].print(std::cout);
        }
    }

    ~Bank() {
        delete[] bankAccounts;
    }

private:
    BankAccount* bankAccounts;
    int size;
    int capacity;

    int roundToPowerOfTwo(int num) const {
        num--;
        num |= num >> 1;
        num |= num >> 2;
        num |= num >> 4;
        num |= num >> 8;
        num |= num >> 16;
        num++;
        return num;
    }

    void resize(int newCap) {
        capacity = newCap;

        BankAccount* temp = new BankAccount[capacity];

        for (int i = 0; i < size; i++) {
            temp[i] = bankAccounts[i];
        }

        delete[] bankAccounts;

        bankAccounts = temp;
    }

    void shiftLeft(int index) {
        for (int i = index; i < size - 1; i++) {
            bankAccounts[i] = bankAccounts[i + 1];
        }
    }
};


int main() {

}