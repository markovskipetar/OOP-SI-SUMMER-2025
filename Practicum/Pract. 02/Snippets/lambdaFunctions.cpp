#include <iostream>
#include <fstream>

bool descendingOrder(int a, int b)
{
	return (a > b);
}

bool ascendingOrder(int a, int b)
{
    return (a < b);
}

void selectionSort(int* arr, size_t size, bool(*predicate)(int, int)) 
{
    for (size_t i = 0; i < size - 1; i++) 
    {
        size_t bestIndex = i;

        for (size_t j = i + 1; j < size; j++) 
        {
            if (predicate(arr[j], arr[bestIndex])) 
            {
                bestIndex = j;
            }
        }

        if (bestIndex != i) 
        {
            std::swap(arr[i], arr[bestIndex]);
        }
    }
}

void printArr(const int* arr, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    
    std::cout << std::endl;
}

int main()
{
    constexpr size_t SIZE = 5;

    int arr[SIZE] = {4, 2, 5, 1, 3};
    std::cout << "Unsorted: ";
    printArr(arr, SIZE);

    selectionSort(arr, SIZE, ascendingOrder);
    std::cout << "Ascending: ";
    printArr(arr, SIZE);
   
    selectionSort(arr, SIZE, [](int a, int b) -> bool {return a < b;});
    std::cout << "Ascending with lambda: ";
    printArr(arr, SIZE);
    
    selectionSort(arr, SIZE, descendingOrder);
    std::cout << "Descending: ";
    printArr(arr, SIZE);

    bool(*func)(int, int) = [](int a, int b) {return a < b; };
}
