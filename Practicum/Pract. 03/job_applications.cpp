#include <iostream>
#include <fstream>
#include <sstream>

namespace CONSTANTS
{
	constexpr size_t COMPANY_NAME_MAX_SIZE = 20;
	constexpr size_t BUFFER_MAX_SIZE = 1024;
}

struct JobApp
{
	char companyName[CONSTANTS::COMPANY_NAME_MAX_SIZE]{};
	size_t programmersSize = 0;
	long long salary = 0;
};

JobApp readApp()
{
	char buff[CONSTANTS::BUFFER_MAX_SIZE]{};
	std::cin.getline(buff, CONSTANTS::BUFFER_MAX_SIZE);

	std::stringstream ss(buff);

	JobApp app;
	ss >> app.companyName >> app.programmersSize >> app.salary;
	return app;
}

JobApp* readAppArr(size_t n)
{
	JobApp* apps = new JobApp[n]{};
	for (size_t i = 0; i < n; i++)
	{
		apps[i] = readApp();
	}

	return apps;
}

void saveAppArrToBinary(std::ofstream& outFile, const JobApp* apps, size_t n)
{
	outFile.write((const char*)apps, sizeof(JobApp) * n);
}

void saveAppArrToBinary(const char* fileName, const JobApp* apps, size_t n)
{
	if (!fileName || !apps || n == 0)
	{
		return;
	}

	std::ofstream outFile(fileName, std::ios::binary | std::ios::app);
	if (!outFile.is_open())
	{
		return;
	}

	saveAppArrToBinary(outFile, apps, n);
	outFile.close();
}

void filterOffers(std::ifstream& inFile, std::ofstream& outFile, long long minSalary)
{
	while (true)
	{
		JobApp app;
		inFile.read((char*)&app, sizeof(JobApp));

		if (inFile.eof())
		{
			break;
		}

		if (app.salary >= minSalary)
		{
			outFile.write((const char*)&app, sizeof(JobApp));
		}
	}
}

void filterOffers(const char* from, const char* to, long long minSalary)
{
	if (!from || !to)
	{
		return;
	}

	std::ifstream inFile(from, std::ios::binary);
	std::ofstream outFile(to, std::ios::binary | std::ios::app);
	if (!inFile.is_open() || !outFile.is_open())
	{
		return;
	}

	filterOffers(inFile, outFile, minSalary);
	inFile.close();
	outFile.close();
}

bool existOffer(std::ifstream& inFile, const char* companyName)
{
	while (true)
	{
		JobApp app;
		inFile.read((char*)&app, sizeof(JobApp));

		if (inFile.eof())
		{
			break;
		}

		if (!strcmp(app.companyName, companyName))
		{
			return true;
		}
	}

	return false;
}

bool existOffer(const char* fileName, const char* companyName)
{
	if (!fileName || !companyName)
	{
		return false;
	}

	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile.is_open())
	{
		return false;
	}

	return existOffer(inFile, companyName);
}


void freeAppArr(JobApp*& apps, size_t& n)
{
	delete[] apps;
	apps = nullptr;

	n = 0;
}

int main()
{
	//size_t n;
	//std::cin >> n;
	//std::cin.ignore(); // '\n'

	//JobApp* apps = readAppArr(n);
	
	size_t n = 3;
	JobApp apps[3] = {
		{"companyAAA", 30, 30},
		{"companyBBB", 30, 300},
		{"companyCCC", 30, 3000},
	};
	
	saveAppArrToBinary("apps.bin", apps, n);
	filterOffers("apps.bin", "filtered.bin", 100);

	std::cout << existOffer("filtered.bin", "companyBBB") << std::endl; // True
	std::cout << existOffer("filtered.bin", "companyAAA") << std::endl; // False

	//freeAppArr(apps, n);

	return 0;
}
