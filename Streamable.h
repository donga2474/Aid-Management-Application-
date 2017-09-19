/*
Nmae::Ravindrakumar Donga
ID:121726120
*/

#pragma once
#ifndef SICT_STREAMABLE_H__
#define SICT_STREAMABLE_H__
#include <iostream>
#include <fstream>
using namespace std;
namespace sict {
    class Streamable {
    public:
      virtual  fstream& store(fstream& file, bool addNewLine = true)const =0;
      virtual fstream& load(std::fstream& file)=0;
      virtual ostream& write(ostream& os, bool linear)const=0;
      virtual istream& read(istream& is)=0;

    };
}
#endif // !SICT_STREAMABLE_H__

