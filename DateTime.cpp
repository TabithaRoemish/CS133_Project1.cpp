//-----------------------------------------------------------------------------
//	File: DateTime.cpp
//
//	class: DateTime
//	methods:
//		void DateTime::reset()
//		virtual bool DateTime::operator==(const Comparable &other)const
//		virtual bool DateTime::operator<(const Comparable &other)const
//		virtual void input(istream& sin);
//		virtual void print(ostream& sout)const;
//		ostream& operator<<(ostream& sout, const Date& date);
//		istream& operator >> (istream& sin, Date& date);
//-----------------------------------------------------------------------------
#include "DateTime.h"


namespace TR_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:		DateTime
//    method:		reset(DateTime& dateTime)
//
//	  programmer:	Tabitha Roemish
//    description:	resets DateTime to default
//
//    Parameters:	DateTime& dateTime reference to reset
//
//    Called By:	FillDateTime()
//	  Calls:		Date::print(), CTime::print()
//
//    Returns:      none
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	void DateTime::reset()
	{	
		Date::setCurrentDate();
		CTime::setCurrentTime();
	}
//-----------------------------------------------------------------------------
//    Class:		DateTime
//    method:		operator==(const Comparable &other)const
//	  programmer:	Tabitha Roemish
//    description:	true if the two objects are exactly the same
//    Parameters:	const Comparable &other  -- the other DateTime to compare
//    Called By:	main, >=, <=
//    Exceptions:	throws bad_cast if other is not a Date
//    Returns:      true if the two objects are exactly the same;
//					false otherwise
//    History Log:
//					4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	bool DateTime::operator==(const Comparable &other)const
	{
		
		bool returnValue = false;
		try
		{
			const DateTime& otherDateTime = 
				dynamic_cast<const DateTime&>(other);
			if (this->Date::operator==(otherDateTime) &&
				this->CTime::operator==(otherDateTime))
				returnValue = true;
			
		}
		catch (bad_cast e)
		{
		}
		
		return returnValue;
	}
	
//-----------------------------------------------------------------------------
//    Class:		DateTime
//    method:		operator<(const Comparable &other)const
//	  programmer:	Tabitha Roemish
//    description:	true if the current object less than other
//    Parameters:	const Comparable &other  -- the other DateTime to compare
//    Called By:	main, >, <=
//    Exceptions:	throws bad_cast if other is not a Date
//    Returns:      true if the current object less than other;
//				false otherwise
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	bool DateTime::operator<(const Comparable &other)const
	{
		bool returnValue = false;
		
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			
			if (this->Date::operator<(otherDateTime))
				returnValue = true;
			else if (this->Date::operator==(otherDateTime) 
				&& this->CTime::operator<(otherDateTime))
				returnValue = true;
		
		return returnValue;
	}
//-----------------------------------------------------------------------------
//    Class:		DateTime
//    method:		void input(istream& sin)
//	  programmer:	Tabitha Roemish
//    description:	input Date and Time object
//    Parameters:	istream& sin - input reference stream 
//    Called By:	operator >>
//	  Calls:		Date::input();
//					CTime::input();
//    Returns:		none 
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------
	void DateTime::input(istream& sin)
	{
		this->Date::input(sin);
		if (sin.peek()== ' ')
			this->CTime::input(sin);
		
	}
//-----------------------------------------------------------------------------
//    Class:		DateTime
//    method:		print(ostream& sout)const
//
//	  programmer:	Tabitha Roemish
//    description:	prints out DateTime object in dd/mm/yyyy hh:mm:ss format
//
//    Parameters:	ostream& sout - outstream reference
//
//    Called By:	operator<<
//	  Calls:		Date::print(), CTime::print()
//
//    Returns:      none
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	void DateTime::print(ostream& sout)const
	{
		Date::print(sout);
		sout << " ";
		CTime::print(sout);
	}

//-----------------------------------------------------------------------------
//    method:		operator<<(ostream& sout, const DateTime& dateTime)
//	  programmer:	Tabitha Roemish
//    description:	prints out a DateTime object
//    Parameters:	ostream& sout - outstream reference
//					const DateTime& dateTime - DateTime object to output
//    Called By:	main()
//	  Calls:		print()
//    Returns:     ostream& - outstream reference 
//    History Log:
//				   4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	ostream& operator<<(ostream& sout, const DateTime& dateTime)
	{
		dateTime.print(sout);
		return sout;
	}

//-----------------------------------------------------------------------------
//    method:		operator >> (istream& sin, DateTime& dateTime)
//	  programmer:	Tabitha Roemish
//    description:	inputs DateTime object
//    Parameters:	istream& sin, istream reference
//					DateTime& dateTime object to read in
//    Called By:	main()
//	  Calls:		input();
//
//    Returns:      istream reference
//    History Log:
//			4/13/2017  TR  completed version 1.1
//-----------------------------------------------------------------------------

	istream& operator >> (istream& sin, DateTime& dateTime)
	{
		dateTime.input(sin);
		return sin;
	}

}
