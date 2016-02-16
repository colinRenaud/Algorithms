
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
size_t partition(int* array, size_t left,size_t right);

void mergeSort(int* array,size_t size);
void mergeSortAux(int* array,size_t begin, size_t end);
void merge(int* array, size_t begin,size_t middle, size_t end);

void smoothSort(int* array, size_t size);
void selectionSort(int* array,size_t size);


void generateTab(int* array, size_t size, int max);
void runSort(void(*pf)(int*,size_t),int* array,size_t size,string type);
void printArray(int* array, size_t size);

int main(int argc, char ** argv) {//args : 1:size 2: element 3:max element

    if(argc != 3) {
        cout << "Error missing argument"; std::terminate();
    }
    size_t size = atoi(argv[1]);
    int max = atoi(argv[2]);
    int* array = new int[size];


    //int array[6] = {8,17,1,9,3,2};
    int* save = new int[size];
    generateTab(save,size,max);
    cout << "Array of size " << size  << " generated "<< endl << endl;

    std::copy(array,array+size,save);
    runSort(&stdSort,array,size,"std");

    std::copy(save,save+size,array);
    runSort(&stdQsort,array,size,"std Quick");

    std::copy(save,save+size,array);
    runSort(&quickSort,array,size,"Quick");

    std::copy(save,save+size,array);
    runSort(&mergeSort,array,size,"Merge");

    /*std::copy(save,save+size,array);
    runSort(&smoothSort,array,size,"Smoort");

    std::copy(save,save+size,array);
    runSort(&selectionSort,array,size,"Selection");*/

    return 0;
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

size_t partition(int* array, size_t left,size_t right) { // return index as T is splited into T[0..i] and T[i+1,size-1]
    size_t i = left, j = right;
    int pivot = array[(i+j)/2];
    while(i <= j) {
        while(array[i] < pivot)
            i++;
        while(array[j] > pivot)
            j--;
        if(i <= j) {
            std::swap(array[i],array[j]);
            i++;
            j--;
        }
    }
    return i;
}

void merge(int* array,size_t begin,size_t middle,size_t end) {

    size_t arraySize = (end-begin)+1;
    int *copy = new int[arraySize];

    size_t left = begin;
    size_t right = middle+1;

    for(size_t i=0 ; i<arraySize ; i++) {

        if(right == end+1 || array[left] <= array[right]) { // if right == end+1 the comparasion between right and left part is impossible
            // but element of left array > element of array[right] but there are not writed yet
            copy[i] = array[left];
            ++left;
        }
        else if(left == middle+1 ||  array[left] > array[right]){
            copy[i] = array[right];
            ++right;
        }
    }
    std::copy(copy,copy+arraySize,array+begin);
    delete[] copy;
}

void mergeSortAux(int* array,size_t begin,size_t end) {
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
    for (size_t i = 0; i < size ; ++i) {
        for(size_t j = size -1 ; j > i ; j--) {
            if(array[j] < array[j-1])
                std::swap(array[j],array[j-1]);
        }
    }
}

void selectionSort(int* array,size_t size) {
    for (size_t i = 0; i < size ; ++i) {
        size_t minIndex = i;
        for (size_t j = i+1; j < size; ++j) {
            if(array[j] < array[minIndex])
                minIndex = j;
        }
        if( i != minIndex)
            std::swap(array[i],array[minIndex]);
    }
}

void tournamentSort(int* array, size_t  size) {

}

void timSort(int* array, size_t size) {

}

void generateTab(int* array,size_t size,int max) {
    if(size) {
        for (size_t i = 0; i < size; ++i)
            array[i] = rand() % max;
    }
}

void runSort(void(*pf)(int*,size_t),int* array,size_t size,string type) {
    clock_t tbegin,tend,telapsed;
    cout << "Begin " << type <<  "sort" << endl;

    tbegin = clock();
    (*pf)(array,size);
    tend = clock();

    telapsed = (tbegin - tend)/(CLOCKS_PER_SEC/1E3);
    string sorted = std::is_sorted(array,array+size) ? "yes":"no";
    cout << "Array is sorted ? " << sorted << endl;
    cout << "Ellapsed time with "<< type <<" Sort " << telapsed  <<" ms "<< endl << endl;
}

void printArray(int* array, size_t size) {
    for(size_t i=0 ; i< size ; i++)
        std::cout << array[i] << " " ;
    std::cout << std::endl << std::endl ;
}
