#include <iostream>
#include <sstream>

namespace CONSTANTS{
    constexpr int BUFFER_MAX=1024;
    constexpr int MAX_INT=2147483647;
};


int findSum(std:: stringstream& ss){
    int number, sum = 0;
    while(ss >> number){
        sum += number;
    }
    return sum;
}

double findArithmeticMean(std:: stringstream& ss){
    double number,count = 0,  sum = 0;
    while(ss >> number){
        sum+=number;
        count++;
    }
    ss.clear();  
    ss.seekg(0,std::ios::beg);
    return (double)sum / count;
}

void findMaxandMinNumber(std:: stringstream &ss, int& maxN, int& minN){
    int number;
    while (ss >> number ){
        maxN = (maxN < number) ? number : maxN;

        minN = (minN > number) ? number : minN;
        
    }
    ss.clear();  
    ss.seekg(0,std::ios::beg);

}

int main(){
    // char buffer[CONSTANTS::BUFFER_MAX];
    // std:: cin.getline(buffer,CONSTANTS::BUFFER_MAX);
    // std:: stringstream ss(buffer);
    //std:: cout << findSum(ss);
    //std:: cout << findArithmeticMean(ss);
    //int maxN=0,minN = CONSTANTS:: MAX_INT;
    //findMaxandMinNumber(ss,maxN,minN);
    //std:: cout << maxN << " " << minN;
    //
}
