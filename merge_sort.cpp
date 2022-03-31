
#include <iostream>
#include <fstream>
#include <random>
#include <chrono> 
#include "merge_sort.h"
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

//Funkcja odpowiedzialna za sortowanie tablicy. Otrzymuje informacje o położeniu "lewej" i "prawej" części tablicy, które sortując scala.
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

//Funkcja odpowiedzialna za rekurencyjne dzielenie problemu na mniejsze a następnie przekazywanie danych do funkcji merge.
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

//Funkcja main, sortuje oraz zapisuje dane do pliku
int main()
{
    srand(1);
    int size = SIZE;
    int testArray[size]; // 4 7 8 6 4 6 7 3 10
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 100000 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }

    printArray(testArray, size);
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(testArray, 0, size + 1);
    auto finish = std::chrono::high_resolution_clock::now();

    cout << "Sorted array: \n";
    printArray(testArray, size);
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}