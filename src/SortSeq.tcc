

#include "SortSeq.hpp"
#include <algorithm>

template <typename T>
void quickSort(T* beginSeq, T*endSeq) {
    size_t size = endSeq-beginSeq;
    if(size)
        quickSortAux(beginSeq,0,size-1);
}

template <typename T>
void quickSortAux(T* beginSeq, size_t left, size_t right) {
    size_t pivot = partition(beginSeq,left,right);
    if(left < pivot -1)
        quickSortAux(beginSeq,left,pivot-1);
    if(right > pivot )
        quickSortAux(beginSeq,pivot,right);
}

template <typename T>
size_t partition(T* beginSeq, size_t left, size_t right) {
    size_t i = left, j = right;
    int pivot = beginSeq[(i+j)/2];
    while(i <= j) {
        while(beginSeq[i] < pivot) i++;
        while(beginSeq[j] > pivot) j--;
        if(i <= j) {
            std::swap(beginSeq[i],beginSeq[j]);
            i++; j--;
        }
    }
    return i;
}

template <typename T>
void mergeSort(T* beginSeq, T* endSeq) {
    size_t size = endSeq-beginSeq;
    if (size)
        mergeSortAux(beginSeq,0,size-1);
}

template <typename T>
void mergeSortAux(T* beginSeq, size_t begin, size_t end) {
    if (begin !=  end) {
        size_t middle=(end+begin)/2;
        mergeSortAux(beginSeq,begin,middle);
        mergeSortAux(beginSeq,middle+1, end);
        merge(beginSeq,begin,middle,end);
    }
}

template <typename T>
void merge(T* beginSeq, size_t begin, size_t middle, size_t end) {
    size_t arraySize = (end-begin)+1;
    T *copy = new T[arraySize];
    size_t left = begin, right = middle+1;
    for(size_t i=0 ; i<arraySize ; i++) {
        if(right == end+1 || beginSeq[left] <= beginSeq[right]) { // if right == end+1 the comparasion between right and left part is impossible
            // but element of left array > element of array[right] but there are not writed yet
            copy[i] = beginSeq[left];
            ++left;
        }
        else if(left == middle+1 ||  beginSeq[left] > beginSeq[right]){
            copy[i] = beginSeq[right];
            ++right;
        }
    }
    std::copy(copy,copy+arraySize,beginSeq+begin);
    delete[] copy;
}


template <typename T>
void smoothSort(T* beginSeq, T* endSeq) {
    size_t size = endSeq- beginSeq;
    for (size_t i = 0; i < size ; ++i) {
        for(size_t j = size -1 ; j > i ; j--) {
            if(beginSeq[j] < beginSeq[j-1])
                std::swap(beginSeq[j],beginSeq[j-1]);
        }
    }
}

template <typename T>
void selectionSort(T* beginSeq, T* endSeq) {
    size_t size = endSeq- beginSeq;
    for (size_t i = 0; i < size ; ++i) {
        size_t minIndex = i;
        for (size_t j = i+1; j < size; ++j) {
            if(beginSeq[j] < beginSeq[minIndex])
                minIndex = j;
        }
        if( i != minIndex)
            std::swap(beginSeq[i],beginSeq[minIndex]);
    }
}
