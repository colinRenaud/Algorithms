
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <stdexcept>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

string generateLoremIpsum();
list<string> generateList(const string& loremIpsum );
vector<string> generateVector(const string& loremIpsum );
void sortByAlphabeticList(list<string>& loremIpsum);
void sortByAlphabeticVector(vector<string>& loremIpsum);
bool compareString(const string & first, const string& second);

int main() {
	typedef high_resolution_clock::time_point time;

	time begin = high_resolution_clock::now();
	const string s = generateLoremIpsum();
	time end = high_resolution_clock::now();
	cout << "Generate Lorem Ipsum  " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "µs"<< endl;

	begin = high_resolution_clock::now();
	vector<string> vector = generateVector(s);
	end = high_resolution_clock::now();
	cout << "Generate vector  " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "µs"<< endl;

	begin = high_resolution_clock::now();
	list<string> list = generateList(s);
	end = high_resolution_clock::now();
	cout << "Generate list  " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "µs"<< endl;

	begin = high_resolution_clock::now();
	sortByAlphabeticVector(vector);
	end = high_resolution_clock::now();
	cout << "Sort vector  " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "µs"<< endl;

	begin = high_resolution_clock::now();
	sortByAlphabeticList(list);
	end = high_resolution_clock::now();
	cout << "Sort List " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "µs"<< endl;
	return 0;
}

/**
 *  sort the vector
 *  store in a map the begin index of each letter
 *  ex :
 *  a : index 0 of the   vector
 *  b : index 81 of the  vector
 *  h : index 451 of the vector
 */
void sortByAlphabeticVector(vector<string>& loremIpsum) {

	sort(loremIpsum.begin(),loremIpsum.end(),compareString);
	unordered_map<char,int>  indexOfString;
	char currentLetter;

	for (unsigned int i = 0; i < loremIpsum.size(); ++i) {
		char tmp=loremIpsum[i][0];
		if( tmp != currentLetter) {
			currentLetter = tmp;
			indexOfString.insert(pair<char,int>(currentLetter,i));
		}
	}
	/*unordered_map<char,int>::iterator iter = indexOfString.begin();
	while(iter != indexOfString.end()) {
		cout << "Letter " << (*iter).first << " index " << (*iter).second << endl;
		iter++;
	}*/
}

void sortByAlphabeticList(list<string>& loremIpsum) {

	typedef list<string>::iterator listIter;
	loremIpsum.sort(compareString);
	unordered_map<char,listIter>  indexOfString;
	char currentLetter; // get the first letter

	for (listIter iter = loremIpsum.begin();iter != loremIpsum.end(); ++iter) {
		char tmp=(*iter)[0];
		if( tmp != currentLetter) {
			currentLetter = tmp;
			indexOfString.insert(pair<char,listIter>(currentLetter,iter));
		}
	}

	/*unordered_map<char,listIter>::iterator iter = indexOfString.begin();
	while(iter != indexOfString.end()) {
		cout << "Letter " << (*iter).first << " index "<< endl;
		iter++;
	}*/
}

vector<string> generateVector(const string& loremIpsum) {
	vector<string> loremVector;
	loremVector.reserve(8192);
	string::size_type size = loremIpsum.size();
	if(size > 0) {
		int unsigned i=0,j=0;
		string subWord;
		while(i < size) {
			if(isalpha(loremIpsum[i])) {
				j=i;
				while(isalpha(loremIpsum[j]))
					j++;
				loremVector.push_back(loremIpsum.substr(i,j-i));
				i += (j-i);
			}
			else
				i++;
		}
	}
	else
		throw domain_error("Error word is empty");
	return loremVector;
}

list<string> generateList(const string& loremIpsum ) {
	list<string> loremList;
	string::size_type size = loremIpsum.size();
	if(size > 0) {
		int unsigned i=0,j=0;
		string subWord;
		while(i < size) {
			if(isalpha(loremIpsum[i])) {
				j=i;
				while(isalpha(loremIpsum[j]))
					j++;
				loremList.push_back(loremIpsum.substr(i,j-i));
				i += (j-i);
			}
			else
				i++;
		}
	}
	else
		throw domain_error("Error word is empty");
	return loremList;
}

string generateLoremIpsum() {
	string s =  "Lorem ipsum dolor sit amet, ea aliquid civibus voluptatum usu,"
			" dicant possit ex sit. Clita gloriatur efficiantur an mea, persius "
			"inermis et usu. Duo eu audire antiopam, vim utamur sapientem et.";
	stringstream ss;
	for (int i = 0; i < 300; ++i)
		ss << s;
	return ss.str();

}

bool compareString(const string & first, const string& second) {
	unsigned int i =0;
	while( i<first.length() && i < second.length() ) {
		if( tolower(first[i]) < tolower(second[i])) return true;
		if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return first.length() < second.length() ;
}




