#include <iostream>
#include <fstream>
#include <random>
#define SIZE 9 // Liczba elementów do posortowania
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

int middleOfThree(int a, int b, int c)
{
    // Checking for b
    if ((a < b && b < c) || (c < b && b < a))
        return b;

    // Checking for a
    else if ((b < a && a < c) || (c < a && a < b))
        return a;

    else
        return c;
}

int generatePivotValue(int array[], int leftIDX, int rightIDX){
    int mid = leftIDX+(rightIDX-leftIDX)/2;
    swap(array[mid],array[rightIDX]); //14:50 po co??
    return array[mid];
}

void quickSort(int array[], int leftIDX, int rightIDX)
{
    int extraArray[SIZE];

    int finger = leftIDX;
    int border = leftIDX - 1;

    int pivot = generatePivotValue(array,leftIDX,rightIDX);
    //int pivot = array[rightIDX];
    if (leftIDX < rightIDX)
    {
        while (finger < rightIDX)
        {
            if (array[finger] < pivot)
            {
                border++;
                if (border != finger)
                    swap(array[finger], array[border]);
            }
            finger++;
            printArray(array, SIZE);
        }
        border++;
        if (border != rightIDX)
        {
            swap(array[rightIDX], array[border]);
        }
        quickSort(array, leftIDX, border - 1);
        quickSort(array, border + 1, rightIDX);
    }
}

// Funkcja main, sortuje oraz zapisuje dane do pliku
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
    int testArray[] = {9, 1, 2, 4, 5, 7, 8, 6, 3};

    printArray(testArray, size);
    quickSort(testArray, 0, size - 1);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}