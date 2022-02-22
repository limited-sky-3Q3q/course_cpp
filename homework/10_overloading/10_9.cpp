/******************************
 * TODO Auther   : by SR
 * FilePath: \vscodefile\2020\2020\homework\10_overloading\10_9.cpp
 * Date          : 2020-03-21 19:41:46
 * LastEditTime: 2020-03-22 11:50:02
 * !今日运势         : 吉，无bug
******************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
#include<array>
using namespace std;
typedef long long ll;

/******************************
 *类声明部分
******************************/
#ifndef HugeInteger_H
#define HugeInteger_H
class HugeInteger {
	friend ostream& operator<<(ostream&, const HugeInteger&);
public:
	static const int digits{40}; // maximum digits in a HugeInteger

	int length()const;//返回大数的长度
	//构造函数的重载
	HugeInteger(long = 0);//以长度为64位以下的整数初始化时
	HugeInteger(const string&);//以长度为64位以上的整数初始化时

	//与大数，整数，字符串的加法运算符重载
	HugeInteger operator+(const HugeInteger&) const;
	HugeInteger operator+(int) const;
	HugeInteger operator+(const std::string&) const;
	//与大数，整数，字符串的乘法运算符重载
	HugeInteger operator*(const HugeInteger&) const;
	HugeInteger operator*(const int) const;
	HugeInteger operator*(const std::string&) const;
	//与大数，整数，字符串的减法运算符重载
	HugeInteger operator-(const HugeInteger&) const;
	HugeInteger operator-(const int) const;
	HugeInteger operator-(const std::string&) const;
	//与大数，整数，字符串的除法运算符重载
	HugeInteger operator/(const HugeInteger&) const;
	HugeInteger operator/(const int) const;
	HugeInteger operator/(const std::string&) const;
	//关系运算符重载
	bool operator==(const HugeInteger&) const;
	bool operator!=(const HugeInteger&) const;
	bool operator>(const HugeInteger&) const;
	bool operator<(const HugeInteger&) const;
	bool operator>=(const HugeInteger&) const;
	bool operator<=(const HugeInteger&) const;
	
private:
	array<short, digits> integer{}; // default init to 0s
};
#endif
/******************************
 类函数定义部分
******************************/
//#include <cctype> // isdigit function prototype
int HugeInteger::length()const{
	int i;
	for(i=0; (i<digits)&&(0==integer[i]); ++i){}
	return digits-i;
}

HugeInteger::HugeInteger(long value) {
	for (int j=digits-1; value != 0 && j >= 0; j--){
		integer[j] = value % 10;
		value /= 10;
	}
}
HugeInteger::HugeInteger(const string& number) {
	int length=number.size();
	for (int j=digits-length, k=0; j<digits; ++j, ++k){
		if (isdigit(number[k])){
		integer[j] = number[k] - '0';
		}
	}
} 
ostream& operator<<(ostream& output, const HugeInteger& num) {
	int i;
	//跳过前面的0
	for (i = 0; (i < HugeInteger::digits) && (0 == num.integer[i]); ++i){}

	if (i == HugeInteger::digits) {
		output << 0;
		}
		else {
		for (; i < HugeInteger::digits; ++i) {
				output << num.integer[i];
		}
	}
	return output;
}

HugeInteger HugeInteger::operator+(const HugeInteger& op2)const{
	HugeInteger temp;
	int carry = 0;
	for (int i{digits - 1}; i >= 0; i--){
		temp.integer[i] = integer[i]+op2.integer[i]+carry;
	//判断是否进位
	if (temp.integer[i] > 9) { 
		temp.integer[i] %= 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}
	return temp;
}
HugeInteger HugeInteger::operator+(int op2) const {
return *this + HugeInteger(op2);
}
HugeInteger HugeInteger::operator+(const string& op2) const {
return *this + HugeInteger(op2);
}

/******************************
 实现乘法
******************************/
HugeInteger HugeInteger::operator*(const HugeInteger&op2)const{
	HugeInteger temp(0),temp2(0);
	int length= op2.length();
	for(int j=0; j<length; j++){
		int pos=digits-1-j;//现在计算第几位
		temp=0;
		for(int i=1; i<=op2.integer[pos]; i++){
			temp = temp+*this;
		}
		int len2=temp.length();
		//左移j位
		for(int i=len2; i>0; i--){
			if(digits-i<0)continue;
			int t=temp.integer[digits-i];
			temp.integer[digits-i]=0;
			temp.integer[digits-i-j]=t;
		}
		temp2 = temp + temp2;
	}
	return temp2;
}
HugeInteger HugeInteger::operator*(const int op2) const{
	return *this + HugeInteger(op2);
}
HugeInteger HugeInteger::operator*(const std::string&op2) const{
	return *this + HugeInteger(op2);
}
/******************************
 实现减法
******************************/
HugeInteger HugeInteger::operator-(const HugeInteger&temp) const{
	HugeInteger left=*this;
	int length=temp.length(),pos,carry=0;
	for(int i=1; i<=length; i++){
		pos=digits-i;//目前计算的位
		left.integer[pos] -=temp.integer[pos];
		if(left.integer[pos]<0){
			left.integer[pos]+=10;
			left.integer[pos-1]--;
		}
	}
	return left;
}
HugeInteger HugeInteger::operator-(const int temp) const{
	return *this-HugeInteger(temp);
}
HugeInteger HugeInteger::operator-(const std::string&temp) const{
	return *this-HugeInteger(temp);
}
/******************************
 实现除法
******************************/
HugeInteger HugeInteger::operator/(const HugeInteger&op2) const{
	HugeInteger temp1=*this,//左数的复制
				temp2(op2),//右数的复制
				//temp3(0),//用于比较
				ans(0);
	int pos=length()-op2.length();//需要向左移动的位数
	for(int i=temp2.length(); i>0; i--){
		if(digits-i<0)continue;
		int t=temp2.integer[digits-i];
		temp2.integer[digits-i]=0;
		temp2.integer[digits-i-pos]=t;
	}
	for(int i= pos; i>=0; i--){
		while(temp1>=temp2){//当可以继续除时
			temp1 = temp1-temp2;
			ans.integer[digits-1-i]++;
		}
		//右移一位
		if(i-1<0)break;//最后一次时，不执行下方的代码，暨不进行右移
		for(int i=1; i<=temp2.length(); i++){
			//if(digits-i<0)continue;
			int t=temp2.integer[digits-i];
			temp2.integer[digits-i]=0;
			temp2.integer[digits-i+1]=t;
		}
	}
	return ans;
}
HugeInteger HugeInteger::operator/(const int temp) const{
	return *this/HugeInteger(temp);
}
HugeInteger HugeInteger::operator/(const std::string&temp) const{
	return *this/HugeInteger(temp);
}
/******************************
 关系运算符重载
******************************/
bool HugeInteger::operator==(const HugeInteger&temp) const{
	return !(*this!=temp);
}
bool HugeInteger::operator!=(const HugeInteger&temp) const{
	if(this->length()!=temp.length())return true;
	int len=this->length();
	for(int i=digits-1; i>digits-1-len; i--){
		if(integer[i]!=temp.integer[i]){
			return true;
		}
	}
	return false;
}
bool HugeInteger::operator>(const HugeInteger&temp) const{
	if(this->length()>temp.length())return true;
	if(this->length()<temp.length())return false;
	int len=this->length();
	for(int i=digits-len; i<digits; i++){
		if(integer[i]>temp.integer[i]){
			return true;
		}
		else if(integer[i]<temp.integer[i]){
			return false;
		}
		continue;
	}
	return false;
}
bool HugeInteger::operator<(const HugeInteger&temp) const{
	return !(*this>temp || *this==temp);
}
bool HugeInteger::operator>=(const HugeInteger&temp) const{
	return (*this>temp || *this==temp);
}
bool HugeInteger::operator<=(const HugeInteger&temp) const{
	return (*this<temp || *this==temp);
}
int main(){
	HugeInteger a("123456789012345678901234567890");
	//cout<<(a/1234567890);
	HugeInteger n1{7654321};
	HugeInteger n2{7891234};
	HugeInteger n3{"1299999999999999999999999"};
	HugeInteger n4{"1"};
	HugeInteger n5;

	cout << "n1 is " << n1 << "\nn2 is " << n2
	<< "\nn3 is " << n3 << "\nn4 is " << n4
	<< "\nn5 is " << n5 << "\n\n";

	n5 = n1 + n2;
	cout << n1 << " + " << n2 << " = " << n5 << "\n\n";

	cout << n3 << " + " << n4 << "\n= " << (n3 + n4) << "\n\n";
	n5 = n1 + 9;
	cout << n1 << " + " << 9 << " = " << n5 << "\n\n";

	n5 = n2 + "10000";
	cout << n2 << " + " << "10000" << " = " << n5 <<"\n\n";
	
	cout<<n2<<" - "<<n1<<" = "<<n2-n1<<"\n\n";
	n3 = n3+1;
	cout<<n3<<" * "<<123<<"\n= "<<n3*123<<"\n\n";

	cout<<n2<<" / "<<8<<" = "<<n3/8<<"\n";
	//cout<<(n1==n2);
	return 0;
}
