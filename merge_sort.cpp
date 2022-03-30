// Merge sort in C++

#include <iostream>
#include <merge_sort.h>
using namespace std;


// Print the array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

class MergeSort
{
private:
    static int* extraArray;
    static void mergeSort(int array[], int leftIDX, int rightIDX)
    {
        if (leftIDX < rightIDX)
        {
            int middleIDX = (leftIDX + rightIDX) / 2;
            mergeSort(array, leftIDX, middleIDX);
            mergeSort(array, middleIDX + 1, rightIDX);
            merge(array, leftIDX, middleIDX, rightIDX);
        }
    }
    static void merge(int array[], int leftIDX, int middleIDX, int rightIDX)
    {
        for (int i = leftIDX; i <= rightIDX; i++)
        {
            extraArray[i] = array[i];
        }
        int finger1, current = leftIDX;
        int finger2 = middleIDX + 1;

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
    }

public:
    static void sort(int arrayToSort[],int size)
    {
        extraArray[size];
        mergeSort(arrayToSort, 0, size - 1);
    }
};

// Driver program
int main()
{
    int size = 10;
    int testArray[size];
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 100 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }

    printArray(testArray, size);

    MergeSort::sort(testArray, size);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    return 0;
}