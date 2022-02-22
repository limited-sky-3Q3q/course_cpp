//Date.cpp
#include <sstream>
#include <string>
#include<exception>
#include<ctime>
#include<iostream>
#include "Date.h"
using namespace std;

// Date constructor (should do range checking)
Date::Date(int y, int m, int d){
    setDate(y,m,d);
}//设置初始年月日

void Date::setDate(int y,int m,int d){
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
bool Date::checkDate(int y, int m, int d)const{
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

void Date::nextDay(){
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
string Date::toString() const {
    ostringstream output;
    cout<<year<<'/'<<month<<'/'<< day;
    return output.str();
} 