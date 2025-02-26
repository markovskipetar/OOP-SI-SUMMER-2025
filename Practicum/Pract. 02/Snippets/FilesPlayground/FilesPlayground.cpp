#include <iostream>

//Trqbva ni za rabota s file-ove
#include <fstream>

namespace Files
{
    const char* FILE1_NAME = "file1.txt";
    const char* FILE2_NAME = "file2.txt";
    const char* FILE3_NAME = "file3.txt";
    const size_t BUFFER_SIZE = 1024;
}

void writeNumberToFileExample()
{
    //Otvarqme nov potok za pisane i mu zadavame imeto na file-a
    std::ofstream outputFile(Files::FILE1_NAME);

    //Zaduljitelno vinagi kato otvarqme nov potok trqbva da napravim
    //proverka dali se e otvoril uspeshno
    if (!outputFile.is_open())
    {
        //davame nqkakvo suobshtenie za greshka
        std::cout << "Error with file: " << Files::FILE1_NAME << std::endl;
        return;
    }

    int num = 4;
    //Izpolzvame formatiran vhod
    outputFile << num;
    
    //Mojem da si predstavqme che outputFile e sushtoto kato cout
    //vsichko koeto mojem da pravim sus cout mojem i s outputFile
    
    outputFile << ' ';

    outputFile << num;

    //Sudurjanieto na file-a shte e "<stoinost na num> <stoinost na num>"

    //Operatorite << i >> vrushtat potok za tova mojem da gi chain-vame
    outputFile << num << ' ' << num;
}

void readNumberFromFileExample()
{
    std::ifstream inputFile(Files::FILE2_NAME);

    if (!inputFile.is_open())
    {
        std::cout << "Error with file: " << Files::FILE2_NAME << std::endl;
        return;
    }

    int num;

    inputFile >> num;
}

//Printira sudurjanieto na file vurhu konzolata
void readFileExample()
{
    std::ifstream inputFile(Files::FILE1_NAME);

    if (!inputFile.is_open())
    {
        std::cout << "Error with file: " << Files::FILE1_NAME << std::endl;
        return;
    }

    char buffer[Files::BUFFER_SIZE];

    while (!inputFile.eof())
    {
        inputFile.getline(buffer, Files::BUFFER_SIZE);
        std::cout << buffer;
    }
}

void readNumberAndStringExample()
{
    std::ifstream inputFile(Files::FILE3_NAME);

    if (!inputFile.is_open())
    {
        std::cout << "Error with file: " << Files::FILE3_NAME << std::endl;
        return;
    }

    int num;
    char buffer[Files::BUFFER_SIZE];

    inputFile >> num;

    //Trqbva da se ignorne edin simvol zashtoto sled operator >> ukazatelqt e vurhu blank space 
    //ili vurhu simvol za nov red i ako e simvol za nov red togava shte stane problem 
    //zashtoto toi e default razdelitelq na getline
    inputFile.ignore();

    inputFile.getline(buffer, Files::BUFFER_SIZE);

    std::cout << "Number: " << num << " string: " << buffer;
}

int main()
{
    writeNumberToFileExample();
    readNumberAndStringExample();
}

