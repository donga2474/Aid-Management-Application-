// AmaPersishable.cpp
#include<iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include"AmaPerishable.h"
#include"Product.h"
#include"general.h"

#define COMMA ","
namespace sict {
    //constructor
    AmaPerishable::AmaPerishable(char) :AmaProduct('P'){}
    //sets the expiry date
    const Date& AmaPerishable:: expiry()const {
        return  expiry_;
    }
    //returns the expiry date
    void AmaPerishable::expiry(const Date &value) {
        expiry_ = value;
    }
    fstream& AmaPerishable::store(fstream& file, bool addNewLine )const {
      
        AmaProduct::store(file, false);
        
        if (addNewLine == true) {
            file << COMMA ;
           file << expiry_<<'\n'; 
           // expiry().write(file) << '\n';
        }
        else {
            file << COMMA ;
           cout << expiry_<<'\n';
            //expiry().write(file);
        }
            

        return file;
    }
    fstream& AmaPerishable::load(fstream& file) {
        Date tempdate;
        AmaProduct::load(file);
        file >> tempdate;
        file.ignore();
        expiry(tempdate);
        return file;
    }
    ostream& AmaPerishable::write(ostream& ostr, bool linear)const {
        AmaProduct::write(ostr, linear);
        if (err_.isClear() ) {
            if (linear) {
                ostr << expiry();
                //expiry().write(ostr);
            }
            else if (!linear) {
                ostr << '\n' << "Expiry date: ";
                expiry().write(ostr);
            }
        }
        return ostr;
        

    }
    istream& AmaPerishable::read(istream& istr) {
        Date date;
        AmaProduct::read(istr);
        if (err_.isClear()) {
            cout << "Expiry date (YYYY/MM/DD): ";
            istr >> date;
            if (date.bad()) {
                if (date.errCode() == CIN_FAILED) {
                    err_.message("Invalid Date Entry");
                    istr.setstate(ios::failbit);
                }
                else if (date.errCode() == YEAR_ERROR) {
                    err_.message("Invalid Year in Date Entry");
                    istr.setstate(ios::failbit);
                }
                else if (date.errCode() == MON_ERROR) {
                    err_.message("Invalid Month in Date Entry");
                    istr.setstate(ios::failbit);
                }
                else if (date.errCode() == DAY_ERROR) {
                    err_.message("Invalid Day in Date Entry");
                    istr.setstate(ios::failbit);
                }
            }
            else expiry(date);
           
        }
        return istr;
    }
}
