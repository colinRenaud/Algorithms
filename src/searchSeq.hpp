/**
 * Some search algorithm implementation
 * The algorithm are generic type based so you could use it with any type
 * The algorithm search a element of type T into a contiguous sequence composed of T element
 * The sequence is determined by a pointer begin and a pointer end
 * So the search is in sequence[begin,end]
 * n is the size of the sequence so n = end-begin with end > begin
 * List of algorithm
 * -> sequential search into non sorted sequence O(n)
 * -> binary search into sorted sequence O(log(n)
 * -> recursive binary search into sorted sequence O(log(n))
 * -> a method for run search on structure and benchmark the algorithm
 * -> a example of the STL binary search algorithm which is faster than any other of my implementation
 *
 */

#ifndef SEARCH_SEARCH_HPP
#define SEARCH_SEARCH_HPP

#include <string>
#include <stddef.h>
#include <time.h>
#include <iostream>


/**
 * Search element into the sequence [begin,end]
 *
 * @return the first occurrence of T
 * @return nullptr if nothing is find, or if end is after or equal to begin
 * @param begin : begin of the sequence
 * @param end : end of the sequence
 * @param element : element to found into sequence
 * Complexity :
 * Up to O(end-begin) if the elem doesn't exist
 * O(elementIndex) with elementIndex E [begin,end]
 */

template <typename T>
T* searchSeq(T* begin , T*end, const T& element);


/**
 * Search element into the sequence [begin,end]
 * the algorithm use binary search and only work is sequence is sorted
 *
 * @return a pointer to the first occurrence of element
 * @return nullptr if nothing is find, or if end is after or equal to begin
 * @param begin : begin of the sequence
 * @param end : end of the sequence
 * @param element : element to find into sequence
 *
 * Complexity :
 * O( log2(end-begin))
 */

template <typename T>
T* binarySearchSeq(T* begin, T*end , const T& element);

/**
 * Search element into the sequence [begin,end]
 * the algorithm use binary search and only work is sequence is sorted
 * the algorithm is recursive and use binarySearchRecAux
 *
 * @return a pointer to the first occurrence of element
 * @return nullptr if nothing is find, or if end is after or equal to begin
 * @param begin : begin of the sequence
 * @param end : end of the sequence
 * @param element : element to find into sequence
 *
 * Complexity :
 * O( log2(end-begin))
 */
template <typename T>
T* binarySearchSeqRec(T* begin, T*end , const T& element);

/**
 * Search element into the sub-sequence [seq+begin,seq+end]
 * the algorithm use binary search and only work is sequence is sorted
 * the algorithm is recursive
 *
 * @return a pointer to the first occurrence of element
 * @param seq : pointer to the sequence
 * @param begin : begin of the sub-sequence
 * @param end : end of the sub-sequence
 * @param element : element to find into sub-sequence
 */
template <typename T>
T* binarySearchSeqRecAux(T* seq, size_t begin, size_t end , const T& element);

template <typename T>
void runSearch(T*(*searchFunction)(T*,T*,const T&),T*,T*,const T&,std::string searchType);


int compareInt (const void * a, const void * b);

void stl_search(size_t*begin,size_t*end,const size_t & element);

#include "searchSeq.tcc"

#endif //SEARCH_SEARCH_H

