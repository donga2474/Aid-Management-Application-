/*
Nmae::Ravindrakumar Donga
ID:121726120
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"Streamable.h"
#include"general.h"
#include"Product.h"
using namespace std;
namespace sict {
    //constructors
    Product::Product() {
        sku_[0] = '\0';
        name_ = nullptr;
        price_ = 0.0;
        taxed_ = true;
        quantity_ = 0;
        qtyNeeded_ = 0;
    }
    //constructor with five parameter
    Product::Product(const char* sk,const char* nam, bool tax, double prize, int nqty)
    {
        sku(sk);
        name(nam);
        quantity(0);
        taxed(tax);
        qtyNeeded(nqty);
        price(prize);
        
    }
  
    //copy constructor
    Product::Product(Product& p) 
    {
        name_ = nullptr;    
        *this = p;
                
    }
    //destructor
    Product:: ~Product() {
        
       delete[] name_; 
       name_ = nullptr;
       
        
     }
    //overload of =operator
    Product& Product::operator=(const Product& p)
    {
        
        if (this != &p) //checks wether its the same adress or not
        {
            sku(p.sku_);
            quantity(p.quantity_);
            taxed(p.taxed_);
            qtyNeeded(p.qtyNeeded_);
            price(p.price_);
            name(p.name_);
          
        }
        
        
        return *this;
    }

    //setter functions
    void Product::sku(const char* sku) {
        strncpy(sku_, sku, MAX_SKU_LEN);
        sku_[MAX_SKU_LEN] = '\0';
    }



    void Product::price(const double price)
    {
        price_ = price;
    }



    void Product::name(const char* name)
    {
        int size = strlen(name);                 
        name_ = new char[size+1];
        strncpy(name_, name, size+1);
        name_[size] = '\0';        
    }

    void Product::taxed(const bool taxed) {
        taxed_ = taxed;
    }
    void Product::quantity(const int quantity) {
        quantity_ = quantity;
    }
    void Product::qtyNeeded(const int qtyneeded) {
        qtyNeeded_ = qtyneeded;
    }

    //getter function
   const char* Product::sku()const {
        return sku_;
    }
   double Product::price()const {
       return price_;
   }
   const char* Product::name()const {
       return name_;
   }
   bool Product::taxed()const {
       return taxed_;
   }
   int Product ::quantity()const {
       return quantity_;
   }
   int Product ::qtyNeeded()const {
       return qtyNeeded_;
   }
   double Product::cost()const {
       double total;
       if (taxed_ ==true) {
           total=price_*(TAX+1);        
       }
       else 
           total=price_;
       return total;
   }
   bool Product::isEmpty()const {
       return (name_ == nullptr);
   }



   //overload
   bool Product::operator==(const char* sk) {
       if (strcmp(sk, sku_) == 0) {
           return true;
      }
       else return false;
   }
   int Product::operator+=(int qt) {
       quantity_ = quantity_ + qt;
       return quantity_;

   }
   int Product::operator-=(int qt) {
       quantity_ = quantity_ - qt;
       return quantity_;
   }

   //Non-Member operator overload:
   double operator+=(double&left, const Product& right) {
       double q = right.quantity();
       double c = right.cost();
     double totalprice= (q) * (c);
     left = (left)+totalprice;
       return left;
   }
   
  
   std::istream& operator >> (std::istream& istr,  Product& p) {
       p.read(istr);
       return istr;

   }
   std::ostream& operator<<(std::ostream& ostr, const Product& p) {
       bool linear=true;
       p.write(ostr,linear);
       return ostr;
   }
}