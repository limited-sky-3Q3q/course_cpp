/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\12_Object Orient\12_13.cpp
 * Date: 2020-03-31 14:25:37
 * LastEditTime: 2020-04-11 19:41:20
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
#include<vector>
using namespace std;
typedef long long ll;

/************************************************
 11.10题部分，有做略微修改
************************************************/
/************************************************
 *声明部分
************************************************/
class Account{
	protected:
		double balance{0};
	public:
		Account(double);
		Account(){};
		bool check(double);//检查是否大于等于0

		void credit(double);//存钱
		void debit(double);//取钱,要检查
		
		double getBalance();//查询余额

		//只是在基类中声明，不具有实际意义
		double interestRate;
		virtual double calculateInterest(){};
		double transactionFee{0};
		virtual void credit(){};
		virtual void debit(){};
		virtual double getTransactionFee(){};
};
class SavingsAccount : virtual public Account{//储蓄账户
	private:
		double interestRate{0};//百分比，interestRate%
	public:
		SavingsAccount(double, double);
		double calculateInterest();//返回利息
};
class CheckingAccount : virtual public Account{//支票账户
	private:
		double transactionFee{0};//手续费
	public:
		CheckingAccount(double, double);
		void credit(double);//存钱
		void debit(double);//取钱,要检查
		double getTransactionFee(){
			return transactionFee;
		}
};

/************************************************
 *定义部分
************************************************/

double Account::getBalance(){
	return balance;
}
void Account::debit(double temp){
	if(balance < temp){//钱不够
		cout<<"\n要取的金额不足，本次操作失败。";
	}
	else{
		balance -= temp;
		cout<<"\n操作成功，本次操作取出"<<temp<<"。";
	}
}
void Account::credit(double temp){
	if(temp>0){
		balance += temp;
		cout<<"\n存储金额增加"<<temp<<"。";
	}
	else{
		cout<<"\n输入的数据不合法，本次存储无效。";
	}
}
Account::Account(double b){
	if(!check(b)){
		cout<<"\n初始值小于0";
		balance=0;
	}
	else{
		balance=b;
	}
}
bool Account::check(double b){
	return b>=0;
}

SavingsAccount::SavingsAccount(double b, double i){
	if(!check(b)){
		cout<<"\nbalance初始值小于0";
		balance=0;
	}
	else{
		balance=b;
	}
	if(i<0){
		cout<<"\ninterestRate初始值小于0";
		balance=0;
	}
	else{
		interestRate=i;
	}
}
double SavingsAccount::calculateInterest(){//返回利息
	return interestRate*balance/100;
}

CheckingAccount::CheckingAccount(double b, double f){
	if(!check(b)){
		cout<<"\nbalance初始值小于0";
		balance=0;
	}
	else{
		balance=b;
	}
	if(f<0){
		cout<<"\ntransactionFee初始值小于0";
		balance=0;
	}
	else{
		transactionFee=f;
	}
}
void CheckingAccount::credit(double temp){//存钱
	if(temp-transactionFee>0){
		balance += temp-transactionFee;
		cout<<"\n扣除手续费后，存储金额增加"<<temp-transactionFee<<"。";
	}
	else{
		cout<<"\n输入的数据不合法，本次存储无效。";
	}
}
void CheckingAccount::debit(double temp){//取钱,要检查
	if(balance-transactionFee < temp){//钱不够
		cout<<"\n要取的金额不足，本次操作失败。";
	}
	else{
		balance -= temp+transactionFee;
		cout<<"\n操作成功，本次操作取出"<<temp<<"。";
	}
}
/************************************************
 * 测试部分
************************************************/

vector<Account*>sa;//储蓄账户数组
vector<Account*>ca;//支票账户数组
double tempA,tempB,totalInterest{0};
void read(){//读取数据
	enum{SA,CA,END};
	int now;
	for(int i=1; 1; i++){
		cout<<"\n\n现在输入第"<<i<<"个账户"
			<<"\n现在输入的是(储蓄账户输入0,支票账户输入1,结束输入输入2):";
		cin>>now;
		switch(now){
			case SA : {//储蓄账户
				cout<<"请输入账户的初始余额："; cin>>tempA;
				cout<<"请输入账户年利率(直接输入百分比的数字，不需要带符号)："; cin>>tempB;
				Account* temp;
				sa.push_back(temp);
				sa[sa.size()-1]= new SavingsAccount(tempA, tempB);
				
				cout<<"\n是否进行存取款操作（取款请输入0，存款请输入1，否则请输入2）：";
				while(cin>>now){
					if(now==2)break;
					switch(now){
						case 0:{
							double temp;
							cout<<"\n请输入取款金额：";cin>>temp;
							sa[sa.size()-1]->debit(temp);
							break;
						}
						case 1:{
							double temp;
							cout<<"\n请输入存款金额：";cin>>temp;
							sa[sa.size()-1]->credit(temp);
							break;
						}
						default : cout<<"\n请输入正确的数据";
					}
					cout<<"\n是否继续进行存取款操作（取款请输入0，存款请输入1，否则请输入2）：";
				}

				
				//存款加上利息
				totalInterest += sa[sa.size()-1]->calculateInterest();
				sa[sa.size()-1]->credit(sa[sa.size()-1]->calculateInterest());
				cout<<"\n本次操作结束，该账户的存款已加上利息";
				break;
			}
			case CA :{//支票账户
				cout<<"请输入账户余额："; cin>>tempA;
				cout<<"请输入手续费："; cin>>tempB;
				Account* temp;
				ca.push_back(temp);
				ca[ca.size()-1]= new CheckingAccount(tempA, tempB);
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
	read();
	cout<<"\n输入了"<<sa.size()<<"个储蓄账户,"<<ca.size()<<"个支票账户";
	cout<<"\n储蓄账户的已获得的利息总和为："<<totalInterest<<'\n';
	
	for(int i=1; i <= sa.size(); i++){
		cout<<"\n\n第"<<i<<"个储蓄账户：";
		cout<<"\n余额："<<sa[sa.size()-1]->getBalance();
		cout<<"\n当前可获得利息："<<sa[sa.size()-1]->calculateInterest();
	}
	cout<<"\n===========================================";
	for(int i=1; i <= ca.size(); i++){
		cout<<"\n\n第"<<i<<"个支票账户：";
		cout<<"\n余额："<<ca[ca.size()-1]->getBalance();
		cout<<"\n手续费："<<ca[ca.size()-1]->getTransactionFee();
	}
	return 0;
}
