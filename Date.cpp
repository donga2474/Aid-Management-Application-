// Final Project Milestone 1
//
// Version 1.0
// Date
// Author   Ravindrakumar Donga
// Description
//
//senecaid:121726120
//email:rdonga@seneca.ca
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include<iostream>
#include"Date.h"
#include"general.h"

using namespace std;

namespace sict
{
    Date::Date()          // default Constructor it safe assign the values
    {
        year_ = 0;
        mon_ = 0;
        day_ = 0;
        readErrorCode_ = NO_ERROR;
    }

    Date::Date(int C_year, int C_month, int C_day) // constructor with three parameters passed. that sets the values of day,month and year;
    {
        if (C_year != 0 && C_month != 0 && C_day != 0)
        {
            year_ = C_year;
            mon_ = C_month;
            day_ = C_day;
            readErrorCode_ = NO_ERROR;
        }
        else
        {
            year_ = 0;
            mon_ = 0;
            day_ = 0;
            readErrorCode_ = NO_ERROR;
        }
    }

    void Date::errCode(int errorCode)        // sets the value of readerrorcode_;
    {
        readErrorCode_ = errorCode;
    }

    int Date::errCode()const            //Returns the readErrorCode_ value.
    {
        return readErrorCode_;
    }

    bool Date::bad()const                   //Returns true if readErrorCode_ is not equal to zero
    {
        if (readErrorCode_ != NO_ERROR)
            return true;
        else
            return false;
    }


    int Date::value()const            // returns the largest value = latest date;
    {
        return year_ * 372 + mon_ * 31 + day_;
    }

    int Date::mdays()const	            // returns the number of days in that month; 
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }

    bool Date::operator==(const Date& D)const       // check for the same date
    {
        if (this->value() == D.value())
            return true;
        else
            return false;
    }

    bool Date::operator!=(const Date& D)const       //check that both date are not same
    {
        if (this->value() != D.value())
            return true;
        else
            return false;
    }

    bool Date::operator<(const Date& D)const        //check that date1 is lessthan date2
    {
        if (this->value() < D.value())
            return true;
        else
            return false;
    }

    bool Date::operator>(const Date& D)const    //check that date1 is greater than date2
    {
        if (this->value() > D.value())
            return true;
        else
            return false;
    }

    bool Date::operator<=(const Date& D)const       //check that date1 is lessthan equal date2
    {
        if (this->value() <= D.value())
            return true;
        else
            return false;
    }

    bool Date::operator>=(const Date& D)const   // check that date1 is greater thanequal to date2
    {
        if (this->value() >= D.value())
            return true;
        else
            return false;
    }

    istream& Date::read(std::istream& istr)         //read the value and check whetherdate is correct or not
    {
       
        istr >> year_;
        istr.ignore(5, '/');
        istr >> mon_;
        istr.ignore(5, '/');
        istr >> day_;

        if (istr.fail())    //if it fails to takae the valuue
        {
            readErrorCode_ = CIN_FAILED;
            return istr;
        }
        if (year_ < MIN_YEAR || year_ > MAX_YEAR)   //check  the validity of the year
        {
            readErrorCode_ = YEAR_ERROR;
            return istr;
        }
        if (mon_ < 1 || mon_ > 12 )     //check if the month is valide or not
        {
            readErrorCode_ = MON_ERROR;
            return istr;
        }
        if (day_ > mdays() || day_ < 0 )    //check for the validate date
        {
            readErrorCode_ = DAY_ERROR;
            return istr;
            
        }
       

        return istr;
    }
    ostream& Date::write(std::ostream& ostr) const   //prints the value 
    {

        ostr << year_ << "/";

        ostr.width(2);
        ostr.fill('0');
        ostr << mon_ << "/";

        ostr.width(2);
        ostr.fill('0');
        ostr << day_;
        return ostr;
    }



    std::istream& operator >> (std::istream& istr, Date& D)     //overload the >> operator
    {
        D.read(istr);
        return istr;
    }
    std::ostream& operator<<(std::ostream& ostr,const Date& D)  //overload the << operator
    {
        D.write(ostr);
        return ostr;


    }
}
