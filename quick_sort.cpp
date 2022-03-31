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
    // printArray(array, size);
    if (leftIDX < rightIDX)
    {
        int pivotValue = generatePivotValue(array, leftIDX, rightIDX);
        while (leftIDX <= rightIDX)
        {
            // printArray(array, size);
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

void printResultToFile(int number, int size, float time, char filename[])
{
    ofstream plikwy;
    plikwy.open(filename,std::ios_base::app);
    plikwy << "Nr." << number << " Czas: " << time << "  Rozmiar: " << size << endl;
    plikwy.close();
}

// Funkcja main, sortuje oraz zapisuje dane do pliku
int main()
{
    for (int i = 0; i < 100; i++)
    {
        srand(i);
        int size = SIZE;
        int testArray[size]; // 4 7 8 6 4 6 7 3 10
        int testArray2[size];
        for (int i = 0; i < size; i++)
        {
            int number = rand() % SIZE + 1;
            testArray[i] = number;
            testArray2[i] = number;
        }

        // printArray(testArray, size);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(testArray, size);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        printResultToFile(i + 1, size, elapsed.count(), "quick_sort-wyniki.txt");
    }
    return 0;
}