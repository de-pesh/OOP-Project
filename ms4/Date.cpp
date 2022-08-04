// Final Project Milestone 1
// Date Module
// File  Date.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
//#include <ctime> hataya
#include "Date.h"
using namespace std;



namespace sdds
{
    //global variables added
    bool sdds_test = false;
    int sdds_year = 2022;
    int sdds_mon = 8;
    int sdds_day = 7;
    

    bool Date::validate()
    {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
        {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12)
        {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays())
        {
            errCode(DAY_ERROR);
        }
        return !bad();
    }

    int Date::mdays() const
    {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }
//replaced functions from here
   int Date::systemYear()const {
      int theYear = sdds_year;
      if (!sdds_test) {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         theYear = lt.tm_year + 1900;
      }
      return theYear;
   }
   void Date::setToToday() {
      if (sdds_test) {
         m_day = sdds_day;
         m_mon = sdds_mon;
         m_year = sdds_year;
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         m_day = lt.tm_mday;
         m_mon = lt.tm_mon + 1;
         m_year = lt.tm_year + 1900;
      }
      errCode(NO_ERROR);
   }
   //To here

    int Date::daysSince0001_1_1() const
    { // day since 0001/01/01
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3)
        {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }

    Date::Date() : m_CUR_YEAR(systemYear())
    {
        setToToday();
    }

    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
    {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }

    const char *Date::dateStatus() const
    {
        return DATE_ERROR[errCode()];
    }

    int Date::currentYear() const
    {
        return m_CUR_YEAR;
    }

    void Date::errCode(int readErrorCode)
    {
        m_ErrorCode = readErrorCode;
    }

    int Date::errCode() const
    {
        return m_ErrorCode;
    }

    bool Date::bad() const
    {
        return m_ErrorCode != 0;
    }

    // To read date
    istream &Date::read(istream &is)
    {
        errCode(NO_ERROR);
        is >> m_year;
        is.ignore(); // to ignore single charater
        is >> m_mon;
        is.ignore();
        is >> m_day;

        if (!is)
        {
            is.clear();
            errCode(CIN_FAILED);
        }
        else
        {
            validate();
        }
        return is;
    }

    void Date::Today() {
        setToToday();
    }


    // Writing out
    ostream &Date::write(ostream &os) const
    {
        if (bad())
        {
            os << dateStatus();
        }
        else
        {
            os << m_year << "/";
            if (m_mon < 10)
                os << "0";
            os << m_mon << "/";
            if (m_day < 10)
                os << "0";
            os << m_day;
        }
        return os;
    }

    int Date::getDays() const
    {
        return daysSince0001_1_1();
    }

    Date::operator bool() const
    {
        return (!bad());
    }

    ostream &operator<<(ostream &os, const Date &RO)
    {
        return RO.write(os);
    }

    istream &operator>>(istream &is, Date &RO)
    {
        return RO.read(is);
    }

    int DaysInMonth(int month, int year)
    {
        int n = 0;
        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))))
        {
            n = days[month - 1] + 1;
        }
        else
        {
            n = days[month - 1];
        }
        return n;
    }

    // Operator Overloading
    bool operator==(const Date &d1, const Date &d2)
    {
        return (d1.getDays() == d2.getDays());
    }

    bool operator!=(const Date &d1, const Date &d2)
    {
        return (d1.getDays() != d2.getDays());
    }

    bool operator>=(const Date &d1, const Date &d2)
    {
        return (d1.getDays() >= d2.getDays());
    }

    bool operator<=(const Date &d1, const Date &d2)
    {
        return (d1.getDays() <= d2.getDays());
    }

    bool operator<(const Date &d1, const Date &d2)
    {
        return (d1.getDays() < d2.getDays());
    }

    bool operator>(const Date &d1, const Date &d2)
    {
        return (d1.getDays() > d2.getDays());
    }

    int operator-(const Date &d1, const Date &d2)
    {
        return (d1.getDays() - d2.getDays());
    }
}