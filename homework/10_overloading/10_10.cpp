/******************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\10_overloading\10_10.cpp
 * Date: 2020-03-22 10:49:22
 * LastEditTime: 2020-03-22 11:49:52
 * !今日运势: 吉，无bug
******************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
typedef long long ll;
int gcd(int a,int b){//求最大公因数
    if(a==0)return b;
    return gcd(b%a, a);
}

class RationalNumber{
    friend ostream &operator<<(ostream&, const RationalNumber&);//重载输出运算符

    private:
        int numerator=0;//分子
        int denominator=1;//分母

    public:
        RationalNumber();
        RationalNumber(int, int);
        //化简分数
        RationalNumber simplify(const RationalNumber)const;
        //重载二元运算符
        RationalNumber operator+(const RationalNumber)const;
        RationalNumber operator-(const RationalNumber)const;
        RationalNumber operator*(const RationalNumber)const;
        RationalNumber operator/(const RationalNumber)const;
        //重载逻辑运算符
        bool operator==(const RationalNumber&)const;
        bool operator!=(const RationalNumber)const;
        bool operator>(const RationalNumber)const;
        bool operator<(const RationalNumber)const;
        bool operator>=(const RationalNumber)const;
        bool operator<=(const RationalNumber)const;
        
        
};
RationalNumber::RationalNumber(){
    numerator=0;//分子
    denominator=1;//分母
}
RationalNumber::RationalNumber(int a, int b){//a,b分别代表分子分母
    if(b==0){//检查分母是否为0
        throw invalid_argument("分母为0");
    }
    if(b<0){
        b=-b;
        a=-a;
    }
    //化简分数
    if(a==0){
        numerator=0;
        denominator=1;
        return;
    }
    numerator=a/gcd(abs(a),abs(b));
    denominator=b/gcd(abs(a),abs(b));
}
/******************************
 化简分数
******************************/
RationalNumber RationalNumber::simplify(const RationalNumber temp1)const{
    RationalNumber temp2=temp1;
    //a,b分别代表分子分母
    int a=temp2.numerator, b=temp2.denominator;
    if(b<0){
        b=-b;
        a=-a;
    }
    if(a==0){
        temp2.numerator=0;
        temp2.denominator=1;
        return temp2;
    }
    temp2.numerator=a/gcd(a,b);
    temp2.denominator=b/gcd(a,b);
    return temp2;
}
/******************************
 重载输出运算符
******************************/
ostream &operator<<(ostream& out, const RationalNumber&temp){
    if(temp.numerator==0)out<<0;
    else out<<temp.numerator<<'/'<<temp.denominator;
    return out;
}
/******************************
 //重载二元运算符
******************************/

RationalNumber RationalNumber::operator+(const RationalNumber temp)const{
    RationalNumber ans;
    ans.denominator=this->denominator*temp.denominator;
    ans.numerator=this->denominator*temp.numerator+temp.denominator*this->numerator;
    return simplify(ans);
}
RationalNumber RationalNumber::operator-(const RationalNumber temp)const{
    RationalNumber ans;
    ans.denominator=this->denominator*temp.denominator;
    ans.numerator=this->denominator*(-temp.numerator)+temp.denominator*this->numerator;
    return simplify(ans);
}
RationalNumber RationalNumber::operator*(const RationalNumber temp)const{
    RationalNumber ans;
    ans.denominator=this->denominator*temp.denominator;
    ans.numerator=temp.numerator*this->numerator;
    return simplify(ans);
}
RationalNumber RationalNumber::operator/(const RationalNumber temp)const{
    RationalNumber ans;
    ans.denominator=this->denominator*temp.numerator;
    ans.numerator=temp.denominator*this->numerator;
    return simplify(ans);
}

/******************************
 重载逻辑运算符
******************************/

bool RationalNumber::operator==(const RationalNumber &temp)const{
    RationalNumber ans=*this-temp;
    if(ans.numerator==0)return true;
    else return false;
}
bool RationalNumber::operator!=(const RationalNumber temp)const{
    return !(*this==temp);
}
bool RationalNumber::operator>(const RationalNumber temp)const{
    RationalNumber ans=*this-temp;
    if(ans.numerator>0)return true;
    else return false;
}
bool RationalNumber::operator<(const RationalNumber temp)const{
    return !(*this>=temp);
}
bool RationalNumber::operator>=(const RationalNumber temp)const{
    return (*this>temp ||*this==temp);
}
bool RationalNumber::operator<=(const RationalNumber temp)const{
    return (*this<temp ||*this==temp);
}
int main(){
	RationalNumber a,b(1,2),c(3,9),d(4,-10);
    cout<<"a = "<<a<<"\nb = "<<b<<"\nc = "<<c<<"\nd = "<<d;
    
    cout<<"\n\nb + c = "<<b+c;
    cout<<"\nb - c = "<<b-c;
    cout<<"\nb * c = "<<b*c;
    cout<<"\nb / c = "<<b/c;
    cout<<"\nb == c = "<<(b==c);
	return 0;
}
