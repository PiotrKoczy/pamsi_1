#include <iostream>
#include <fstream>
#include <random>
#define SIZE 10 // Liczba elementów do posortowania
using namespace std;

// Wypisywanie tablicy do konsoli
void printArray(int array[], int size)
{
    for (int parentID = 0; parentID < size; parentID++)
        cout << array[parentID] << " ";
    cout << endl;
}

// Wypisywanie tablicy do pliku
void printArrayToFile(int array[], int size, char filename[])
{
    ofstream plikwy;
    plikwy.open(filename);
    for (int parentID = 0; parentID < size; parentID++)
        plikwy << array[parentID] << "," << endl;
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
    for (int parentID = size - 1; parentID > 0; parentID--)
    {
        if ((parentID - 1) % 2 == 0)
            parentID = (parentID - 1) / 2;
        else
            parentID = (parentID - 2) / 2;

        int largestChildID = findLargestChild(array, parentID);

        int tmp1 = array[parentID];
        int tmp2 = array[largestChildID];
        if (array[parentID] < array[largestChildID])
            swap(array[parentID], array[largestChildID]);
        //printArray(array, size);
    }
}

void swapWithBiggerChild(int array[], int parentID, int done_nr)
{
    int largestChildID = findLargestChild(array, parentID);
    if (largestChildID > 0)
    {
        int tmp1 = parentID;
        int tmp2 = largestChildID;
        if (largestChildID < SIZE - done_nr)
            swap(array[parentID], array[largestChildID]);
        //printArray(array, SIZE);
        swapWithBiggerChild(array, largestChildID, done_nr);
    }
}

void endHeapSort(int array[], int size)
{
    int parentID;
    int finalArray[size];
    for (int done_nr = 1; done_nr < size; done_nr++)
    {
        swap(array[0], array[size - done_nr]);
        for (int parentID = 0; parentID < SIZE - done_nr; parentID++)
        {
            swapWithBiggerChild(array, parentID, done_nr);
            //printArray(array, size);
        }
    }
    printArray(array, size);
}

int main()
{
    srand(1);
    int size = SIZE;
    // int testArray[size]; // 4 7 8 6 4 6 7 3 10
    // int testArray2[size];
    // for (int parentID = 0; parentID < size; parentID++)
    // {
    //     int number = rand() % 10 + 1;
    //     testArray[parentID] = number;
    //     testArray2[parentID] = number;
    // }
    // int testArray[] = {9, 1, 2, 4, 5, 7, 8, 6, 3};
    // int testArray[] = {4,7,8,6,4,6,7,5,10};
    int testArray[] = {9, 7, 4, 3, 6, 5, 1, 2, 8, 11};

    printArray(testArray, size);
    heapSort(testArray, size);
    cout << "Sorted heapSort: \n";
    printArray(testArray, size);
    endHeapSort(testArray, size);

    cout << "Sorted endHeapSort: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}