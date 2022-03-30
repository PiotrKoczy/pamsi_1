#ifndef MERGE_SORT_H // include guard
#define MERGE_SORTH

using namespace std;

class MergeSort
{
private:
    int const_size=10;

public:
    void mergeSort(int*, int, int);
    void merge(int*, int, int, int);
    MergeSort(int);
};

#endif