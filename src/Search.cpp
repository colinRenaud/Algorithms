#include <iostream> // cout and basic io stream
#include <algorithm> // sort
#include <time.h> // ctime
#include <stdlib.h> // rand
#include <string>

using namespace std;

bool search(int* array,size_t size, int element);
bool sortedSearch(int* array,size_t size,int element);
bool dichotomicSearch(int *array, size_t size, int element);
bool dichotomicSearchRec(int * array,size_t size,int element);

bool dichotomicSearchRecAux(int* array,int element,size_t begin,size_t end);
void generateTab(int* array, size_t size, int max);
void runSearch(bool(*searchFunction)(int*,size_t,int),int* array,size_t size,int element,string searchType);

int main(int argc, char **argv) { // args : 1:size 2: element 3:max element

	if(argc == 4) {
		size_t size = atoi(argv[1]);
		int element = atoi(argv[2]);
		int max =  atoi(argv[3]);

		int* array = new int[size];
		generateTab(array,size,max);
		cout << "Array of size " << size  << " generated "<< endl << endl;

		// non sorted
		runSearch(&search,array,size,element,"iterative");
		sort(array,array+size);
		runSearch(&sortedSearch,array,size,element,"sorted");
		runSearch(&dichotomicSearch,array,size,element,"dichotomic");
		runSearch(&dichotomicSearchRec,array,size,element,"recursive dichotomic");

		free(array);
		return 0;
	}

	else {
		cout << "Error missing argument" ;
		return 1;
	}
}


void generateTab(int* array,size_t size,int max) {
	if(size >0 ) {
		for (size_t i = 0; i < size; ++i)
			array[i] = rand() % max;
	}
}

/*end if end of array reached || if element finded
 if end array reached  -> no element founded before
 but if end non reached and while loop ended -> element finded*/
bool search(int* array,size_t size, int element) {
	size_t i = 0;
	while(i < size && array[i] != element)
		i++;
	cout <<"Search stop after " << i << " itération" << endl;
	return i < size;
}

/*end if end of array reached || if element finded
if end array reached  -> no element founded before
but not necessary element finded : element could be  > or = to element*/
bool sortedSearch(int* array,size_t size,int element) {
	size_t i = 0;
	while(i < size && array[i] < element)
		i++;
	cout <<"Search stop after " << i << " itération" << endl;
	return i != size && array[i] == element;
}

bool dichotomicSearch(int *array, size_t size, int element) {
	size_t begin = 0, end = size -1,middle = 0, i = 0;
	bool finded = false;
	while(! finded && begin <= end) {
		middle = (begin+end)/2;
		if(array[middle] == element)
			finded= true;
		else if(array[middle] < element)
			begin = middle +1;
		else // array[middle] > element
			end = middle -1;
		i++;
	}
	cout <<"Search stop after " << i << " itération" << endl;
	return finded;
}
bool dichotomicSearchRec(int * array,size_t size,int element) {
    return dichotomicSearchRecAux(array,element,0,size-1);
}

bool dichotomicSearchRecAux(int* array,int element,size_t begin,size_t end) {
    if(begin > end)
        return false;
    else {
        size_t middle = (begin+end)/2;
        if(array[middle] == element)
            return true;
        else if(array[middle] > element)
            return dichotomicSearchRecAux(array,element,begin,middle-1);
        else
            return dichotomicSearchRecAux(array,element,middle+1,end);
    }
}

void runSearch(bool(*searchFunction)(int*,size_t,int),int* array,size_t size,int element,string searchType) {
	clock_t tbegin,tend,telapsed;
	tbegin = clock();

	cout << "Begin search" << endl;
	bool contains = (*searchFunction)(array,size,element) ? "yes":"no";
	tend = clock();

	cout << "Non sorted Array contains "<< element<< " ? " <<  contains << endl;
	telapsed = (tbegin - tend)/(CLOCKS_PER_SEC/1E6);
	cout << "Ellapsed time with " <<searchType << " search method " << telapsed  <<" µs "<< endl << endl;
}
