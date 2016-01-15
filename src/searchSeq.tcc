#include "searchSeq.hpp"



template <typename T>
T* searchSeq(T* begin , T*end, const T& element) {
    if( begin >= end)
        return nullptr;
    size_t size = end - begin;
    size_t i = 0;
    while(i < size) {
        if( begin[i] == element )
            return begin+i;
        i++;
    }
    return nullptr;
}

template <typename T>
T* binarySearchSeq(T* begin, T*end , const T& element) {
    if( begin >= end)
        return nullptr;
    size_t begIndex = 0 , endIndex = end-begin , middle = 0;
    while(begIndex <= endIndex) {
        middle = (begIndex + endIndex)/2;
        if(begin[middle] > element)
            endIndex = middle-1;
        else if(begin[middle] < element)
            begIndex = middle+1;
        else //begin[middle] == element
            return begin+middle;
    }
    return nullptr;
}

template <typename T>
T* binarySearchSeqRec(T* begin, T*end , const T& element) {
    if( begin >= end)
        return nullptr;
    return binarySearchSeqRecAux(begin,0,(end-begin),element); // from begin to end
}

template <typename T>
T* binarySearchSeqRecAux(T* seq, size_t begin, size_t end , const T& element) {
    if(begin > end)
        return nullptr;
    size_t middle = (begin+end)/2;
    if(seq[middle] > element)
        return binarySearchSeqRecAux(seq,begin,middle-1,element);
    else if(seq[middle] < element)
        return binarySearchSeqRecAux(seq,middle+1,end,element);
    return seq+middle; // seq[middle] == element)
}

template <typename T>
void runSearch(T*(*searchSeqF)(T*,T*,const T&),T* begin,T*end ,const T& element,std::string searchType) {
    clock_t tbegin,tend,telapsed;
    std::cout << "Begin search" << std::endl;

    tbegin = clock();
    T* contains = (*searchSeqF)(begin,end,element);
    tend = clock();

    std::string str = contains ? "yes":"no";
    std::cout << "Sequence contains " << element << " ? " << str << std::endl;

    telapsed = (tend - tbegin)/(CLOCKS_PER_SEC/1E9);
    std::cout << "Ellapsed time with " << searchType << " search method " << telapsed << " ns " << std::endl<< std::endl;
}


int compareInt(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

void stl_search(size_t* begin,size_t*end,const size_t & element) {
    clock_t tbegin,tend,telapsed;
    std::cout << "Begin search" << std::endl;

    tbegin = clock();
    void* contains = std::bsearch(&element,begin,(end-begin),sizeof(size_t),compareInt);
    tend = clock();

    std::string str = contains ? "yes":"no";
    std::cout << "Sequence contains " << element << " ? " << str << std::endl;

    telapsed = (tend - tbegin)/(CLOCKS_PER_SEC/1E9);
    std::cout << "Ellapsed time with STL binary search method " << telapsed << " ns " << std::endl<< std::endl;
}
