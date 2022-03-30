#ifndef MERGE_SORT_H // include guard
#define MERGE_SORTH

namespace std
{
    class MergeSort
    {
    private:
        static int *extraArray;
        static void mergeSort(int array[], int leftIDX, int rightIDX) {}
        static void merge(int array[], int leftIDX, int middleIDX, int rightIDX) {}

    public:
        static void sort(int arrayToSort[], int size) {}
    };
}
#endif