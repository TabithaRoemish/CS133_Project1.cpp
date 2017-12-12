//-----------------------------------------------------------------------------
//	File: Date.h
//
//	class: Date
//-----------------------------------------------------------------------------
#ifndef DATE_H
#define DATE_H
//-----------------------------------------------------------------------------
//    Class:			Date
//
//    File:             Date.cpp
//
//    Title:            Date Class
//
//    Description:		This file contains the class definition for Date
//
//    Programmer:		Tabitha Roemish
//   
//    Date:             4/28/2017
// 
//    Version:          1.1
//  
//    Environment:   Hardware: intel(R) Xeon(R) CPU E5-1620 
//                   Software:  Windows 10 Enterprise;
//								compiles with Visual Studio 2015;
//	  class Date:
//
//	  Properties:
//		short m_year;		// full year, i.e., 2006
//		short m_month;		// 0 - 11
//		short m_dayOfMonth; // 1 - days in that month
//		short m_dayOfYear;  // 1 - 365 or 366
//		short m_dayOfWeek;	// 0 - 6
//
//	  Methods:
//		Inline:
//
//		Static:
//			static bool isLeapYear(short year) 
//				true if year is a leap year; false otherwise
//			static short daysInMonth(short month, short year) 
//				returns the number of days in month for that year
//			static const char* monthName(int monthNum) 
//				returns a string representation of monthNum
//			static const char* weekdayName(int weekdayNum) 
//				returns a string representation of weekdayNum
//		Non-Static:
//			short getDayOfWeek() const
//					returns short - index for day of week
//			short getDayOfMonth() const
//					returns short - index for day of month
//			short getMonth() const
//					returns short - index for month
//			short getYear() const
//					returns short - year
//			short getDayOfYear() const
//					returns short for day of year (0-365 or 366)
//			virtual bool operator!=(const Comparable &other)const
//			virtual bool operator>(const Comparable &other)const
//			virtual bool operator<=(const Comparable &other)const
//			virtual bool operator>=(const Comparable &other)const		
//
//
//		Non-inline:
//			virtual bool operator==(const Comparable &other)const
//			virtual bool operator<(const Comparable &other)const
//			virtual void input(istream& sin)
//			virtual void print(ostream& sout)const
//			void setMonth(short monthIn)
//			void setYear(short yearIn)
//			void setCurrentDate(void)
//			void setDayOfYear(void)
//			void setDayOfWeek(void)
//			void setDayOfMonth(short dayOfMonth)
//			Date tomorrow()const
//			Date yesterday()const
//			short countLeaps(short year)const
//			void print(ostream& sout)const;
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
//						4/28/2017 TR completed version 1.1
// ----------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Comparable.h"
using namespace std;

const string monthNames[] = { "January", "February", "March", "April", "May", 
"June", "July", "August", "September", "October", "November", "December" };

const string weekNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday", 
"Thursday", "Friday", "Saturday" };

const short normalDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const short leapDays[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
 
namespace TR_DATETIME
{
	const short LOWYEAR = 1760;
	const short DAYSINYEAR = 365;
	const short STARTDAYOFWEEK = 2;
	const short MONTHSINYEAR = 12;
	const short DAYSINWEEK = 7;

	class Date : virtual public Comparable
	{
	public:
		Date(short day = -1, short month = -1 , short year = -1);
		virtual ~Date(void) {}
		// pure virtuals that MUST be defined
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
			{return !((*this) == other);}
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
			{return !((*this) < other) && !((*this) == other);}
		virtual bool operator<=(const Comparable &other)const
			{return !((*this) > other);}
		virtual bool operator>=(const Comparable &other)const
			{return !((*this) < other);}
		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;
	
		// mutators
		void setCurrentDate(void);
		void setDayOfMonth(short dayOfMonth);
		void setMonth(short monthIn);
		void setYear(short yearIn);
		short countLeaps(short year)const;

		Date tomorrow()const;
		Date yesterday()const;
		
		//accessors
		short getDayOfWeek()const {return m_dayOfWeek;}
		short getDayOfMonth()const {return m_dayOfMonth;}
		short getMonth()const {return m_month;}
		short getYear()const {return m_year;}
		short getDayOfYear()const {return m_dayOfYear;}

		//statics
		static bool isLeapYear(short year)
			{return (year % 4 == 0) && (year % 400 == 0 || year % 100 != 0);}
		static short daysInMonth(short month, short year)
			{return (isLeapYear(year)) ? leapDays[month] : normalDays[month];} 
		static const char* monthName(int monthNum)
			{return monthNames[monthNum].c_str();}
		static const char* weekdayName(int weekdayNum)
			{return weekNames[weekdayNum].c_str();}
	
	private:
		void setDayOfYear(void);
		void setDayOfWeek(void);

	protected:
		short m_year;  // full year, i.e., 2012
		short m_month; // 0 - 11
		short m_dayOfMonth; // 1 - days in that month
		short m_dayOfYear;  // 1 - 365 or 366
		short m_dayOfWeek;	// 0 - 6
	};
	
	ostream& operator<<(ostream& sout, const Date& date);
	istream& operator>>(istream& sin, Date& date);

	void readInput(istream& sin, short& input, const char * err);
}
#endif
