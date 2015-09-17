//
// Created by spiraltek on 15/09/15.
//
#include <iostream> // cout and basic io stream
#include <algorithm> // sort
#include <time.h> // ctime
#include <stdlib.h> // rand
#include <string>
#include <stdio.h>

using namespace std;

void stdSort(int * array, size_t size);
void quickSort(int * array, size_t size);
void quickSortAux(int *array,size_t left,size_t right);
int partition(int* array, size_t left,size_t right);
void generateTab(int* array, size_t size, int max);
bool isSorted(int* array,size_t size);
void runSort(void(*pf)(int*,size_t),int* array,size_t size,string type);

int main(int argc, char ** argv) {//args : 1:size 2: element 3:max element

    if(argc == 3) {
        size_t size = atoi(argv[1]);
        int max = atoi(argv[2]);
        int* array = new int[size];
        int* save = new int[size];

        generateTab(array,size,max);
        std::copy(array,array+size,save);
        cout << "Array of size " << size  << " generated "<< endl << endl;

        runSort(&stdSort,array,size,"std");
        std::copy(save,save+size,array); // restore original data for comparaison of each sort
        runSort(&quickSort,array,size,"Quick");

        free(save);
        free(array);
        return 0;
    }
    else {
        cout << "Error missing argument" ;
        return 1;
    }
}

void stdSort(int * array, size_t size) {
    sort(array,array+size);
}

void quickSort(int * array, size_t size) {
    return quickSortAux(array,0,size-1);
}

void quickSortAux(int *array,size_t left,size_t right) {
    size_t pivot = partition(array,left,right);
    if(left < pivot -1)
        quickSortAux(array,left,pivot-1);
    if(right > pivot)
        quickSortAux(array,pivot,right);
}

int partition(int* array, size_t left,size_t right) { // return index as T is splited into T[0..i] and T[i+1,size-1]
    size_t i = left, j = right;
    int pivot = array[(i+j)/2], tmp = 0;
    while(i <= j) {
        while(array[i] < pivot)
            i++;
        while(array[j]>pivot)
            j--;
        if(i <= j) {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }
    return i;
}

void generateTab(int* array,size_t size,int max) {
    if(size > 0) {
        for (size_t i = 0; i < size; ++i)
            array[i] = rand() % max;
    }
}

bool isSorted(int* array,size_t size) {
    if(size == 0 || size == 1)
        return true;
    size_t i = 0;
    while(i<size-1) {
        if (array[i] > array[i + 1])
            return false;
        ++i;
    }
    return true;
}
void runSort(void(*pf)(int*,size_t),int* array,size_t size,string type) {
    clock_t tbegin,tend,telapsed;
    cout << "Begin sort" << endl;
    
    tbegin = clock();
    (*pf)(array,size);
    tend = clock();

    telapsed = (tbegin - tend)/(CLOCKS_PER_SEC/1E6);
    string sorted = isSorted(array,size) ? "yes":"no";
    cout << "Array is sorted ? " << sorted << endl;
    cout << "Ellapsed time with "<< type <<" Sort " << telapsed  <<" ùs "<< endl << endl;
}
