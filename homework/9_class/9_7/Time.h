//Time.h
#include<string>
#ifndef TIME_H
#define TIME_H
class Time {
public:
    explicit Time(int=0, int=0, int=0);//默认构造函数
    

    // set functions
    void setTime(int, int, int); // set hour, minute, second
    void setHour(int); // set hour (after validation)
    void setMinute(int); // set minute (after validation)
    void setSecond(int); // set second (after validation)
    
    // get functions
    int getHour() const; // return hour
    int getMinute() const; // return minute
    int getSecond() const; // return second

    //+1s
    void tick();

    std::string toUniversalString() const; // 24-hour time format string
    std::string toStandardString() const; // 12-hour time format string
private:
    int hour{0}; // 0 - 23 (24-hour clock format)
    int minute{0}; // 0 - 59
    int second{0}; // 0 - 59
};

#endif