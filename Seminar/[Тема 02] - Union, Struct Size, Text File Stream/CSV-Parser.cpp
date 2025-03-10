#include <iostream>
#include <fstream>
#include <sstream>

namespace FilePreparation
{
	constexpr int lineItemsCount = 5;

	const char* line1[5] = { "FirstName", "LastName", "Fn", "Faculty", "City" };
	const char* line2[5] = { "Petar", "Petrov", "12345", "FMI", "Sofia" };
	const char* line3[5] = { "Ivan", "Ivanov", "54321", "FHF", "Sofia" };
	const char* line4[5] = { "Georgi", "Georgiev", "12399", "FZF", "Sofia" };
	const char* line5[5] = { "Dimitar", "Dimitrov", "99568", "FJMK", "Sofia" };

	void writeRowToCsvFile(std::ofstream& writer, const char* line[])
	{
		for (int i = 0; i < lineItemsCount - 1; i++)
		{
			writer << line[i] << ",";
		}

		writer << line[lineItemsCount - 1] << std::endl;
	}

	bool prepareCSVFile()
	{
		std::ofstream csvWriter("csvFile.csv");

		if (!csvWriter.good())
		{
			return false;
		}

		writeRowToCsvFile(csvWriter, line1);
		writeRowToCsvFile(csvWriter, line2);
		writeRowToCsvFile(csvWriter, line3);
		writeRowToCsvFile(csvWriter, line4);
		writeRowToCsvFile(csvWriter, line5);

		csvWriter.close();
		return true;
	}
}

namespace Constants
{
	constexpr int maxRowsCount = 32;
	constexpr int maxRowLength = 128;

	constexpr int maxValuesInRowCount = 8;
	constexpr int maxValueLength = 16;
}

typedef char Value[Constants::maxValueLength];

struct Row
{
	Value values[Constants::maxValuesInRowCount];
};

struct Table
{
	int rowsCount = 0;
	int valuesInRowCount = 0;

	Row rows[Constants::maxRowsCount];
};

int getValuesInRowCount(std::ifstream& csvReader)
{
	int initialCsvReaderPosition = csvReader.tellg();

	char dummyRowBuffer[Constants::maxRowLength];
	csvReader.getline(dummyRowBuffer, Constants::maxRowLength);

	std::stringstream ss(dummyRowBuffer);

	int valuesInRowCount = 0;

	while (!ss.eof())
	{
		char dummyValueBuffer[Constants::maxValueLength];

		ss.getline(dummyValueBuffer, Constants::maxValueLength, ',');

		valuesInRowCount++;
	}

	csvReader.clear(); // if we have only one line in the file, eof will be 1, so call clear to use seek() correctly
	csvReader.seekg(initialCsvReaderPosition);

	return valuesInRowCount;
}

int getFileRowsCount(std::ifstream& csvReader)
{
	int initialCsvReaderPosition = csvReader.tellg();

	int rowsCount = 0;

	while (true)
	{
		char symbol = csvReader.get();

		if (csvReader.eof())
		{
			break;
		}

		if (symbol == '\n')
		{
			rowsCount++;
		}
	}

	csvReader.clear(); // eof is 1, call clear to use seek() correctly
	csvReader.seekg(initialCsvReaderPosition);

	return rowsCount;
}

void getTableDimensions(Table& table, std::ifstream& csvReader)
{
	table.valuesInRowCount = getValuesInRowCount(csvReader);
	table.rowsCount = getFileRowsCount(csvReader);
}

void readRow(Row& tableRow, std::ifstream& csvReader)
{
	char rowBuffer[Constants::maxRowLength];
	csvReader.getline(rowBuffer, Constants::maxRowLength);

	std::stringstream ss(rowBuffer);

	int index = 0;

	while (!ss.eof())
	{
		ss.getline(tableRow.values[index], Constants::maxValueLength, ',');
		index++;
	}
}

void readCSVFile(Table& table, std::ifstream& csvReader)
{
	for (int i = 0; i < table.rowsCount; i++)
	{
		readRow(table.rows[i], csvReader);
	}
}

void printTable(const Table& table)
{
	for (int row = 0; row < table.rowsCount; row++)
	{
		const Row& tableRow = table.rows[row];

		for (int col = 0; col < table.valuesInRowCount; col++)
		{
			std::cout << tableRow.values[col] << ", ";
		}

		std::cout << std::endl;
	}
}

int main()
{
	if (!FilePreparation::prepareCSVFile())
	{
		std::cout << "Stream for csv file preparation failed!" << std::endl;
		return -1;
	}

	std::ifstream csvReader("csvFile.csv");

	if (!csvReader.is_open())
	{
		std::cout << "Stream for csv file reading failed!" << std::endl;
		return -1;
	}

	Table table;

	getTableDimensions(table, csvReader);

	readCSVFile(table, csvReader);

	csvReader.close();

	printTable(table);
}