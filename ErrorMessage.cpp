// Final Project Milestone 2
// Version 1.0
// Date	
// Author	Ravindrakumar donga
//id 121726120
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include "ErrorMessage.h"
namespace sict
{
    ErrorMessage::ErrorMessage()
    {
        message_ = nullptr;
    }
    ErrorMessage::ErrorMessage(const char* errorMessage)
    {
        message_ = nullptr;
        message(errorMessage);
    }
    ErrorMessage& ErrorMessage::operator=(const char* errorMessage)
    {
        clear();
        message(errorMessage);
        
        return *this;
    }

    void ErrorMessage::clear()
    {
        delete[] message_;
        message_ = nullptr;
    }
    bool ErrorMessage::isClear()const
    {
        if (message_ == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void ErrorMessage::message(const char* value)
    {
        delete[] message_;
        int length = strlen(value);
        message_ = new char[length + 1];
        strncpy(message_, value,length);
        message_[length] = '\0';
    }
    const char* ErrorMessage::message()const
    {
        return message_;
    }
    ErrorMessage::~ErrorMessage()
    {
        delete[] message_;
    }
    std::ostream& ErrorMessage::write(std::ostream& write)const
    {
        if (isClear() == false)
        {
            write << message_;
        }
        return write;
    }
    std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& errorMessage)
    {
        errorMessage.write(ostr);
        return ostr;
    }
}
