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

void quickSort(int array[], int leftIDX, int rightIDX)
{
    int extraArray[SIZE];

    int finger = leftIDX;
    int border = leftIDX-1;
    random_device rd;                                    // obtain a random number from hardware
    mt19937 gen(rd());                                   // seed the generator
    uniform_int_distribution<> distr(leftIDX, rightIDX); // define the range
    int idx1 = distr(gen);
    int idx2 = distr(gen);
    int idx3 = distr(gen);
    

    int pivot = middleOfThree(idx1,idx2,idx3);
    while (finger < rightIDX)
    {
        if (array[finger] > array[pivot])
            finger++;
        if (array[finger] < array[pivot])
        {
            for (int i = 0; i <= SIZE; i++)
            {
                extraArray[i] = array[i];
            }
            if (array[finger] != array[border])
                swap(array[finger], array[border+1]);
            
            finger++;
        }
        if (array[finger] == array[pivot])
        {
            if (array[border+1] != array[pivot])
                swap(array[border+1], array[pivot]);
            if (leftIDX < border - 1)
            {
                printArray(array, SIZE);
                quickSort(array, leftIDX, border - 1);
            }
            if (border + 1 < rightIDX)
            {
                printArray(array, SIZE);
                quickSort(array, border + 1, rightIDX);
            }
        }
        for (int i = 0; i <= SIZE; i++)
        {
            extraArray[i] = array[i];
        }
    }
}

// Funkcja main, sortuje oraz zapisuje dane do pliku
int main()
{
    srand(1);
    int size = SIZE;
    int testArray[size]; //4 7 8 6 4 6 7 3 10 
    int testArray2[size];
    for (int i = 0; i < size; i++)
    {
        int number = rand() % 10 + 1;
        testArray[i] = number;
        testArray2[i] = number;
    }
    // int testArray[] = {9, 1, 2, 4, 5, 7, 8, 6, 3};

    printArray(testArray, size);
    quickSort(testArray, 0, size - 1);

    cout << "Sorted array: \n";
    printArray(testArray, size);
    printArrayToFile(testArray, size, "merge_sort");
    return 0;
}