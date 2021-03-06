//-----------------------------------------------------------------------------
//	File: ArraySort.h
//-----------------------------------------------------------------------------

#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include "DateTime.h"
using namespace std;
using namespace TR_DATETIME;
//----------------------------------------------------------------------------
// One of two choices for format of these function
// This set uses pointers in the way that the STL uses iterators
//----------------------------------------------------------------------------
namespace PB_ARRAYSORT
{	
	void quickSort(Comparable** from, Comparable** to);	
	Comparable** partition(Comparable** from, Comparable** to);	
	void SortFirstMiddleLast(Comparable** from,
		Comparable** mid, Comparable** to);	
	void insertionSort(Comparable** from, Comparable** to);
	void safeRead(istream& sin, Comparable* d, const char* prompt);
	void printArray(ostream & sout, Comparable **a, int size);
	void fillArrayDateTime(istream& sin, short arraySize, Comparable ** objectArray);
	void fillArrayDate(istream& sin, short arraySize, Comparable ** objectArray);
	void clearArray(short ArraySize, Comparable** objectArray);
}
#endif