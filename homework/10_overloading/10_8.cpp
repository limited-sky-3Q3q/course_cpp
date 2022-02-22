
/**
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\10_overloading\10_8.cpp
 * Date: 2020-03-21 17:45:23
 * LastEditTime: 2020-03-21 19:42:18
 * ! 今日运势: 吉，无bug
**/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
typedef long long ll;

/******************************
 * 类声明部分
******************************/
#ifndef COMPLEX_H
#define COMPLEX_H
class Complex {
public:
    explicit Complex(double = 0.0, double = 0.0);
    Complex operator+(const Complex&)const;
    Complex operator-(const Complex&)const;
    Complex operator*(const Complex&)const;
    friend istream &operator>>(istream&, Complex&);
    friend ostream &operator<<(ostream&, const Complex&);
    bool operator==(const Complex&)const;
    bool operator!=(const Complex&)const;
private:
    double real=0;//实数部分
    double imaginary=0;//虚数部分v
};
#endif

/******************************
 * 定义函数部分
******************************/
Complex::Complex(double realPart, double imaginaryPart)
: real{realPart}, imaginary{imaginaryPart} {}

Complex Complex::operator+(const Complex& operand2) const {
return Complex{real + operand2.real, imaginary + operand2.imaginary};
}
Complex Complex::operator-(const Complex& operand2) const {
return Complex{real - operand2.real, imaginary - operand2.imaginary};
} 
Complex Complex::operator*(const Complex &temp)const{
    return Complex{
        real*temp.real - imaginary*temp.imaginary, 
        real*temp.imaginary+temp.real*imaginary
    };
}

istream &operator>>(istream &in, Complex &temp){
    in>>temp.real>>temp.imaginary;
    return in;
}
ostream &operator<<(ostream &out, const Complex &temp){
    out<<'('<<temp.real<<','<<temp.imaginary<<'i'<<')';
    return out;
}

bool Complex::operator==(const Complex&temp)const{
    return (temp.real==real&&temp.imaginary==imaginary)?true:false;
}
bool Complex::operator!=(const Complex&temp)const{
    return !(*this==temp);
}

/******************************
 *main函数部分
******************************/
int main(){
    Complex x;
    Complex y{4.3, 8.2};
    Complex z{3.3, 1.1};
    cout<<"x: "<<x<<"\ny: "<<y<<"\nz: "<<z;

    x = y + z;
    cout<<"\n\nx = y + z:\n"<<x<<" = "<<y<<" + "<<z;
    
    x = y - z;
    cout<<"\n\nx = y - z:\n"<<x<<" = "<<y<<" - "<<z;

    x = y * z;
    cout<<"\n\nx = y * z:\n"<<x<<" = "<<y<<" * "<<z;

    cout<<"输入新的y和z，格式为‘实数+空格+虚数’：\n";
    cin>>y>>z;
    cout<<"新的y: "<<y<<"\n新的z: "<<z;
    
    cout<<"\n\ny==z: "<<(y==z);
    cout<<"\ny!=z: "<<(y!=z);
	return 0;
}
