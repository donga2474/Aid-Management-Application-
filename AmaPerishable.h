// AmaPerishable.h
#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include"AmaProduct.h"
#include"Date.h"


namespace sict {
    class AmaPerishable :public AmaProduct {
        Date expiry_;
    public:
        AmaPerishable(char P='N');
        const Date& expiry()const;//getter
        void expiry(const Date &value);//accesssor
        fstream& store(fstream& , bool addNewLine = true)const;
        fstream& load(fstream& file);
        ostream& write(ostream& ostr, bool linear)const;
        istream& read(istream& istr);
    };
}
#endif