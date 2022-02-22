/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\assignment\ass2\Library.cpp
 * Date: 2020-04-04 17:41:48
 * LastEditTime: 2020-04-19 12:58:28
 * !今日运势: 吉，无bug
************************************************/
#include"Library.h"
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string>
#include<string.h>
using namespace std;
typedef long long ll;

Library::Library(){
	int T1,T2,l,r;
	char ch;
	char temp[1000]; char *p;
	string now; now.clear();

	cin>>T1;getchar();
	for(int i=0; i<T1; i++){//录入书籍信息
		cin.getline(temp, 1000);
		p=strtok(temp, ";");
	
		if(!isupper(p[0])){//非法格式
			cerr<<"\n书籍编号错�??";
			exit(1);
		}
		for(int i=1; i<4; i++){
			if(isdigit(p[i]))continue;
			cerr<<"\n书籍编号错�??";
			exit(1);
		}
		contents.BookRecords[p].book_id=p;
		string temp_id=p;

		//书名部分
		p=strtok(NULL, ";");
		if(isupper(!p[0])){
			cerr<<"\n书名格式错�??";
			exit(1);
		}
		contents.BookRecords[temp_id].book_title=p;
		
		//作者名部分
		p=strtok(NULL, " ");
		contents.BookRecords[temp_id].first_name=p;
		p=strtok(NULL, ";");
		contents.BookRecords[temp_id].last_name=p;
		
		//年份
		p=strtok(NULL, ";");
		int year=0;
		for(int i=0; i<strlen(p); i++){
			year += (p[i]-'0')*(pow(10, 3-i));
		}
		if(!(year>=1000 && year <= 2999)){
			cerr<<"\n年份错�??";
			exit(1);
		}
		contents.BookRecords[temp_id].year_published=year;

		//份数
		year=0;
		p=strtok(NULL, ";");
		for(int i=strlen(p)-1; i>=0; i--){
			year += (p[i]-'0')*(pow(10, i));
		}
		contents.BookRecords[temp_id].number_of_copies=year;
		contents.BookRecords[temp_id].total=year;
		contents.total_book+=year;
		contents.num++;//种类+1
	}

	cin>>T2;getchar();
	total_brrower=T2;
	for(int i=0; i<T2; i++){//录入借书人信�?
		cin.getline(temp, 1000);
		p=strtok(temp, ";");
		string temp_id=p;
		//借书人编�?
		for(int i=0; i<strlen(p); i++){
			if(!isdigit(p[i]) || i>=5){
				cerr<<"\n借书人编号错�?";
				exit(1);
			}
		}
		Borrowers[temp_id].borrower_id=p;

		//借书人�?�名
		p=strtok(NULL, " ");
		Borrowers[temp_id].first_name=p;
		p=strtok(NULL, ";");
		Borrowers[temp_id].last_name=p;
		
		//借的�?
		//int n;
		p=strtok(NULL, ";");
		ch=p[0];
		for(int i=0; i<ch-'0'; i++){
			p=strtok(NULL, ";");
			if(contents.BookRecords[p].number_of_copies){
				contents.BookRecords[p].number_of_copies--;

				total_book_on_loan++;
				Borrowers[temp_id].number_of_copies--;
				Borrowers[temp_id].number_of_books_on_loan++;
				Borrowers[temp_id].book_ids[i]=p;
			}
			else{
				cerr<<"\n要借的书数量不�?";
				exit(1);
			}
		}
	}
	cout<<"\nOK";
}

void Library::display_books(){
	cout<<"\n现在借出的书�?数量为："<<total_book_on_loan;
	contents.display();
}

void Library::display_brrowers(){
	cout<<"\n借书人的信息�?"
		<<"\n======================================================";
	for(auto it=Borrowers.begin(); it != Borrowers.end(); it++){
		cout<<Borrowers[it->first];
	}
}

ostream& operator<<(ostream &out, BookRecord &temp){
	out <<"\n书名�?"<<"�?"<<temp.book_title<<"�?"
		<<"\n序号�?"<<temp.getID()
		<<"\n发�?�年份："<<temp.year_published
		<<"\n作者："<<temp.first_name<<' '<<temp.last_name
		<<"\n馆藏数量，包�?借出的："<<temp.total
		<<"\n当前�?借阅的数量："<<temp.number_of_copies
		<<"\n======================================================";
	return out;
}

ostream& operator<<(ostream &out, Borrower &temp){
	out <<"\n姓名�?"<<temp.first_name<<' '<<temp.last_name
		<<"\nID�?"<<temp.borrower_id
		<<"\n当前借的书籍数量�?"<<temp.number_of_books_on_loan
		<<"\n当前借的书籍ID�?";
		for(int i=0; i<5 && !(temp.book_ids[i].empty()); i++){
			out<<temp.book_ids[i]<<' ';
		}
	out <<"\n当前�?借阅的数量："<<temp.number_of_copies
		<<"\n======================================================";
	return out;
}

void Catalogue::display(){
	cout<<"\n书本总数为："<<total_book;
	cout<<"\n书本种类�?"<<num;
	cout<<"\n书本的�?�细信息�?"
		<<"\n======================================================";
	for(auto it=BookRecords.begin(); it != BookRecords.end(); it++){
		cout<<BookRecords[it->first];
	}
}

void Borrower::display(){
	cout<<*this;
}
void BookRecord::display(){//展示信息
	cout<<*this;
}
string BookRecord::getID(){
	return this->book_id;
}