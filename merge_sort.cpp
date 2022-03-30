// Merge sort in C++

#include <iostream>
#include <fstream>
#include "merge_sort.h"
#define SIZE 1000 // Liczba elementów do posortowania
using namespace std;

// Print the array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

void printArrayToFile(int array[], int size, char filename[])
{
    ofstream plikwy;
    plikwy.open(filename);
    for (int i = 0; i < size; i++)
        plikwy << array[i] << "," << endl;
    plikwy.close();
}

void merge(int array[], int leftIDX, int middleIDX, int rightIDX)
{
    static int extraArray[SIZE];
    for (int i = leftIDX; i <= rightIDX; i++)
    {
        extraArray[i] = array[i];
    }
    int finger1 = leftIDX;
    int finger2 = middleIDX + 1;
    int current = leftIDX;

    while (finger1 <= middleIDX && finger2 <= rightIDX)
    {
        if (extraArray[finger1] <= extraArray[finger2])
        {
            array[current] = extraArray[finger1];
            finger1++;
        }
        else
        {
            array[current] = extraArray[finger2];
            finger2++;
        }
        current++;
    }
    while (finger1 <= middleIDX)
    {
        array[current] = extraArray[finger1];
        current++;
        finger1++;
    }
};

void mergeSort(int array[], int leftIDX, int rightIDX)
{
    if (leftIDX < rightIDX)
    {
        int middleIDX = (leftIDX + rightIDX) / 2;
        mergeSort(array, leftIDX, middleIDX);
        mergeSort(array, middleIDX + 1, rightIDX);
        merge(array, leftIDX, middleIDX, rightIDX);
    }
};

// Driver program
int main()
{

    int size = SIZE;
    int testArray[size];
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 100000 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }

    printArray(testArray, size);
    mergeSort(testArray, 0, size + 1);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}