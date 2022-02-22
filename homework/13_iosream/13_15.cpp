/******************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\13_iosream\13_15.cpp
 * Date: 2020-03-28 16:08:21
 * LastEditTime: 2020-03-28 16:17:03
 * !今日运势: 吉，无bug
******************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
typedef long long ll;

class point{
    private:
        int x{0},y{0};
        bool failBit{false};//错误位默认为false
    public:
        friend istream &operator>>(istream&, point&);
        friend ostream &operator<<(ostream&, point&);
};
istream &operator>>(istream &in, point &temp){
    in>>temp.x;//>>temp.y;
    if(cin.fail()){//输入的坐标数据不合法
        temp.failBit=true;
        in.clear();
        string str;
        in>>str;//跳过当前段的非法数据
    }
    in>>temp.y;
    if(cin.fail()){//输入的坐标数据不合法
        temp.failBit=true;
        in.clear();
        string str;
        in>>str;//跳过当前段的非法数据
    }
    return in;
}
ostream &operator<<(ostream &out, point &temp){
    if(temp.failBit)return out;
    out<<'('<<temp.x<<','<<temp.y<<')';
    return out;
}

int main(){
    point test1, test2, test3;
    cout<<"请输入3个坐标的数据:";
/************************************************
    浮点数也是类型错误
************************************************/
    //输入1.2 3 A 4 123 456
    cin>>test1>>test2>>test3;

    cout<<"现在输出test1:"<<test1<<"\n";
    cout<<"现在输出test2:"<<test2<<"\n";
    cout<<"现在输出test3:"<<test3<<"\n";
	return 0;
}
