//main.cpp
#include"Date.h"
#include<iostream>
using namespace std;
int main(){
    Date a;
    //a.toString();
    int n;
    cout<<"\n请输入要调用nextDay函数的次数：";
    cin>>n;
    for(int i=1; i<=n; i++){
        cout<<"\n现在进行第"<<i<<"次操作";
        a.nextDay();
        cout<<"\n本次操作完成，目前的日期为：";
        a.toString();
    }
    cout<<"\n所有操作完成，程序结束";
}