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

void doMaxHeap(int array[], int size, int parentID)
{
    int topID = parentID;
    int leftChildID = parentID * 2 + 1;
    int rightChildID = parentID * 2 + 2;

    if (leftChildID < size && array[leftChildID] > array[topID])
        topID = leftChildID;
    if (rightChildID < size && array[rightChildID] > array[topID])
        topID = rightChildID;
    if(topID != parentID){
        swap(array[topID], array[parentID]);
        doMaxHeap(array,size,topID);
    }
}

void heapSort(int array[], int size)
{
    if (size == 0)
        return;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        doMaxHeap(array, size, i);
    }
    for (int i = size - 1; i > 0; i--)
    {
        swap(array[0], array[i]);
        size--;
        doMaxHeap(array, size, 0);
    }
}

void printResultToFile(int number, int size, float time, char filename[])
{
    ofstream plikwy;
    plikwy.open(filename,std::ios_base::app);
    plikwy << "Nr." << number << " Czas: " << time << "  Rozmiar: " << size << endl;
    plikwy.close();
}

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
        heapSort(testArray, size/2);
        // printArray(testArray, size);
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(testArray, size);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        //printResultToFile(i + 1, size, elapsed.count(), "new_heap_sort-wyniki.txt");
    }
    return 0;
}