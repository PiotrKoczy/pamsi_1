
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

// Funkcja odpowiedzialna za sortowanie tablicy. Otrzymuje informacje o położeniu "lewej" i "prawej" części tablicy, które sortując scala.
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

// Funkcja odpowiedzialna za rekurencyjne dzielenie problemu na mniejsze a następnie przekazywanie danych do funkcji merge.
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
    mergeSort(array, 0, size + 1);
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
        swap(array[i], array[size - i]);
    }
}

int main()
{
    int testArray[SIZE];
    int randomArray[SIZE];
    int size = SIZE;
    int size_array[5] = {10000, 50000, 100000, 500000, 1000000};
    std::string result;
    int c = sizeof(size_array) / sizeof(size_array[0]);
    for (int a = 0; a < c; a++)
    {

        for (int i = 0; i < 100; i++)
        {
            generateRandom(randomArray, size_array[a], i);
            copyArray(testArray, randomArray, size_array[a]);
            result = "wyn_mergesort_fullrng_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] / 4);
            result = "wyn_mergesort_25_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] / 2);
            result = "wyn_mergesort_50_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] * 0.75);
            result = "wyn_mergesort_75_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] * 0.95);
            result = "wyn_mergesort_95_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] * 0.99);
            result = "wyn_mergesort_99_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            mergeSort(testArray, 0, size_array[a] * 0.997);
            result = "wyn_mergesort_99_7_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);

            copyArray(testArray, randomArray, size_array[a]);
            reverseArray(testArray, size_array[a]);
            result = "wyn_mergesort_reverse_" + std::to_string(size_array[a]) + ".csv";
            test(testArray, size_array[a], result, i);
        }
    }
    return 0;
}

// // Funkcja main, sortuje oraz zapisuje dane do pliku
// int main()
// {
//     for (int i = 0; i < 100; i++)
//     {
//         srand(i);
//         int size = SIZE;
//         int testArray[size]; // 4 7 8 6 4 6 7 3 10
//         int testArray2[size];
//         for (int i = 0; i < size; i++)
//         {
//             int number = rand() % SIZE + 1;
//             testArray[i] = number;
//         }
//         mergeSort(testArray, 0, size+1);
//         // printArray(testArray, size);
//         auto start = std::chrono::high_resolution_clock::now();
//         mergeSort(testArray, 0, size + 1);
//         auto finish = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> elapsed = finish - start;
//         std::cout << "Elapsed time: " << elapsed.count() << " s\n";
//         //printResultToFile(i + 1, size, elapsed.count(), "merge_sort-wyniki.txt");
//     }
//     return 0;
// }