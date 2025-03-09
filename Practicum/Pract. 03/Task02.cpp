#include <iostream> 
#include <fstream>


namespace CONSTANTS{
    constexpr int MAX_BUFFER =1024;
}

void readNumbers(int *arr, int N){
    if(!arr) return;

    for (int i = 0; i < N; i ++){
        std:: cin >> arr[i];
    }

}

void readFromFile(std :: ifstream& ifs, int N){
    if(!ifs.is_open()) return;

    int num;
    for (int i = 2; i < N; i += 3){
        ifs.seekg(i * sizeof(int), std::ios:: beg );
        ifs.read((char*)&num, sizeof(int));
        std:: cout << num << " ";
    }
    std:: cout << std:: endl;
}

int main(){
    int N;
    std:: cin >> N;
    if(N<=0){
        std:: cout << "INVALID INPUT SIZE!" << std:: endl;
        return 1;
    }
    int * arr = new int [N];
    readNumbers(arr,N);

    std::ofstream ofs ("input.dat", std:: ios:: binary);
    if(!ofs.is_open()) {
        std:: cout << "Error creating file!" << std:: endl;
        delete[] arr;
        return 1 ;
    }

    ofs.write( (const char*) arr, N*sizeof(int));
    ofs.close();

    std:: ifstream ifs ("input.dat", std:: ios:: binary);
    readFromFile(ifs, N);

    delete[] arr;

}
