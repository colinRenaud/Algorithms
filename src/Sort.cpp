
#include <iostream> // cout and basic io stream
#include <algorithm> // sort
#include <time.h> // ctime
#include <stdlib.h> // rand
#include <string>
#include <stdio.h>

using namespace std;

int compare (const void * a, const void * b);
void stdSort(int * array, size_t size);
void stdQsort(int* array,size_t size);
void quickSort(int * array, size_t size);
void quickSortAux(int *array,size_t left,size_t right);
int partition(int* array, size_t left,size_t right);
void mergeSort(int* array,size_t size);
void mergeSortAux(int* array,size_t begin, size_t end);
void merge(int* array, size_t begin,size_t middle, size_t end);

void generateTab(int* array, size_t size, int max);
bool isSorted(int* array,size_t size);
void runSort(void(*pf)(int*,size_t),int* array,size_t size,string type);
void printArray(int* array, size_t size);

int main(int argc, char ** argv) {//args : 1:size 2: element 3:max element

    if(argc == 3) {
        size_t size = atoi(argv[1]);
        int max = atoi(argv[2]);
        int* array = new int[size];
        int* save = new int[size];

        generateTab(save,size,max);
        std::copy(save,save+size,array);
        cout << "Array of size " << size  << " generated "<< endl << endl;

        runSort(&stdSort,array,size,"std");
        std::copy(save,save+size,array);
        runSort(&stdQsort,array,size,"std Quick");
        std::copy(save,save+size,array);
        runSort(&quickSort,array,size,"Quick");
        std::copy(save,save+size,array);
        runSort(&mergeSort,array,size,"Merge");
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

int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void stdQsort(int* array,size_t size) {
    qsort(array,size,sizeof(int),compare);
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

void merge(int* array,size_t begin,size_t middle,size_t end) {
       size_t arraySize = (end-begin)+1;
    int *copy = new int[(arraySize/2)+1];

    size_t left = begin;
    size_t right = middle+1;
    std::copy(array+begin,array+middle+1,copy);  // copy old values
    size_t copyIndex = 0;

    for(size_t i=begin;i<=end;i++) {
        if (left==middle+1)
            break;
        else if (right == (end+1) || copy[copyIndex]<array[right] ) {
            array[i]=copy[copyIndex];
            left++;
            copyIndex++;
        }
        else  // (copy[left-begin]>=array[right])
            array[i]=array[right++];
    }
    delete [] copy;
}

void mergeSortAux(int* array,size_t begin,size_t end)
{
    if (begin !=  end) {
        size_t middle=(end+begin)/2;
        mergeSortAux(array,begin,middle);
        mergeSortAux(array,middle+1, end);
        merge(array,begin,middle,end);
    }
}

void mergeSort(int* array,size_t size) {
    if (size)
        mergeSortAux(array,0,size-1);
}

void heapSort(int* array, size_t size) {

}

void introSort(int* array, size_t size) {

}

void smoothSort(int* array, size_t size) {

}

void tournamentSort(int* array, size_t  size) {

}

void timSort(int* array, size_t size) {

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
    cout << "Begin " << type <<  "sort" << endl;
    
    tbegin = clock();
    (*pf)(array,size);
    tend = clock();

    telapsed = (tbegin - tend)/(CLOCKS_PER_SEC/1E3);
    string sorted = isSorted(array,size) ? "yes":"no";
    cout << "Array is sorted ? " << sorted << endl;
    cout << "Ellapsed time with "<< type <<" Sort " << telapsed  <<" ms "<< endl << endl;
}

void printArray(int* array, size_t size) {
    for(size_t i=0 ; i< size ; i++) {
        std::cout << array[i] << " " ;
    }
    std::cout << std::endl;
}
