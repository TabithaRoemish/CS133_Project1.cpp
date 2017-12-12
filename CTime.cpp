//-----------------------------------------------------------------------------
//	File: CTime.cpp
//
//	class: CTime
//	methods:
//		void CTime::setCurrentTime()
//		CTime(void)
//		CTime(int hour, int minute, int second)
//		CTime::operator==(const Comparable &other)const
//		CTime::operator<(const Comparable &other)const
//		CTime::setHour(short hour)
//		CTime::setMinute(short minute)
//		void CTime::setSecond(short second)
//		CTime::input(istream& sin)
//		CTime::print(ostream& sout)const
//		operator<<(ostream& sout, const CTime& time)
//		operator >> (istream& sin, CTime& time)
//-----------------------------------------------------------------------------
#include "CTime.h"
#include "Date.h"

namespace TR_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:		CTime
//	  method:		setCurrentTime()
//	  programmer:	Paul Bladek
//    description:	sets the time from the system clock
//
//    Called By:	constructor, mutators
//
//    History Log:
//			2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		CTime(void)
//
//	  programmer:	Tabitha Roemish
//    description:	constructor, creates default (current time)

//    Called By:	main
//	  Calls:		setCurrentTime()
//
//    Returns:      CTime object
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	CTime::CTime(void)
	{
		setCurrentTime();
	}

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		CTime(int hour, int minute = 0, int second = 0)
//
//	  programmer:	Tabitha Roemish
//    description:	constructor which takes in 3 parameters
//
//    Parameters:	int hour, int min, int second - hour, min and sec of time
//
//    Called By:	main
//
//    Returns:    CTime object  
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	CTime::CTime(int hour, int minute, int second)
	{
		setCurrentTime();
		setHour(hour);
		setMinute(minute);
		setSecond(second);
	}

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		operator==(const Comparable &other)const
//
//	  programmer:	Tabitha Roemish
//    description:	true if the two objects are exactly the same
//
//    Parameters:	const Comparable &other (base class container)
//
//    Called By:	main, >=, <=
//
//    Exceptions:	throws bad_cast if other is not a Date
//    Returns:      true if the two objects are exactly the same;
//				false otherwise
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	 bool CTime::operator==(const Comparable &other)const
	{
		 bool returnValue = false;
		 try
		 {
			 const CTime &otherTime = dynamic_cast<const CTime&>(other);
			 if (m_hour == otherTime.m_hour && m_minute == otherTime.m_minute 
				 && m_second == otherTime.m_second)
				 returnValue = true;
		 }
		 catch (bad_cast e)
		 {}
		 return returnValue;
	}
//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		operator<(const Comparable &other)const
//
//	  programmer:	Tabitha Roemish
//    description:	true if the current object less than other
//
//    Parameters:	const Comparable &other  -- the other CTime to compare
//
//    Called By:	main, >, <=
//    Exceptions:	throws bad_cast if other is not a Date
//
//    Returns:      true if the current object less than other;
//				false otherwise
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	 bool CTime::operator<(const Comparable &other)const
	 {
		 bool returnValue = false;
		 
			 const CTime &otherTime = dynamic_cast<const CTime&>(other);
			
			 if (otherTime.m_hour > m_hour)
				 returnValue = true;
			 else if (otherTime.m_hour == m_hour
				 && otherTime.m_minute > m_minute)
				 returnValue = true;
			 else if (otherTime.m_hour == m_hour
				 && otherTime.m_minute == m_minute
				 && otherTime.m_second > m_second)
				 returnValue = true;
		
		 return returnValue;
	 }

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		setHour(short hour)
//	  programmer:	Tabitha Roemish
//    description:	checks limits and sets the hour
//    Parameters:	short hour - hour to set
//    Called By:	constructor
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	 void CTime::setHour(short hour)
	 {
		 m_hour = (hour > 0 && hour < MAXHOUR-1) ? hour : m_hour;
	 }

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		setMinute(short minute)
//	  programmer:	Tabitha Roemish
//    description:	checks limits and sets minute
//    Parameters:	short minute - minute to set
//    Called By:	constructor     
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	 void CTime::setMinute(short minute)
	 {
		 m_minute = (minute > 0 && minute < MAXMINSEC - 1) ? minute : m_minute;
	 }

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		setSecond(short second)
//	  programmer:	Tabitha Roemish
//    description:	Checks limits and sets seconds
//    Parameters:	short second - seconds to set
//    Called By:	constructor     
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	 void CTime::setSecond(short second)
	 {
		 m_second = (second > 0 && second < MAXMINSEC - 1) ? second : m_second;
	 }

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		CTime::input(istream& sin)
//	  programmer:	Tabitha Roemish
//    description:	input CTime in hh:mm:ss format
//
//    Parameters:	istream & sin , istream reference
//
//    Called By:	operatorr>>
//	  Calls:		readInput();
//					setHour();
//					setMinut();
//					setSecond();
//
//    Returns:      
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	 void CTime::input(istream& sin)
	 {
		 short hour = 0;
		 short minute =0;
		 short second = 0;

		 if (sin >> hour)
		 {
			 if (sin.peek() == ':')
			 {
				 sin.get();
				 sin >> minute;
				 if (sin.peek() == ':')
				 {
					 sin.get();
					 sin >> second;
				 }
			 }
		 }
		 setCurrentTime();
		 setHour(hour);
		 setMinute(minute);
		 setSecond(second);

	 }

//-----------------------------------------------------------------------------
//    Class:		CTime
//    method:		print(ostream& sout)const
//	  programmer:	Tabitha Roemish
//    description:	prints CTime object in HH:MM:SS
//    Parameters:	ostream& sout, output stream
//    Called By:	operator<<   
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	 void CTime::print(ostream& sout)const
	 {
		 sout << m_hour << ":" << m_minute << ":" << m_second;
	 }


//-----------------------------------------------------------------------------
//    method:		operator<<(ostream& sout, const CTime& time)	
//	  programmer:	Tabitha Roemish
//    description:	outputs CTime object
//    Parameters:	ostream& sout, const CTime& time 
//					- output stream and CTime object reference
//    Called By:	main
//	  Calls:		print()
//    Returns:      ostream reference
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	 ostream& operator<<(ostream& sout, const CTime& time)
	 {
		 time.print(sout);
		 return sout;
	 }

//-----------------------------------------------------------------------------
//    method:		operator >> (istream& sin, CTime& time)	
//	  programmer:	Tabitha Roemish
//    description:	inputs CTime object
//    Parameters:	istream& sin, CTime & - input stream, CTime object to rea
//    Called By:	main
//	  Calls:		input()
//    Returns:      istream reference
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	 istream& operator >> (istream& sin, CTime& time)
	 {
		 time.input(sin);
		 return sin;
	 }
}
