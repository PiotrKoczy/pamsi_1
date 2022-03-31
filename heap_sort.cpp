#include <iostream>
#include <fstream>
#include <random>
#define SIZE 10 // Liczba elementów do posortowania
using namespace std;

// Wypisywanie tablicy do konsoli
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

// Wypisywanie tablicy do pliku
void printArrayToFile(int array[], int size, char filename[])
{
    ofstream plikwy;
    plikwy.open(filename);
    for (int i = 0; i < size; i++)
        plikwy << array[i] << "," << endl;
    plikwy.close();
}

int largest(int array[], int parentID)
{
    int largest;
    int i = parentID;
    int root = array[i];
    int child;
    if ((2 * i + 1 < SIZE) && (2 * i + 2 < SIZE))
    {
        largest = max(array[2 * i + 1], array[2 * i + 2]);
        if (largest == array[2 * i + 1])
            child = 2 * i + 1;
        else
            child = 2 * i + 2;
    }
    else if (2 * i + 2 == SIZE - 1)
    {
        largest = array[2 * i + 2];
        child = 2 * i + 2;
    }
    else if (2 * i + 1 == SIZE - 1)
    {
        largest = array[2 * i + 1];
        child = 2 * i + 1;
    }
    else
        return NULL;
    return child;
}

void heapSort(int array[], int size)
{
    int parentID;
    for (int i = size - 1; i > 0; i--)
    {
        if ((i - 1) % 2 == 0)
            parentID = (i - 1) / 2;
        else
            parentID = (i - 2) / 2;

        int largestChild = largest(array, parentID);

        int tmp1 = array[parentID];
        int tmp2 = array[largestChild];
        if (array[parentID] < array[largestChild])
            swap(array[parentID], array[largestChild]);
        printArray(array, size);
    }
}

int main()
{
    srand(1);
    int size = SIZE;
    // int testArray[size]; // 4 7 8 6 4 6 7 3 10
    // int testArray2[size];
    // for (int i = 0; i < size; i++)
    // {
    //     int number = rand() % 10 + 1;
    //     testArray[i] = number;
    //     testArray2[i] = number;
    // }
    // int testArray[] = {9, 1, 2, 4, 5, 7, 8, 6, 3};
    // int testArray[] = {4,7,8,6,4,6,7,5,10};
    int testArray[] = {9, 7, 4, 3, 6, 5, 1, 2, 8, 11};

    printArray(testArray, size);
    heapSort(testArray, size);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}