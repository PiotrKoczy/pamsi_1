#include <iostream>
#include <fstream>
#include <random>
#include <chrono> 
#define SIZE 1000000 // Liczba elementów do posortowania
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

int findLargestChild(int array[], int parentID)
{
    int largest;
    int root = array[parentID];
    int i = parentID;
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
        return -1;
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

        int largestChildID = findLargestChild(array, parentID);

        int tmp1 = array[parentID];
        int tmp2 = array[largestChildID];
        if (array[parentID] < array[largestChildID])
            swap(array[parentID], array[largestChildID]);
        // printArray(array, size);
    }
}

void swapWithBiggerChild(int array[], int parentID, int done_nr)
{
    int largestChildID = findLargestChild(array, parentID);
    if (largestChildID > 0)
    {
        //printArray(array, SIZE);
        int tmp1IDX = parentID;
        int tmp2IDX = largestChildID;
        int tmp1 = array[parentID];
        int tmp2 = array[largestChildID];
        if ((largestChildID < SIZE - done_nr) && (array[largestChildID] > array[parentID]))
            swap(array[parentID], array[largestChildID]);
        // printArray(array, SIZE);
        swapWithBiggerChild(array, largestChildID, done_nr);
    }
}

void endHeapSort(int array[], int size)
{
    int parentID;
    int finalArray[size];
    for (int done_nr = 1; done_nr < size-1; done_nr++)
    {
        swap(array[0], array[size - done_nr]);
        for (int parentID = 0; parentID < SIZE - (done_nr+1); parentID++)
        {
            swapWithBiggerChild(array, parentID, done_nr);
        }
    }
}

int main()
{
    srand(1);
    int size = SIZE;
    int testArray[size]; // 4 7 8 6 4 6 7 3 10
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 1000 + 1;
        testArray[i] = number;
    }
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(testArray, size);
    endHeapSort(testArray, size);
    auto finish = std::chrono::high_resolution_clock::now();

    cout << "Sorted endHeapSort: \n";
    printArray(testArray, size);
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}