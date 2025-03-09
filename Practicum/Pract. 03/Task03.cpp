#include <iostream>
#include <fstream>

namespace CONSTANTS{
    constexpr int NAME = 20;
}

bool compareStrings(const char *str1, const char*str2){
    if(!str1 || !str2) return false;

    while(*str1 && *str2){
        if(*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

size_t findFileSize(std:: ifstream& ifs){
    if(!ifs.is_open()) return 0;

    size_t currPos = ifs.tellg();
    ifs.seekg(0, std:: ios:: end);
    size_t size = ifs.tellg();
    ifs.seekg(currPos,std:: ios:: beg);
    return size;
}

struct Offer{
    char name [CONSTANTS:: NAME];
    int number;
    long long salary;
};

void readOffer(Offer& offer){
    std:: cin >> offer.name >> offer.number >> offer.salary ;
}

void readOffersArray(Offer* offers, int N){
    for (int i = 0; i < N; i++){
        readOffer(offers[i]);
    }
}

void printToFile(std:: ofstream& ofs, const Offer *offers, int n){
    if(!ofs.is_open()) return;

    ofs.seekp(0, std:: ios:: end);
    ofs.write((const char*) offers, n * sizeof(Offer));
}

void filterOffers(const char* filePath, long long minSalary){
    std:: ifstream ifs (filePath, std:: ios:: binary);
    std:: ofstream ofs("filteredOffers.dat", std:: ios:: binary);
    if(!ifs.is_open() || !ofs.is_open()) return; 

   Offer offer;
    while(ifs.read((char*) &offer, sizeof(Offer))){
        if(offer.salary >= minSalary) 
        ofs.write((char*)&offer, sizeof(Offer));
    }
    ifs.close();
    ofs.close();

}

void readFile(std:: ifstream& ifs ){
    if(!ifs.is_open()) return;

    size_t size = findFileSize(ifs) / sizeof(Offer);
    Offer offer;
    while(ifs.read((char*)&offer, sizeof(Offer))){
        std:: cout <<  offer.name << " " << offer.number << " " << offer.salary << std:: endl; 
    }

}

bool existOffer (const char* filePath, const char* name){
    std:: ifstream ifs(filePath, std:: ios:: binary);
    if(!ifs.is_open()) return false;
    
    size_t size = findFileSize(ifs)/ sizeof(Offer);
    Offer offer;
    ifs.seekg(0, std::ios:: beg);
    for (int i = 0; i < size; i++){
        ifs.seekg(i*sizeof(Offer), std:: ios:: beg);
        ifs.read((char*)&offer, sizeof(Offer));
        if(compareStrings(offer.name, name)) return true;
    }
    return false;
}

int main(){
    // int n;
    // std:: cout << "n: ";
    // std:: cin >> n;

    // Offer * offers = new Offer[n];
    // readOffersArray(offers, n);
    
    // std:: ofstream ofs("firms.dat", std:: ios:: binary);
    // printToFile(ofs,offers,n);
    // ofs.close();
    // delete[] offers;
    // filterOffers("firms.dat", 1500);
    
    // std:: ifstream ifs("filteredOffers.dat", std:: ios:: binary);
    // std:: ifstream ifs("firms.dat", std:: ios::binary);
    // readFile(ifs);

   
    // std:: cout << existOffer("firms.dat", "Apple");
    //
    
}