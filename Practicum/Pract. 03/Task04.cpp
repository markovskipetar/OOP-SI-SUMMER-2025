#include <iostream>
#include <fstream>

namespace CONSTANTS{
    constexpr int TITLE = 20;
    constexpr int AUTHOR = 20;
    
}

bool compareStrings(const char* str1, const char* str2){
    while(*str1 && *str2){
        if (*str1!= *str2) return false;
        str1++;
        str2++;
    }
    return (*str1==*str2);
}

struct Book {
    char title[CONSTANTS::TITLE];
    char author [CONSTANTS::AUTHOR];
    size_t year;
    size_t copies;
};

void addBook(std::ofstream& ofs){
    if(!ofs.is_open()) return;

    ofs.seekp(0,std::ios::end);
    Book b;
    std::cout << std:: endl;
    std:: cout << "Enter book's title, author, year, copies" << std:: endl;
    std::cin.ignore();
    std:: cin.getline(b.title,CONSTANTS:: TITLE);
    std:: cin.getline(b.author, CONSTANTS::AUTHOR);
   
    std:: cin >> b.year >> b.copies;

    ofs.write((char*) &b, sizeof(Book));
    
}

void printBooks(std::ifstream&ifs){
    if(!ifs.is_open()) return;

    Book b;
    while(ifs.read((char*)&b, sizeof(Book))){
        std :: cout << b.title << std:: endl;
        std :: cout << b.author << std:: endl;
        std :: cout << b.year << std:: endl;
        std :: cout << b.copies << std:: endl;
        std:: cout << "\n" << std:: endl;
    }
}

void findBookByName(std::ifstream& ifs, const char* name){
    if(!ifs.is_open()) return;

    Book b;
    while(ifs.read((char*)&b, sizeof(Book))){
        if(compareStrings(b.title, name)){
            std:: cout << b.title <<" "<< b.author << " " << b.year <<" "<< b.copies << std::endl;
        }
    }
}

int main(){
    // std:: ofstream ofs("books.dat", std:: ios :: binary | std:: ios:: ate | std::ios::in);
    // int size;
    // std:: cin >>size;
    // for (int i = 0; i < size; i++ ){
    //     addBook(ofs);
    // }
    // ofs.close();
    // std:: cout <<"\n\n";

    //  std:: ifstream ifs("books.dat", std:: ios:: binary);
    //  printBooks(ifs);

    // char name[1024]= "Persy Jackson";
    // findBookByName(ifs, name);
    //

}