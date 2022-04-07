#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#define SIZE 500000 // Liczba elementów do posortowania

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
    if (topID != parentID)
    {
        swap(array[topID], array[parentID]);
        doMaxHeap(array, size, topID);
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

int generatePivotValue(int array[], int leftIDX, int rightIDX)
{
    int mid = leftIDX + (rightIDX - leftIDX) / 2;
    return array[mid];
}

int quickSort(int array[], int size)
{
    static int MAXiteration = 2 * log(size) / M_LN2;
    static int iteration = 0;
    iteration++;
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

        if (iteration >= MAXiteration)
        {
            heapSort(array, size);
            iteration = 0;
        }
        else
        {
            quickSort(array, rightIDX + 1);             // od lewej krawędzi do pierwszej nieuporządowanej liczby
            quickSort(&array[leftIDX], size - leftIDX); // od pierwszej nieuporządkowanej liczby do prawej krawędzi
        }
    }
}

void introSort(int array[], int size)
{
    quickSort(array, size);
}

void printResultToFile(int number, int size, float time, string filename)
{
    ofstream plikwy;
    plikwy.open(filename, std::ios_base::app);
    plikwy << number << "," << time << endl;
    plikwy.close();
}

void test(int array[], int size, string filename, int idx)
{
    auto start = std::chrono::high_resolution_clock::now();
    introSort(array, size);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    printResultToFile(idx + 1, size, elapsed.count(), filename);
}

void generateRandom(int testArray[], int size, int seed)
{
    srand(seed);
    for (int i = 0; i < size; i++)
    {
        int number = rand() % size + 1;
        testArray[i] = number;
    }
}

void copyArray(int randomArray1[], int randomArray2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        randomArray1[i] = randomArray2[i];
    }
}

void reverseArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        swap(array[i],array[size-i]);
    }
}

int main()
{
    int testArray[SIZE];
    int randomArray[SIZE];
    int size = SIZE;
    int size_array[4]={10000,50000,100000,500000};
    std::string result;
    int c=sizeof(size_array)/sizeof(size_array[0]);
    for (int a = 0; a < c; a++)
    {
    
    for (int i = 0; i < 100; i++)
    {
        generateRandom(randomArray, size_array[a], i);
        copyArray(testArray, randomArray, size_array[a]);
        result = "wyn_introsort_fullrng_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] / 4);
        result = "wyn_introsort_25_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] / 2);
        result = "wyn_introsort_50_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] * 0.75);
        result = "wyn_introsort_75_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);
        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] * 0.95);
        result = "wyn_introsort_95_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] * 0.99);
        result = "wyn_introsort_99_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        introSort(testArray, size_array[a] * 0.997);
        result = "wyn_introsort_99_7_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);

        copyArray(testArray, randomArray, size_array[a]);
        reverseArray(testArray, size_array[a]);
        result = "wyn_introsort_reverse_" + std::to_string(size_array[a]) + ".csv";
        test(testArray, size_array[a], result, i);
    }
    }
    return 0;
}