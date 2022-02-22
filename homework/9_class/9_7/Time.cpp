//Time.cpp
#include"Time.h"//引用头文件 Time.h
#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<string>

using namespace std;
typedef unsigned int ui;

//设置初始化数据

Time::Time(int h, int m, int s){
	//! 刚刚使用setTime()（只有声明，没有定义），不会生成程序，也不会报错
	setTime(hour, minute, second);
	cout<<"设置成功，初始时间为："<<toStandardString()<<"\n";
}
void Time::setTime(int h, int m, int s){
	cout<<"\n请输入小时：";
	cin>>h;
	setHour(h);
	cout<<"\n请输入分钟：";
	cin>>m;
	setMinute(m);
	cout<<"\n请输入秒：";
	cin>>s;
	setSecond(s);
	return;
}

void Time::setHour(int h){
	if(h>=0 && h<24){
		hour=h;
	}
	else{
		throw invalid_argument("hour must be 0-23");
	}
}
void Time::setMinute(int m){
	if(m>=0 && m<60){
		minute=m;
	}
	else{
		throw invalid_argument("minute must be 0-59");
	}
}
void Time::setSecond(int s){
	if(s>=0 && s<60){
		second=s;
	}
	else{
		throw invalid_argument("second must be 0-59");
	}
}

//设置返回值
ui Time::getHour() const {
	return hour;
}
ui Time::getMinute() const {
	return minute;
}
ui Time::getSecond() const {
	return second;
}

//返回时间
string Time::toUniversalString()const{//24小时制
	ostringstream output;
	cout<<setfill('0')<<setw(2)<<getHour()<<":"
		<<setw(2)<<getMinute()<<":"<<setw(2)<<getSecond();
	return output.str();
}
string Time::toStandardString()const{//12小时制
	cout<< ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12)
		<< ":" << setfill('0') << setw(2) << getMinute() << ":" << setw(2)
		<< getSecond() << (hour < 12 ? " AM" : " PM");
	ostringstream output;
	return output.str();
} 

//+1s
void Time::tick(){
	second++;
	if(second==60){
		second=0;
		minute++;
		if(minute==60){
			minute=0;
			hour++;
			if(hour==24){
				hour=0;
			}
		}
	}
	cout<<"执行+1S的操作，这次操作执行后的时间为：";
	toStandardString();
	return;
}

