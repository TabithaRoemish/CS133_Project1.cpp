//-----------------------------------------------------------------------------
//	File: DateTime.h
//
//	class: DateTime
//-----------------------------------------------------------------------------
#ifndef DATETIME_H
#define DATETIME_H
#include "Date.h"
#include "CTime.h"
//-----------------------------------------------------------------------------
//    Class:			Date
//
//    File:             Date.cpp
//
//    Title:            Date Class
//
//    Description:		This file contains the class definition for DateTime
//
//    Programmer:		Tabitha Roemish
//   
//    Date:             4/28/2017
// 
//    Version:          1.0
//  
//    Environment:   Hardware: intel(R) Xeon(R) CPU E5-1620 
//                   Software:  Windows 10 Enterprise;
//								compiles with Visual Studio 2015;
//	  class DateTime:
//
//	  Methods:
//		Inline:
//			DateTime(); // void default constructor
//			DateTime(short dayOfMonth, short month = 0, short year = 0,
//				short hour = 0, short minute = 0, short second = 0)
//				- constructor with date & time parameters
//			DateTime(const Date& date, const CTime& time);
//				- constructor with date & time references
//			virtual ~DateTime(); // destructor
//			virtual bool operator!=(const Comparable &other)const
//			virtual bool operator>(const Comparable &other)const
//			virtual bool operator<=(const Comparable &other)const
//			virtual bool operator>=(const Comparable &other)const

//		Non-inline:
//			virtual void input(istream& sin);
//			virtual void print(ostream& sout)const;
//			void reset();
//			virtual bool operator<(const Comparable &other)const;
//			virtual bool operator==(const Comparable &other)const;
//			ostream& operator<<(ostream& sout, const Date& date);
//			istream& operator >> (istream& sin, Date& date);
//    History Log:
//						4/28/2017 TR completed version 1.1
// ----------------------------------------------------------------------------
namespace TR_DATETIME
{

	class DateTime: public Date, public CTime
	{
	public:
		//constructors
		DateTime() : Date(), CTime() {};
		DateTime(short dayOfMonth, short month = 0, short year = 0,
			short hour = 0, short minute = 0, short second = 0) : 
			Date(dayOfMonth,month, year), CTime(hour, minute, second) {};
		DateTime(const Date& date, const CTime& time) :Date(date), 
			CTime(time) {};
		virtual ~DateTime() {};

		void reset();

		//virtual methods
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

	};

	ostream& operator<<(ostream& sout, const Date& date);
	istream& operator >> (istream& sin, Date& date);



}

#endif