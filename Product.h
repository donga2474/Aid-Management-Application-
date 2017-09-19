// Product.h
/*
Nmae::Ravindrakumar Donga
ID:121726120
*/
#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__
#include "general.h"
#include "Streamable.h"

namespace sict {
    class Product:public Streamable {
        char sku_[MAX_SKU_LEN + 1];
        char* name_;
        double price_;
        bool taxed_;
        int quantity_;
        int qtyNeeded_;
    public:
        Product();
        Product(const char* sku,const char* name, bool taxed=true, double price=0.0, int nqty=0);
        Product(Product& p);
        virtual~Product();
        Product& operator=(const Product& p);
        void sku(const char* sku);
        void price(const double price);
        void name(const char* name);
        void taxed(const bool taxed);
        void quantity(const int quantity);
        void qtyNeeded(const int qtyneeded);

        const char* sku()const;
        double price()const;
        const char*  name()const;
        bool taxed()const;
        int quantity()const;
        int qtyNeeded()const;
        double cost()const;
        bool isEmpty()const;

        bool operator==(const char* sk);
        int operator+=(int qt);
        int operator-=(int);

    };
    double operator+=(double&, const Product&);
    std::istream& operator >> (std::istream& istr,  Product& p);
    std::ostream& operator<<(std::ostream& ostr, const Product& p);

    
}
#endif // !SICT_PRODUCT_H__
