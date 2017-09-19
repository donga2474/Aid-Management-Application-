// AmaProduct.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include"AmaProduct.h"
#include"general.h"
#define COMMA ","
namespace sict {
    
    //constructor
    AmaProduct::AmaProduct(char tag) {
        fileTag_ = tag;
    }
   //unit getter
    const char* AmaProduct::unit()const {
        return  unit_;
    }
    //unit setter
    void AmaProduct::unit(const char* value) {
        strncpy(unit_, value, 11);
        unit_[10] = '\0';
    }
    //store the value to file
    fstream& AmaProduct::store(fstream& file, bool addNewLine)const {
        
           if (addNewLine) {
                file << fileTag_ << COMMA << sku() << COMMA << name() << COMMA << price() << COMMA << taxed() << COMMA << quantity() << COMMA << unit() << COMMA << qtyNeeded() << '\n';
            }
            else
                file << fileTag_ << COMMA << sku() << COMMA << name() << COMMA << price() << COMMA << taxed() << COMMA << quantity() << COMMA << unit() << COMMA << qtyNeeded() ;
            

        
        return file;
    }
    //take the value from the file
    fstream& AmaProduct::load(fstream& file) {
        char sku1[MAX_SKU_LEN];
        char name1[500];
        double price1;
        int tax1;
        int quantity1;
        char unit1[11];
        int quantityneed1;

        file.getline(sku1, MAX_SKU_LEN, ',');
        file.getline(name1, 300, ',');
        
        file >> price1;
        file.ignore();

        file >> tax1;
        file.ignore();

        file >> quantity1;
        file.ignore();

        file.getline(unit1, 12, ',');
        
        file >> quantityneed1;
        file.ignore();

        sku(sku1);
        name(name1);
        price(price1);
        taxed(tax1);
        price(price1);
        unit(unit1);
        quantity(quantity1);
        qtyNeeded(quantityneed1);
        return file;


    }
    //writes the value to the screen
    ostream& AmaProduct::write(ostream& os, bool linear)const {
        if (err_.isClear() == false)
        {
            os << err_;
        }
        else if (linear) {
            os << left << setw(MAX_SKU_LEN) << setfill(' ') << sku() << "|"
                << left << setw(20) << setfill(' ') << name() << "|"
                << right << setw(7) << fixed << setprecision(2) << cost() << "|"
                << right << setw(4) << quantity() << "|"
                << left << setw(10) << unit() << "|"
                << right << setw(4) << qtyNeeded() << "|";
            
                
        }
        else {
            os << "Sku: " << sku() << endl;
            os << "Name: " << name() << endl;
            os << "Price: " << price() << endl;
            if (taxed())
            {
                os << "Price after tax: " << fixed << setprecision(2) << cost() << endl;
            }

            if (taxed() == false)
            {
                os << "Price after tax: " << "N/A" << endl;
            }
            os << "Quantity On Hand: " << quantity()<<" " <<unit()<< endl;
            os << "Quantity Needed: " << qtyNeeded();
            

        }
        return os;
    }
    //reads the value frrom the screen
    istream& AmaProduct::read(istream& istr) {
        char sku1[MAX_SKU_LEN];
        char name1[500];
        double price1;
        char tax1;
        int quantity1;
        char unit1[11];
        int quantityneed1;
        err_.clear();//clears the previously stored message
        if (!istr.fail()) {
            //sku
            cin.ignore();
            cout << "Sku: ";
           // istr >> sku1;
           // sku(sku1);
            istr.getline(sku1, MAX_SKU_LEN, '\n');

            if (istr.fail() == false)
            {
                sku(sku1);
            }
           
            //NAME
            cout << "Name: ";
            //istr >> name1;
            //name(name1);
            istr.getline(name1, 20, '\n');
            if (istr.fail() == false)
            {
                name(name1);
            }
            
            
            //UNIT
            cout << "Unit: ";
            istr.getline(unit1, 11, '\n');
            if (istr.fail() == false)
            {
                unit(unit1);
            }
            //TAXED?
            cout << "Taxed? (y/n): ";
            istr >> tax1;
            switch (tax1)
            {
            case 'Y': taxed(true); break;
            case'y': taxed(true); break;
            case'n': taxed(false); break;
            case'N': taxed(false); break;
            default:err_.message("Only (Y)es or (N)o are acceptable");
                istr.setstate(ios::failbit);
                break;
            }
            //Price
            if (!istr.fail()) {
                cout << "Price: ";
                istr >> price1;
                if (!istr.fail()) {
                    price(price1);
                }
                else {
                    err_.message("Invalid Price Entry");
                    istr.setstate(ios::failbit);
                }
            }
            
            //quantity on hand
            if(!istr.fail()){
                cout << "Quantity On hand: ";
                istr >> quantity1;
                if (!istr.fail()) {
                    quantity(quantity1);

                }
                else {
                    err_.message("Invalid Quantity Entry");
                    istr.setstate(ios::failbit);
                }
            
            }
           

            //quantity Needed
            if (!istr.fail()) {
                cout << "Quantity Needed: ";
                istr >> quantityneed1;
                if (!istr.fail()) {
                    qtyNeeded(quantityneed1);
                    return istr;
                }
                else {
                    err_.message("Invalid Quantity Needed Entry");
                    istr.setstate(ios::failbit);
                }
            }
           
            

        }
        return istr;
    }

}
