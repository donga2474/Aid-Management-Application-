// AmaProduct.h
#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include"Product.h"
#include"ErrorMessage.h"
#include"Streamable.h"
namespace sict {
    class AmaProduct : public Product {
        char fileTag_;
        char unit_[11];
    protected:
        ErrorMessage err_;
    public:
        AmaProduct(char tag='N');
        const char* unit()const;
        void unit(const char* value);
      //  const char fileTag()const;
        fstream& store(fstream& file, bool addNewLine = true)const;
        fstream& load(std::fstream& file);
        ostream& write(ostream& os, bool linear)const;
        istream& read(istream& is);

    };
}

#endif 
