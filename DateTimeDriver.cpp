//------------------------------------------------------
// File: DateTimeDriver.cpp
// Functions: main()
//------------------------------------------------------

#include "CTime.h"
#include "Date.h"
#include "DateTime.h"
#include "ArraySort.h"

using namespace std;
using namespace TR_DATETIME;
using namespace PB_ARRAYSORT;
//--------------------------------------------------------------------
//	Function: main()
//
//	Title: Sorting DateTimes and Dates
//
//  Description: This file contains function main() which tests
//		DateTime and Date sorting
//
//	Programmer: Tabitha Roemish
//
//	Date: 4/13/2017
//
//	Version: 1.0
//
//	Environment:   Hardware: IBM Pentium
//                  Software:  WinXP or later or .NET for execution;
//					Compiles under Microsoft C++ 2005
//	Input: DateTimes and Dates
//
//	Output: DateTimes and Dates sorted
//
//  calls: DateTime class methods and related functions
//
//	called by: none
//
//	Parameter: none
//
//	Returns : EXIT_SUCCESS = successful
//
//	History log:
//		4/13/2017 TR completed v1.
//--------------------------------------------------------------------
int main()
{
	short arraySize = 0;
	cout << "Please enter the number of items you wish to add" << endl;
	readInput(cin, arraySize, "Please enter a number");
	
	Comparable** objectArray = nullptr;
	objectArray = new Comparable*[arraySize];

	for (short i = 0; i < arraySize; i++)
		objectArray[i] = nullptr;

	try
	{
		fillArrayDateTime(cin, arraySize, objectArray); //fill dateTime array
		quickSort(objectArray, &objectArray[arraySize - 1]);
		cout << "Here is your list of dates with times sorted: " << endl;
		printArray(cout, objectArray, arraySize);
		
		clearArray(arraySize, objectArray); //delete each array element

		fillArrayDate(cin, arraySize, objectArray); //fill date array
		quickSort(objectArray, &objectArray[arraySize - 1]);
		cout << "Here is your list of dates sorted: " << endl;
		printArray(cout, objectArray, arraySize);

		clearArray(arraySize, objectArray);
		delete[] objectArray; //delete pointer array
	}
	catch (bad_alloc e)
	{
		cout << "Could not allocate memory";
	}
	
	
	cin.get();
	cin.get();
	return EXIT_SUCCESS;
}