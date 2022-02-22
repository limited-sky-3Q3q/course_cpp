//main.cpp
#include"DateAndTime.h"
#include<iostream>
using namespace std;
int main(){
    DateAndTime a;
    cout<<"初始化成功，初始时间为：";
    a.toString();
    cout<<" ";
    a.toStandardString();
    int n;
    for(int i=1; i<=n; i++){
        cout<<"\n现在进行第"<<i<<"次操作";
        a.tick();
        cout<<"\n本次操作完成，目前的日期为：";
        a.toString();
        cout<<" ";
        a.toStandardString();
    }
    cout<<"\n所有操作完成，程序结束";
}