/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\12_Object Orient\12_12.cpp
 * Date: 2020-03-31 09:27:57
 * LastEditTime: 2020-04-11 21:43:35
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
#include<vector>
using namespace std;

/************************************************
 11.9题部分，有做略微修改
************************************************/
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
		virtual double calculateCost();//计算并返回需要多少钱
		virtual void get(){
			cout<<"\n收件人："<<name;
			cout<<"\n地址："<<province<<' '<<city<<' '<<address;
			return;
		}
};

class TwoDayPackage:virtual public Package{//两日包裹
	private:
		double flatFee{0};//固定运输费用
	public:
		//初始化所有变量
		TwoDayPackage(string, string, string, string, int, double, double, double);
		double calculateCost();//直接加上额外费用
};

class OvernightPackage:virtual public Package{//隔夜包裹
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
	name=n;
	province=p; city=ci; address=a;
	zipCode=z;
	weight=w; cost=co;
}
double Package::calculateCost(){
	return weight*cost;
}

TwoDayPackage::TwoDayPackage(string n, string p, string ci, string a, int z, double w, double co, double f){
	name=n;
	province=p; city=ci; address=a;
	zipCode=z;
	weight=w; cost=co;
	flatFee=f;
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
12.12题 部分
************************************************/
enum {TDP, OP, END};
int now;
double total{0};
vector<TwoDayPackage>t;
vector<OvernightPackage>o;
Package* PackagePtr{NULL};
//临时数据
string tempName{NULL};//收件人姓名
string tempProvince{NULL};//省份
string tempCity{NULL};//城市
string tempAddress{NULL};//详细地址
int tempZipCode{0};//邮政编码，7位数
double tempWeight{0};//单位为千克
double tempCost{0};//每千克重量需要多少钱

void init(){
	cout<<"\n请输入收件人姓名："; cin>>tempName;
	cout<<"请输入省份："; cin>>tempProvince;
	cout<<"请输入城市："; cin>>tempCity;
	cout<<"请输入详细地址："; cin>>tempAddress;
	cout<<"请输入邮政编码："; cin>>tempZipCode;
	cout<<"请输入包裹重量："; cin>>tempWeight;
	cout<<"请输入每千克重量需要多少钱："; cin>>tempCost;
}

void read(){//读取数据
	for(int i=1; 1; i++){
		cout<<"\n\n现在输入第"<<i<<"个包裹"
			<<"\n现在输入的是(两日包裹输入0,过夜包裹输入1,结束输入输入2):";
		cin>>now;
		switch(now){
			case TDP : {//两日包裹
				init();
				double tempFlatFee;
				cout<<"请输入固定运输费用："; cin>>tempFlatFee;
				t.push_back(TwoDayPackage{tempName,tempProvince,tempCity,tempAddress,tempZipCode,tempWeight,tempCost,tempFlatFee});
				total += t[t.size()-1].calculateCost();
				break;
			}
			case OP :{//过夜包裹
				init();
				double tempmAdditionalFee;
				cout<<"请输入额外运输费用："; cin>>tempmAdditionalFee;
				o.push_back(OvernightPackage{tempName,tempProvince,tempCity,tempAddress,tempZipCode,tempWeight,tempCost,tempmAdditionalFee});
				total += o[o.size()-1].calculateCost();
				break;
			}
			case END :{
				cout<<"\n结束输入\n本次操作共输入了"<<i-1<<"组数据";
				return;
			}
		}
	}
}

int main(){

	read();//读入数据

	cout<<"\n输入了"<<t.size()<<"个两日包裹,"<<o.size()<<"个过夜包裹";
	cout<<"\n费用总和为："<<total<<'\n';
	for(int i=1; i <= t.size(); i++){
		cout<<"\n\n第"<<i<<"个两日包裹：";
		t[i-1].get();
		cout<<"\n费用："<<t[i-1].calculateCost();
	}
	for(int i=1; i <= o.size(); i++){
		cout<<"\n\n第"<<i<<"个过夜包裹：";
		o[i-1].get();
		cout<<"\n费用："<<o[i-1].calculateCost();
	}
	return 0;
}





