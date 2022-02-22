#include<iostream>
#ifndef DAT_H
#define DAT_H
class DateAndTime{
    
    public:
        explicit DateAndTime();
        std::string toString() const;
        void setDate();
        void nextDay();
        bool checkDate(int,int,int)const;

        void setTime();
        void setHour(int);
        void setMinute(int);
        void setSecond(int);
        
        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        std::string toUniversalString() const; 
        std::string toStandardString() const; 

        void tick();
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute; 
        int second;
};

#endif