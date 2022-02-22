/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\11_inheritance\11_10.cpp
 * Date: 2020-03-31 14:25:37
 * LastEditTime: 2020-03-31 15:48:28
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
};
class SavingsAccount : virtual public Account{
	private:
		double interestRate{0};//百分比，interestRate%
	public:
		SavingsAccount(double, double);
		double calculateInterest();//返回利息
};
class CheckingAccount : virtual public Account{
	private:
		double transactionFee{0};//手续费
	public:
		CheckingAccount(double, double);
		void credit(double);//存钱
		void debit(double);//取钱,要检查
};

/************************************************
 *定义部分
************************************************/

double Account::getBalance(){
	return balance;
}
void Account::debit(double temp){
	if(balance < temp){//钱不够
		cout<<"\n要取的金额不足。";
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
		cout<<"\n要取的金额不足。";
	}
	else{
		balance -= temp+transactionFee;
		cout<<"\n操作成功，本次操作取出"<<temp<<"。";
	}
}
/************************************************
 * 测试部分
************************************************/

int main(){
	Account test1(100);
	SavingsAccount test2(200, 10);
	CheckingAccount test3(250, 30);

	cout<<"\n执行test1.credit(50)";test1.credit(50);
	cout<<"\n\n执行test1.debit(100)";test1.debit(100);
	cout<<"\n\ntest1.getBalance() = "<<test1.getBalance();
	
	cout<<"\n\n\n执行test2.credit(50)";test2.credit(50);
	cout<<"\n\n执行test2.debit(100)";test2.debit(100);
	//cout<<"\n\n执行test2.calculateInterest()";
	cout<<"\n\ntest2.calculateInterest() = "<<test2.calculateInterest();
	cout<<"\ntest2.getBalance() = "<<test2.getBalance();

	cout<<"\n执行test3.credit(50)";test3.credit(50);
	cout<<"\n\n执行test3.debit(100)";test3.debit(100);
	cout<<"\n\ntest3.getBalance() = "<<test3.getBalance();
	return 0;
}
