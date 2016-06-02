

#ifndef SORT_SORTSEQ_H
#define SORT_SORTSEQ_H

#include <bits/c++config.h>

using std::size_t;

template <typename T>
void quickSort(T* beginSeq, T*endSeq);

template <typename T>
void quickSortAux(T* beginSeq, size_t left, size_t right);

template <typename T>
size_t partition(T* beginSeq, size_t left, size_t right);


template <typename T>
void mergeSort(T* beginSeq, T* endSeq);

template <typename T>
void mergeSortAux(T* beginSeq, size_t begin, size_t end);

template <typename T>
void merge(T* beginSeq, size_t begin, size_t middle, size_t end);


template <typename T>
void smoothSort(T* beginSeq, T* endSeq);

template <typename T>
void selectionSort(T* beginSeq, T* endSeq);


#endif //SORT_SORTSEQ_H
