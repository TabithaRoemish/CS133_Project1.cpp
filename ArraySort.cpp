//-----------------------------------------------------------------------------
//  file: ArraySort.cpp
//  functions:
//		void safeRead(istream& sin, Comparable* d, const char* prompt);
//		void printArray(ostream & sout, Comparable **a, int size);
//		void fillArrayDateTime(istream & sin, short arraySize, 
//					Comparable ** objectArray)
//		void fillArrayDate(istream & sin, short arraySize, 
//					Comparable ** objectArray)
//		void clearArray(short arraySize, Comparable** objectArray)
//		void quickSort(Comparable** from, Comparable** to);	
//		Comparable** partition(Comparable** from, Comparable** to);
//		void SortFirstMiddleLast(Comparable** from,
//			Comparable** mid, Comparable** to);
//		void insertionSort(Comparable** from, Comparable** to);
//-----------------------------------------------------------------------------

#include "ArraySort.h"

#define SIZE_CORRECTION 1 // adjustment for distance between two pointers
#define ARRAY_THRESHOLD 4 // size of array to sort with insertion sort

namespace PB_ARRAYSORT
{
//-----------------------------------------------------------------------------
//    function:		safeRead(istream& sin, Comparable* d, const char* re)
//    description:	safely reads in a DateTime (d) from sin.
//				Re-prompts and re-enters if input is invalid
//    
//    Input:		Comparable* d from sin
// 
//    Called By:	main
// 
//    Parameters:	istream& sin  -- the input stream
//			Comparable* d -- pointer to the object input
//			const char* prompt  -- prompt, if necessary
// 
//    Returns:          void 
//
//    History Log:
//			2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------	
	void safeRead(istream& sin, Comparable* d, const char* prompt)
	{
		const int BUFFERSIZE = 256;
		d->input(sin);
		while(!sin)
		{	// read in number--enter loop if fail
			sin.clear();		// clear fail
			sin.ignore(BUFFERSIZE, '\n');	// read past newline
			cout << prompt << endl;  // re-prompt
			d->input(sin);
		}
		// read past newline once input succeeds
		sin.ignore(BUFFERSIZE, '\n');
	}

//-----------------------------------------------------------------------------
//   function:	void printArray(ostream & sout, Comparable **a, int size)
//    description:	can print out an array of DateTime *
//    Output:		Comparable* d sout
//
//    Called By:	main
// 
//    Parameters:	ostream& sout  -- the output stream
//			Comparable** a -- array of pointers to the objects
//			int size  -- number of elements in the array
// 
//    Returns:          void 
//
//    History Log:
//			2/9/08  PB  completed version 1.0
//			4/26/2017 TR completed version 1.1
// ----------------------------------------------------------------------------	
	void printArray(ostream & sout, Comparable **a, int size)
	{
		for(int i = 0; i < size; i++)
		{
			sout << i + 1 << ": ";
			a[i]->print(sout);
			sout << endl;
		}
		sout << endl;
	}
//-----------------------------------------------------------------------------
//    function:	void fillArrayDateTime(istream & sin, short arraySize, 
//					Comparable ** objectArray)
//    description:	asks for array elements and fills array
//
//    Called By:	main
//	  Calls:		safeRead()
//    Parameters:	istream& sin  -- the input stream
//					short arraySize - number of elements in array
//					Comparable ** objectArray - pointer to array of comparable pointers
//    Returns:          void 
//    History Log:
//			4/26/2017 TR completed version 1.1
// ----------------------------------------------------------------------------	
	void fillArrayDateTime(istream& sin, short arraySize, Comparable ** objectArray)
	{
		DateTime temp;
		Comparable* tempCompare = &temp;

		cout << "Please enter " << arraySize << " dates with times"
			<< " in the following format below: dd/mm/yyyy hh:mm:ss" << endl;

		for (short i = 0; i < arraySize; i++)
		{
			cout << i + 1 << ") ";
			PB_ARRAYSORT::safeRead(cin, tempCompare,
				"Please enter Dates with time in number format");
			objectArray[i] = new DateTime(dynamic_cast<Date&>(*tempCompare),
				dynamic_cast<CTime&>(*tempCompare));
			temp.reset();
		}
		cout << endl;
	}

//-----------------------------------------------------------------------------
//    function:	void fillArrayDate(istream & sin, short arraySize, 
//					Comparable ** objectArray)
//    description:	asks for array elements and fills array
//
//    Called By:	main
//	  Calls:		safeRead()
//    Parameters:	istream& sin  -- the input stream
//					short arraySize - number of elements in array
//					Comparable ** objectArray - pointer to array of comparable pointers
//    Returns:          void 
//    History Log:
//			4/26/2017 TR completed version 1.1
// ----------------------------------------------------------------------------	
	void fillArrayDate(istream& sin, short arraySize, Comparable ** objectArray)
	{
		Date temp;
		Comparable * compareDate = &temp;

		cout << "Please enter " << arraySize << " dates in the following format"
			<< "below: dd/mm/yyyy " << endl;

		for (short i = 0; i < arraySize; i++)
		{
			cout << i + 1 << ") ";
			PB_ARRAYSORT::safeRead(cin, compareDate,
				"Please enter Dates with time in number format");
			objectArray[i] = new Date(dynamic_cast<Date&>(*compareDate));
			temp.setCurrentDate();
		}
		cout << endl;
	}
//-----------------------------------------------------------------------------
//    function:	void clearArray(short arraySize, Comparable** objectArray)
//    description:	releases memory in array
//
//    Called By:	main
//    Parameters:	short arraySize - size of array to clear,
//					Comparable** objectArray - address of array
//    Returns:          void 
//    History Log:
//			4/26/2017 TR completed version 1.1
// ----------------------------------------------------------------------------	
	void clearArray(short arraySize, Comparable** objectArray)
	{
		for (short i = 0; i < arraySize; i++)
		{
			if(objectArray[i] !=nullptr)
				delete objectArray[i];
		}
	}
//-----------------------------------------------------------------------------
//    function:	void quickSort(Comparable** from, Comparable** to)
//    description:	sorts array with pivots
//	  programmer: Tabitha Roemish	
//
//    Called By:	main
//	  Calls:		partition()
// 
//    Parameters:	Comparable** from (base class holder first element), 
//					Comparable** to (base class holder for last element)
// 
//    Returns:          void 
//
//    History Log:
//			4/13/2017 TR completed v1.0
// ----------------------------------------------------------------------------	
	void quickSort(Comparable** from, Comparable** to)
	{
		{
			Comparable** mid = nullptr;
			int size = SIZE_CORRECTION + to - from ; 
			
			if (size > ARRAY_THRESHOLD)
			{
				mid = partition(from, to);
				quickSort(from, mid-1);
				quickSort(mid, to);
			}
			else 
				insertionSort(from, to);
			
		}
	}
//-----------------------------------------------------------------------------
///    function:	Comparable** partition(Comparable** from, Comparable** to)
///    description:	finds middle of two points
//
//	  programmer: Tabitha Roemish	
//
//    Called By:	quickSort()
// 
//    Parameters:	Comparable** from (base class holder first element), 
//					Comparable** to (base class holder for last element)
// 
//    Returns:      Comparable** 
//
//    History Log:
//			4/13/2017 TR completed v1.0
// ----------------------------------------------------------------------------	
	Comparable** partition(Comparable** from, Comparable** to)
	{
		
		Comparable** front = from;
		Comparable** back = to - 1;
		Comparable** middle = front + ((to - from) / 2);
		Comparable** pivot = middle; // comparison element
		
		SortFirstMiddleLast(from, middle, to);
		

		swap(pivot, back); 
		swap(*pivot, *back);
		front++;
		back = pivot;
		back--;
		
		while (front <= back)
		{
			// search forward for out of order element
			while (**pivot > **front)
				++front;
			//search backward for out of order element
			while (**pivot < **back)
				--back;
			if (front < back)
			{
				swap(*front, *back);
				front++;
				back--;
			}
		}
		swap(front, pivot);
		swap(*front, *pivot);
	
		return pivot;
	}

//-----------------------------------------------------------------------------
//    function:	void SortFirstMiddleLast(Comparable** from,
//		Comparable** mid, Comparable** to)
//    description:	sorts array with pivots
//
//	  programmer: Tabitha Roemish	
//
//    Called By:	main
//	  Calls:		partition()
// 
//    Parameters:	Comparable** from (base class holder first element), 
//					Comparable** to (base class holder for last element)
// 
//    Returns:          void 
//
//    History Log:
//			4/13/2017 TR completed v1.0
// ----------------------------------------------------------------------------	
	void SortFirstMiddleLast(Comparable** from,
		Comparable** mid, Comparable** to)
	{
		
		bool low = **from < **mid && **from < **to; 
		bool high = (**from > **mid) && (**from > **to); 
		
		if (high) //if from is high
		{
			swap(*from, *to);
			if (**from > **mid) //if first is greater than mid
				swap(*from, *mid);
		}
		else if(!(high || low)) //if from is mid
		{	swap(*from, *mid); 
			if (**from > **to)
				swap(*from, *to); 
		}
		else if(**mid > **to)
			swap(*mid, *to);

	}

//-----------------------------------------------------------------------------
//    function:	void insertionSort(Comparable** from, Comparable** to)
//    description:	sorts array with insertion
//	  programmer: Tabitha Roemish	
//    Called By:	main
//	  Calls:		
// 
//    Parameters:	Comparable** from (base class holder first element), 
//					Comparable** to (base class holder for last element)
//    Returns:      void 
//    History Log:
//					4/13/2017 TR completed v1.0
// ----------------------------------------------------------------------------	
	void insertionSort(Comparable** from, Comparable** to)
	{

		Comparable * temp = from[0];
		int size = SIZE_CORRECTION + to - from;
		
		for (int i = 1; i < size; i++)
		{
			temp = from[i];			
			int j = 0;
			for (j = i; j > 0; j--)
				if (*temp < *from[j - 1])
					from[j] = from[j - 1];
				else break;
			from[j] = temp;
				
		}
		
	}
}

