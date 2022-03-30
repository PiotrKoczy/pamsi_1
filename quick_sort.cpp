#include <iostream>
#include <fstream>
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

void quickSort(int array[], int leftIDX, int rightIDX)
{
    int finger = leftIDX;
    int border = leftIDX;
    int pivot = rightIDX;
    for (finger; finger < pivot; finger++)
    {
        if (array[finger] > array[pivot])
            finger++;
        if (array[finger] < array[pivot])
        {
            swap(array[finger], array[border + 1]);
            border++;
            finger++;
        }
        else
        {
            swap(array[border], array[pivot]);

            if (leftIDX < border - 1)
                quickSort(array, leftIDX, border - 1);
            if (border + 1 < rightIDX)
                quickSort(array, border + 1, rightIDX);
        }
    }
}

// Funkcja main, sortuje oraz zapisuje dane do pliku
int main()
{

    int size = SIZE;
    int testArray[size];
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 10 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }

    printArray(testArray, size);
    quickSort(testArray, 0, size-1);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}