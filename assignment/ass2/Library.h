/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass2\Library.h
 * Date: 2020-04-04 15:42:02
 * LastEditTime: 2020-04-22 15:25:28
 * !今日运势: 吉，无bug
************************************************/
#include<map>
#include<string>
#include<iostream>
using namespace std;
#ifndef BOOKRECORD_H
#define BOOKRECORD_H
class BookRecord{
    //重载输出运算符以实现display()函数的功能
    friend ostream& operator<<(ostream&, BookRecord&);
    
    public:
        string book_id;//ID
        string book_title;//书名
        string first_name;//名
        string last_name;//姓
        int year_published{0};//发行年份
        int total{0};//书本总数，包括已借出的
        int number_of_copies{total};//目前可借阅书本总数
/************************************************
需要检查：1.book_id是否以大写字母开头
         2.年份是否为4位数，且开头为1或2
若发现错误，给出一个错误信息，然后终止程序运行
************************************************/
        BookRecord(){};
        ~BookRecord(){};
        string getID();//返回书本的ID
        void display();//展示信息
        
};
#endif

#ifndef BORROWER_H
#define BORROWER_H
//借书人
class Borrower{
    //重载输出运算符以实现display()函数的功能
    friend ostream& operator<<(ostream&, Borrower&);
    public:
        string borrower_id;//借书人ID，一个5位数
        string first_name;//名
        string last_name;//姓
        int number_of_books_on_loan{0};//当前借的书本数量
        string book_ids[5];//借的书的ID,最多5本书
        int number_of_copies{5};//借书人当前可借阅的书本数量
/************************************************
需要检查：1.borrower_id是否为一个5位数
若发现错误，给出一个错误信息，然后终止程序运行
************************************************/
        Borrower(){};
        ~Borrower(){};
        void display();//展示信息
};
//int Borrower::total{0};
#endif

#ifndef CATALOGUE_H
#define CATALOGUE_H
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string>
#include<fstream>
#include<map>
class Catalogue{
    public:
        int total_book{0};//所有种类的书的总数，包括借出与未借出的
        int num{0};//含有的书的种类
        std::map<std::string, BookRecord>BookRecords;//用书本编号索引到书本
        
        Catalogue(){};
        ~Catalogue(){};
        void display();
};
#endif

#ifndef LIBRARY_H
#define LIBRARY_H
class Library{
    private:
        //书本的基本信息
        Catalogue contents;
        int total_book_on_loan{0};//借出的书本总数
        //借书人
        std::map<std::string, Borrower>Borrowers;//用id进行索引
        int total_brrower{0};//借书人总数
        
/************************************************
7.displays the total number of books on loan, the 
total number of book records and displays the 
individual book records.
************************************************/
    public:
        //展示
        void display_books();//实现所有书本的信息 
        void display_brrowers();//展示所有借书人
        Library();//初始化: 1.书类目录 2.借书人数量
        ~Library(){};
};
#endif
