//Final Project Milestone 2
// Version 1.0
// Date 
// Author	Ravindrakumar donga
//id 121726120
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#ifndef SICT_ERRORMESSAHE_H
#define SICT_ERRORMESSAGE_H
namespace sict {

    class ErrorMessage
    {
        char* message_;
    public:
        ErrorMessage();
        ErrorMessage(const char* errorMessage);
        ErrorMessage(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const char* errorMessage);
        virtual ~ErrorMessage();
        void clear();
        bool isClear()const;
        void message(const char* value);
        const char* message()const;
        std::ostream& write(std::ostream& ostr)const;

    };

    std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& errorMessage);
}
#endif 

