//-----------------------------------------------------------------------------
//	File: Date.cpp
//
//	class: Date
//	methods:
//		Date::Date(short day, short month, short year)
//		bool Date::operator==(const Comparable &other)const
//		bool Date::operator<(const Comparable &other)const
//		void Date::setCurrentDate(void)
//		void Date::setDayOfWeek(void)
//		void Date::setDayOfYear(void)
//		short Date::countLeaps(short year)const
//		void Date::setDayOfMonth(short dayOfMonth)
//		void Date::setMonth(short month)
//		void Date::setYear(short year)
//		void Date:: input(istream& sin)
//		void Date::print(ostream& sout)const
//		Date Date::tomorrow()const 
//		Date Date::yesterday()const
//		ostream& operator<<(ostream& sout, const Date& date)
//		istream& operator >> (istream& sin, Date& date)
//		readInput(istream& sin, short& input, const char* err)
//-----------------------------------------------------------------------------
#include "Date.h"
#include "ArraySort.h"

namespace TR_DATETIME
{
//-----------------------------------------------------------------------------
//    method:		Date(short day, short month, short year) -- constructor
//
//	  Programmer: Tabitha Roemish
//
//    description:	creates a new Date object
// 
//    Calls:            setCurrentDate()
//			setYear()
//			setMonth()
//			setDayOfMonth()
//			daysInMonth(month, year)
// 
//    Called By:	ostream& operator<<(ostream& sout, const CComplex &c)
// 
//    Parameters:	short day -- day to set
//			short month -- month to set
//			short year -- month to set
//
//    History Log:
//			2/9/08  PB  completed version 1.0
//			4/11/2017 TR completed version 1.1
// ----------------------------------------------------------------------------
	Date::Date(short day, short month, short year)
	{
		setCurrentDate();
		setYear(year);
		setMonth(month);
		setDayOfMonth(day);
		//setDayOfWeek, setDayOfYear called in each method above.
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		operator==(const Comparable& other) const
//
//    description:	true if the two objects are exactly the same
// 
//    Parameters:	const Comparable &other  -- the other Date to compare
//
//    Called By:	main, >=, <=
//    Exceptions:	throws bad_cast if other is not a Date// 
//    Returns:          true if the two objects are exactly the same;
//				false otherwise
//    History Log:
//			5/8/16  PB  completed version 1.1
//-----------------------------------------------------------------------------
	bool Date::operator==(const Comparable &other) const
	{
		bool returnValue = false;
		try
		{
			const Date &otherDate = 
				dynamic_cast<const Date&>(other);
			if(m_year == otherDate.m_year && 
				m_month ==otherDate.m_month &&
				m_dayOfMonth == otherDate.m_dayOfMonth )
				returnValue = true;
		}
		catch(bad_cast e)
		{ }
		return returnValue;
    }
//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		operator<(const Comparable &other) const
//
//	  programmer:	Tabitha Roemish
//
//    description:	true if the current object less than other
// 
//    Parameters:	const Comparable &other  -- the other Date to compare
//
//    Called By:	main, >, <=
//
//    Exceptions:	throws bad_cast if other is not a Date
// 
//    Returns:		true if the current object less than other;
//				false otherwise
//    History Log:
//			5/8/16  PB  completed version 1.1
//			4/11/2017 TR completed version 1.2
// ----------------------------------------------------------------------------
	bool Date::operator<(const Comparable &other) const
	{
		bool returnValue = false;
		
			const Date &otherDate = dynamic_cast<const Date&>(other);
			
			if (otherDate.m_year > m_year)
				returnValue = true;
			else if (otherDate.m_year == m_year && otherDate.m_month > m_month)
				returnValue = true;
			else if (otherDate.m_year == m_year && otherDate.m_month == m_month
				&& otherDate.m_dayOfMonth > m_dayOfMonth)
				returnValue = true;
		
		return returnValue; 
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		setCurrentDate()
//
//    description:	sets the date from the system clock
// 
//    Called By:	constructor, mutators
//
//    History Log:
//			2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	void Date::setCurrentDate(void)
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_year = currentTimePtr->tm_year + 1900;
		m_month = currentTimePtr->tm_mon;
		m_dayOfMonth = currentTimePtr->tm_mday;
		setDayOfYear();
        	setDayOfWeek();
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		setDayOfWeek(void)
//
//    description:	validates and sets the proper day of the week
//	  calls: isLeapYear()
//			countLeaps();
//    History Log:
//                  2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	void Date::setDayOfWeek(void)
	{
		short weekday = 0;
		short adjustment = 0;
		adjustment = (isLeapYear(m_year)) ? adjustment : ++adjustment;
		
		weekday = countLeaps(m_year) + (m_year - LOWYEAR + adjustment) 
			+ m_dayOfYear;
		weekday %= DAYSINWEEK;
		m_dayOfWeek = weekday;
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		setDayOfYear(void)
//	  Programmer:	Tabitha Roemish
//    description:	validates and sets the proper day of the year
//
//    History Log:
//			2/9/08  PB  completed version 1.0
//			4/11/2017 TR complted version 1.1
// ----------------------------------------------------------------------------
	void Date::setDayOfYear(void)
	{
		short dayCount = 0;
		for (short i = 0; i < m_month; i++)
			dayCount += daysInMonth(i,m_year);
		dayCount += m_dayOfMonth;
		m_dayOfYear = dayCount;
	}

//-----------------------------------------------------------------------------
//    Class:			Date
//    method:			countLeaps(short year)const
//
//    description:	returns the number of leap years from 1760 to year
// 
//    Calls:            isLeapYear(short)
// 
//    Returns:          the number of leap years from 1760 to year 
//
//    History Log:
//                           2/9/08  PB  completed version 1.0
//-----------------------------------------------------------------------------
	short Date::countLeaps(short year)const
	{ 
		short leaps = 0;
		for(short i = LOWYEAR; i <= year; i++)
			if (isLeapYear(i))
				leaps++;
	
		return leaps;
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		setDayOfMonth(short dayOfMonth)
//
//    description:	mutator for m_dayOfMonth
// 
//    Calls:            daysInMonth(short, short)
//						setDayOfYear();
//						setDayOfWeek();
// 
//    Parameters:	dayOfMonth --  day of month to set
//
//    History Log:
//			2/9/08  PB  completed version 1.0
//			4/14/2017 TR completed version 1.1
//-----------------------------------------------------------------------------
	void Date::setDayOfMonth(short dayOfMonth)
	{
		if (dayOfMonth > 0
			&& dayOfMonth <= daysInMonth(m_month, m_year))
		{
			m_dayOfMonth = dayOfMonth;
		}

		// catch default if default day is greater than month days
		if (m_dayOfMonth > daysInMonth(m_month, m_year))
			m_dayOfMonth = daysInMonth(m_month, m_year);
		
		setDayOfYear();
		setDayOfWeek();
	}
  
//-----------------------------------------------------------------------------
//    Class:	Date
//    method:		setMonth(short dmonth)
//
//    description:	mutator for m_month
// 
//    Calls:            daysInMonth(short, short)
//			setDayOfYear()
//			setDayOfWeek()
// 
//    Parameters:	month --  month to set
//
//    History Log:
//			2/9/08  PB  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::setMonth(short month)
	{
		month--;
		if (month >= 0 && month <= MONTHSINYEAR)
		{
			if (m_dayOfMonth <= daysInMonth(m_month, m_year))
			{
				m_month = month;
				setDayOfYear();
				setDayOfWeek();
			}
		} 
		
	}
 
//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		setYear(short year)
//
//    description:	mutator for m_year
// 
//    Calls:            isLeapYear(short)
//			setDayOfYear()
//			setDayOfWeek()
// 
//    Parameters:	year --  year to set
//
//    History Log:
//			 2/9/08  PB  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::setYear(short year)
    {
		if (year > LOWYEAR && !isLeapYear(m_year))
		{
			m_year = year;
			setDayOfYear();
			setDayOfWeek();
		}
	}
//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		Date:: input(istream& sin)
//	  programmer:	Tabitha Roemish
//    description:	input from date format dd/mm/yyyy
// 
//    Calls:            
//			
//    Parameters:	istream&
//
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------
	void Date:: input(istream& sin)
	{ 
		
		short day = -1;
		short month = -1;
		short year = -1;
				
		if (sin >> day)
		{
			if (sin.peek() == '/')
			{
				sin.get();
				sin >> month;
				if (sin.peek() == '/')
				{
					sin.get();
					sin >> year;
				}
			}
		}
		setCurrentDate();
		setYear(year);
		setMonth(month);
		setDayOfMonth(day);
		
		
	}
//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		Date::print(ostream& sout)const
//	  programmer:	Tabitha Roemish
//    description:	outputs date in format ex) Tuesday, March 3, 2017
// 
//    Calls:    monthName()        
//			
//    Parameters:	ostream&
//
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------
	void Date::print(ostream& sout)const
	{
		sout << weekdayName(static_cast<int> (m_dayOfWeek));
		sout << ", " 
			<< monthName(m_month)
			<< " " << m_dayOfMonth << ", " << m_year;
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		tomorrow()const
//	  programmer:	Tabitha Roemish
//    description:	increments day by 1
// 
//    Calls:       setDayOfMonth()
//					setMonth()
//					setYear()
//					daysInMonth()
//			
//    Parameters:	none
//
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------
	Date Date::tomorrow()const 
	{	
		// add one to day of month
		Date nextDay = *this;
		if (m_dayOfMonth + 1 >= daysInMonth(m_month, m_year))
		{
			nextDay.setDayOfMonth(1);
			if (m_month == 11) // december
			{
				nextDay.setMonth(1);
				nextDay.setYear(m_year + 1);
			}
			else
				nextDay.setMonth(m_month + 1);
		}
		else
			nextDay.setDayOfMonth(m_dayOfMonth + 1);
		
		return nextDay;
	}

//-----------------------------------------------------------------------------
//    Class:		Date
//    method:		yesterday()const
//	  programmer:	Tabitha Roemish
//    description:	decrements day by 1
// 
//    Calls:       setDayOfMonth()
//					setMonth()
//					setYear()
//					daysInMonth()
//			
//    Parameters:	none
//
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------
	Date Date::yesterday()const
	{
		Date previousDay = *this;

		if (m_dayOfMonth == 1)
		{
			if (m_month == 0)
			{
				previousDay.setYear(m_year - 1);
				previousDay.setMonth(MONTHSINYEAR); //december
				previousDay.setDayOfMonth(daysInMonth(MONTHSINYEAR, m_year)); 
			}
			previousDay.setMonth(m_month - 1);
			previousDay.setDayOfMonth(daysInMonth(m_month - 1, m_year));
		}
		else
			previousDay.setDayOfMonth(m_dayOfMonth - 1);

		return previousDay;
	}

//-----------------------------------------------------------------------------
//    method:		operator<<(ostream& sout, const Date& date)
//	  programmer:	Tabitha Roemish
//    description:	outputs date to ostream&
// 
//    Calls:       print()
//			
//    Parameters:	ostream& - ostream reference, Date& date reference
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const Date& date)
	{
		date.print(cout);
		return sout;
	}

//-----------------------------------------------------------------------------
//    method:		operator<<(ostream& sout, const Date& date)
//	  programmer:	Tabitha Roemish
//    description:	outputs date to ostream&
// 
//    Calls:       print()
//			
//    Parameters:	istream& - istream reference, Date& date reference
//    History Log:
//			 4/11/2017 TR completed version 1.0
//-----------------------------------------------------------------------------	
	istream& operator >> (istream& sin, Date& date)
	{
		date.input(sin);
		return sin;
	}

//-----------------------------------------------------------------------------
//    function:		readInput(istream& sin, short input)
//    description:	safely reads in a short from sin
//				Re-prompts and re-enters if input is invalid
//    
//    Input:		Comparable* d from sin
// 
//    Called By:	main
// 
//    Parameters:	istream& sin  -- the input stream
//					short& input -- reference to input
// 
//    Returns:          void 
//
//    History Log:
//			4/19/2017  TR  completed version 1.0
// ----------------------------------------------------------------------------	
	void readInput(istream& sin, short& input, const char* err)
	{
		const int CLEARSPACE = 256;
		while (!(sin >> input))
		{
			sin.clear();
			sin.ignore(CLEARSPACE, '\n');
			cout << err << endl;
			continue;
		}
		
	}
}
