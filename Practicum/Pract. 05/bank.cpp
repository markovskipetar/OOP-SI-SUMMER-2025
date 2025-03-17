#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

namespace CONSTANTS
{
	constexpr size_t NAME_MAX_SIZE = 15;
	constexpr size_t ACCOUNT_MAX_SIZE = 30;
	constexpr size_t BANK_DEFAULT_ACCOUNTS = 2;
}

class BankAccount
{
public:

	BankAccount() = default;

	BankAccount(const char* name, const char* number, double balance = 0)
	{
		setName(name);
		setNumber(number);
		setBalance(balance);
	}

	const char* getNumber() const
	{
		return number;
	}

	const char* getName() const
	{
		return name;
	}

	double getBalance() const
	{
		return balance;
	}

	void deposit(double ammount)
	{
		if (ammount < 0.0)
		{
			return;
		}

		balance += ammount;
	}

	void draw(double ammount)
	{
		if (ammount < 0.0)
		{
			return;
		}

		if (ammount > balance)
		{
			balance = 0.0;
			return;
		}

		balance -= ammount;
	}

	void print(std::ostream& os) const
	{
		os << "Bank Account:" << std::endl
			<< "Name: " << name << std::endl
			<< "Account Number: " << number << std::endl
			<< "Balance: " << balance << " BGN" << std::endl;
	}

private:

	void setName(const char* name)
	{
		if (!name || strlen(name) == 0)
		{
			return;
		}

		strcpy(this->name, name);
	}

	void setNumber(const char* number)
	{
		if (!number || strlen(number) == 0)
		{
			return;
		}

		strcpy(this->number, number);
	}

	void setBalance(double balance)
	{
		if (balance < 0.0)
		{
			this->balance = 0.0;
			return;
		}

		this->balance = balance;
	}

	char name[CONSTANTS::NAME_MAX_SIZE + 1]{};
	char number[CONSTANTS::ACCOUNT_MAX_SIZE + 1]{};
	double balance = 0.0;
};

class Bank
{
public:
	Bank(): accounts(0), size(0), capacity(2)     
	{
		accounts = new BankAccount[capacity];
	}

	Bank(const char* fileName)
	{
		readAccounts(fileName);
	}
	
	void addAccount(const BankAccount& account)
	{
		if (size >= capacity)
		{
			resize(2 * capacity);
		}

		accounts[size++] = account;
	}

	void removeAccount(const char* number)
	{
		if (!number)
		{
			return;
		}

		int removeAt = getAccountByNumber(number);
		if (removeAt == -1)
		{
			return;
		}
		
		std::swap(accounts[removeAt], accounts[size - 1]);
		size--;
	}

	double getBalanceByNumber(const char* number) const
	{
		if (!number)
		{
			return 0.0;
		}

		int getAt = getAccountByNumber(number);
		if (getAt == -1)
		{
			return 0.0;
		}

		return accounts[getAt].getBalance();
	}

	double getTotalBalanceOf(const char* name) const
	{
		if (!name)
		{
			return 0.0;
		}

		double sum = 0.0;
		for (size_t i = 0; i < size; i++)
		{
			if (!strcmp(accounts[i].getName(), name))
			{
				sum += accounts[i].getBalance();
			}
		}

		return sum;
	}

	void saveToBinary(const char* fileName) const
	{
		if (!fileName)
		{
			return;
		}

		std::ofstream outFile(fileName, std::ios::binary);
		if (!outFile.is_open())
		{
			return;
		}

		saveToBinary(outFile);
		outFile.close();
	}

	void print() const
	{
		std::cout << "[Bank]: " << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			accounts[i].print(std::cout);
		}
	}

	~Bank()
	{
		free();
	}

private:

	int getAccountByNumber(const char* number) const
	{
		if (!number)
		{
			return -1;
		}

		for (size_t i = 0; i < size; i++)
		{
			if (!strcmp(accounts[i].getNumber(), number))
			{
				return i;
			}
		}

		return -1;
	}

	int roundToPowerOfTwo(int num) const 
	{
		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		num++;

		return num;
	}

	size_t getSizeOfFile(std::ifstream& inFile) const
	{
		size_t curr = inFile.tellg();

		inFile.seekg(0, std::ios::end);
		size_t size = inFile.tellg();

		inFile.seekg(curr);
		return size;
	}

	size_t getSizeOfAccounts(std::ifstream& inFile) const
	{
		return getSizeOfFile(inFile) / sizeof(BankAccount);
	}

	void readAccounts(std::ifstream& inFile)
	{
		size = getSizeOfAccounts(inFile);
		capacity = roundToPowerOfTwo(size);
		accounts = new BankAccount[capacity];
		inFile.read((char*)accounts, size * sizeof(BankAccount));
	}

	void readAccounts(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ifstream inFile(fileName, std::ios::binary);
		if (!inFile.is_open())
		{
			return;
		}

		readAccounts(inFile);
		inFile.close();
	}

	void resize(size_t newCap)
	{

		BankAccount* newAccounts = new BankAccount[newCap]{};
		for (size_t i = 0; i < size; i++)
		{
			newAccounts[i] = accounts[i];
		}

		delete[] accounts;
		accounts = newAccounts;
		newAccounts = nullptr;

		capacity = newCap;
	}

	void saveToBinary(std::ofstream& outFile) const
	{
		outFile.write((const char*)accounts, size * sizeof(BankAccount));
	}

	void free()
	{
		delete[] accounts;
		accounts = nullptr;

		size = 0;
		capacity = 0;
	}

	BankAccount* accounts = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};

int main()
{

	BankAccount acc1("Momo", "BG123456789", 100.0);
	BankAccount acc2("Boris", "BG123456790", 102.0);
	BankAccount acc3("Petur", "BG123456791", 104.0);

	Bank bank;
	bank.addAccount(acc1);
	bank.addAccount(acc2);
	bank.addAccount(acc3);
	bank.saveToBinary("bank.bin");
	bank.print();

	Bank bank2("bank.bin");
	bank2.removeAccount("BG123456789");
	bank2.print();

	return 0;
}