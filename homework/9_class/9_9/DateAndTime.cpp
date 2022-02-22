//DateAndTime.cpp
#include"DateAndTime.h"
#include<sstream>
#include<string>
#include<exception>
#include<ctime>
#include<iostream>
#include<iomanip>
using namespace std;

DateAndTime::DateAndTime(){
    setDate();
    setTime();
}
void DateAndTime::setDate(){
    int y,m,d;
    cout<<"请输入年份：";
    cin>>y;
    cout<<"请输入月份：";
    cin>>m;
    cout<<"请输入日期：";
    cin>>d;
    if(!checkDate(y,m,d)){//检查合理性
        throw invalid_argument("请输入正确的日期");
    }
    year=y; month=m; day=d;
}
bool DateAndTime::checkDate(int y, int m, int d)const{
    //判断月份
    if(m<1 || m>12){
            return false;
        }
    
    int a=0;
    switch(m){
        case 1:case 3:case 5:
        case 7:case 8:case 10:
        case 12:
            a=1;
            break;
        case 4:case 6:
        case 9:case 11:
            a=2;
            break;
        case 2:
            a=3;
            break;   
    }
    //判断日期
    if(a==1){
        return (d>=1 && d<=31)?true:false;
    }
    if(a==2){
        return (d>=1 && d<=30)?true:false;
    }
    if(a==3){
        //闰年
        if((y%4==0 && y%100!=0) || y%400==0){
            return (d>=1 && d<=29)?true:false;
        }
        else{//不是闰年
            return (d>=1 && d<=28)?true:false;
        }
    }
    return false;
}

void DateAndTime::nextDay(){
    day++;
    if(checkDate(year,month,day)){
        return;
    }

    day=1;
    month++;
    if(checkDate(year,month,day)){
        return;
    }

    month=1;
    year++;
    if(checkDate(year,month,day)){
        return;
    }
}
//输出日期，格式为 年/月/日
string DateAndTime::toString() const {
    ostringstream output;
    cout<<year<<'/'<<month<<'/'<< day;
    return output.str();
} 

//time

void DateAndTime::setTime(){
    int h, m, s;
	cout<<"请输入小时：";
	cin>>h;
	setHour(h);
	cout<<"请输入分钟：";
	cin>>m;
	setMinute(m);
	cout<<"请输入秒：";
	cin>>s;
	setSecond(s);
	return;
}

void DateAndTime::setHour(int h){
	if(h>=0 && h<24){
		hour=h;
	}
	else{
		throw invalid_argument("hour must be 0-23");
	}
}
void DateAndTime::setMinute(int m){
	if(m>=0 && m<60){
		minute=m;
	}
	else{
		throw invalid_argument("minute must be 0-59");
	}
}
void DateAndTime::setSecond(int s){
	if(s>=0 && s<60){
		second=s;
	}
	else{
		throw invalid_argument("second must be 0-59");
	}
}

//设置返回值
int DateAndTime::getHour() const {
	return hour;
}
int DateAndTime::getMinute() const {
	return minute;
}
int DateAndTime::getSecond() const {
	return second;
}

//返回时间
string DateAndTime::toUniversalString()const{//24小时制
	ostringstream output;
	cout<<setfill('0')<<setw(2)<<getHour()<<":"
		<<setw(2)<<getMinute()<<":"<<setw(2)<<getSecond();
	return output.str();
}
string DateAndTime::toStandardString()const{//12小时制
	cout<< ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12)
		<< ":" << setfill('0') << setw(2) << getMinute() << ":" << setw(2)
		<< getSecond() << (hour < 12 ? " AM" : " PM");
	ostringstream output;
	return output.str();
} 

//+1s
void DateAndTime::tick(){
	second++;
	if(second==60){
		second=0;
		minute++;
		if(minute==60){
			minute=0;
			hour++;
			if(hour==24){
                nextDay();
				hour=0;
			}
		}
	}
	return;
}

