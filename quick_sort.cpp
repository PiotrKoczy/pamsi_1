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



// void quickSort(int array[], int leftIDX, int rightIDX)
// {
//     int extraArray[SIZE];
//     int finger = leftIDX;
//     int border = leftIDX - 1;
//     int pivot = generatePivotValue(array,leftIDX,rightIDX);
//     //int pivot = array[rightIDX];
//     if (leftIDX < rightIDX)
//     {
//         while (finger < rightIDX)
//         {
//             if (array[finger] < pivot)
//             {
//                 border++;
//                 if (border != finger)
//                     swap(array[finger], array[border]);
//             }
//             finger++;
//             printArray(array, SIZE);
//         }
//         border++;
//         if (border != rightIDX)
//         {
//             swap(array[rightIDX], array[border]);
//         }
//         quickSort(array, leftIDX, border - 1);
//         quickSort(array, border + 1, rightIDX);
//     }
// }

int generatePivotValue(int array[], int leftIDX, int rightIDX)
{
    int mid = leftIDX + (rightIDX - leftIDX) / 2;
    return array[mid];
}

void quickSort(int array[], int size)
{
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
        quickSort(array, rightIDX + 1); //od lewej krawędzi do pierwszej nieuporządowanej liczby
        quickSort(&array[leftIDX], size - leftIDX); //od pierwszej nieuporządkowanej liczby do prawej krawędzi
    }
}

// Funkcja main, sortuje oraz zapisuje dane do pliku
int main()
{
    srand(1);
    int size = SIZE;
    int testArray[] = {0, 1, 2, 3, 4, 5, 7, 5, 10};

    printArray(testArray, size);
    quickSort(testArray, size);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}