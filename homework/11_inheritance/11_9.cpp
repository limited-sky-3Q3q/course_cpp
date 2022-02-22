/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\11_inheritance\11_9.cpp
 * Date: 2020-03-31 09:27:57
 * LastEditTime: 2020-04-15 19:31:46
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
typedef long long ll;

/************************************************
 * 声明部分
 * 所有变量在声明时就已经初始化了
************************************************/
class Package{//按照国内的快递进行定义
	protected:
		string name{NULL};//收件人姓名
		string province{NULL};//省份
		string city{NULL};//城市
		string address{NULL};//详细地址
		int zipCode{0};//邮政编码，7位数
		double weight{0};//单位为千克
		double cost{0};//每千克重量需要多少钱

	public:
		//初始化所有变量
		Package(string, string, string, string, int, double, double);
		Package();
		~Package(){cout<<"\nPackage 析构";};
		virtual double calculateCost();//计算并返回需要多少钱
};

class TwoDayPackage: public Package{//两日包裹
	private:
		double flatFee{0};//固定运输费用
	public:
		//初始化所有变量
		TwoDayPackage(string, string, string, string, int, double, double, double);
		~TwoDayPackage(){cout<<"\nTwoDayPackage析构";};
		double calculateCost();//直接加上额外费用
};

class OvernightPackage:virtual public Package{//两日包裹
	private:
		double additionalFee{0};//每千克需要的额外费用
	public:
		//初始化所有变量
		OvernightPackage(string, string, string, string, int, double, double, double);
		double calculateCost();//要加上额外费用
};

/************************************************
 *定义部分
************************************************/

Package::Package(){};

Package::Package(string n, string p, string ci, string a, int z, double w, double co){
	cout<<"\n调用Package";
	name=n;
	province=p; city=ci; address=a;
	zipCode=z;
	weight=w; cost=co;
}
double Package::calculateCost(){
	return weight*cost;
}
TwoDayPackage::TwoDayPackage(string n, string p, string ci, string a, int z, double w, double co, double f)
:Package(n,p, ci, a, z, w, co),flatFee{f}
{
	/*
	name=n;
	province=p; city=ci; address=a;
	zipCode=z;
	weight=w; cost=co;
	*/
cout<<"\n调用TwoDayPackage构造函数";
}
double TwoDayPackage::calculateCost(){
	return weight*cost + flatFee;
}

OvernightPackage::OvernightPackage(string n, string p, string ci, string a, int z, double w, double co, double ad){
	name=n;
	province=p; city=ci; address=a;
	zipCode=z;
	weight=w; cost=co;
	additionalFee=ad;
}
double OvernightPackage::calculateCost(){
	return weight*(cost+additionalFee);
}

/************************************************
 应题目要求，故只展示calculateCost()函数
************************************************/
int main(){
	Package test1("小明","A省","B市","C街D号楼F门",1234567,3.5,2);
	TwoDayPackage test2("小花","A省","B市","C街D号楼F门",1234567,3.5,2,3);
	OvernightPackage test3("老王","A省","B市","C街D号楼G门",1234567,3.5,2,1);

	cout<<"test1.calculateCost() = "<<test1.calculateCost();
	cout<<"\ntest2.calculateCost() = "<<test2.calculateCost();
	cout<<"\ntest3.calculateCost() = "<<test3.calculateCost();
	
	return 0;
}





