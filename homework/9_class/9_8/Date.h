//Date.h
#include <string>
#ifndef DATE_H
#define DATE_H

class Date {
    public:
        explicit Date(int=2000, int=1, int=1);
        std::string toString() const;
        void setDate(int,int,int);
        void nextDay();
        bool checkDate(int,int,int)const;
    private:
        int year;
        int month;
        int day;
};

#endif