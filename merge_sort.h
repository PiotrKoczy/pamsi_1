#ifndef MERGE_SORT_H // include guard
#define MERGE_SORTH

using namespace std;

class MergeSort
{
public:
    static int extraArray[];
    void mergeSort(int*, int, int);
    void merge(int*, int, int, int);
    void sort(int*, int);
    void createExtraArray(int size){for (int i=0;i<size;i++){extraArray[i]=0;}};
    MergeSort(int);
};

#endif