#include <iostream>
#include <fstream>
#include <random>
#define SIZE 1000 // Liczba elementów do posortowania
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
        // printArray(array, SIZE);
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
    for (int done_nr = 1; done_nr < size - 1; done_nr++)
    {
        swap(array[0], array[size - done_nr]);
        // printArray(array, size);
        for (int parentID = 0; parentID < SIZE - (done_nr + 1); parentID++)
        {
            swapWithBiggerChild(array, parentID, done_nr);
            // printArray(array, size);
        }
    }
    // printArray(array, size);
}

int generatePivotValue(int array[], int leftIDX, int rightIDX)
{
    int mid = leftIDX + (rightIDX - leftIDX) / 2;
    return array[mid];
}

int quickSort(int array[], int size)
{
    static int iteration = 0;
    if (iteration < 5)
    {
        iteration++;
        int leftIDX = 0;
        int rightIDX = size - 1;
        printArray(array, size);
        if (leftIDX < rightIDX)
        {
            int pivotValue = generatePivotValue(array, leftIDX, rightIDX);
            while (leftIDX <= rightIDX)
            {
                printArray(array, size);
                while (array[leftIDX] < pivotValue)
                    leftIDX++;
                while (array[rightIDX] > pivotValue)
                    rightIDX--;
                if (leftIDX <= rightIDX) // ta nierówność jest spełniona jeśli po obu stronach znalazła się liczba do przestawienia
                {
                    if (array[leftIDX] != array[rightIDX])
                        swap(array[leftIDX], array[rightIDX]);
                    leftIDX++;
                    rightIDX--;
                }
            }
            quickSort(array, rightIDX + 1);             // od lewej krawędzi do pierwszej nieuporządowanej liczby
            quickSort(&array[leftIDX], size - leftIDX); // od pierwszej nieuporządkowanej liczby do prawej krawędzi
        }
    }
    return iteration;
}

void introSort(int array[], int size)
{
    if (quickSort(array, size) == 5)
    {
        heapSort(array, size);
        endHeapSort(array, size);
    }
}

int main()
{
    srand(1);
    int size = SIZE;
    int testArray[size]; // 4 7 8 6 4 6 7 3 10
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 100 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }
    // int testArray[] = {9, 1, 2, 4, 5, 7, 8, 6, 3};
    // int testArray[] = {4,7,8,6,4,6,7,5,10,69};
    // int testArray[] = {9, 7, 4, 3, 6, 5, 1, 2, 8, 11};

    // printArray(testArray, size);
    introSort(testArray, size);
    cout << "Sorted introsort: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}