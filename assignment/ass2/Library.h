/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass2\Library.h
 * Date: 2020-04-04 15:42:02
 * LastEditTime: 2020-04-22 15:25:28
 * !��������: ������bug
************************************************/
#include<map>
#include<string>
#include<iostream>
using namespace std;
#ifndef BOOKRECORD_H
#define BOOKRECORD_H
class BookRecord{
    //��������������ʵ��display()�����Ĺ���
    friend ostream& operator<<(ostream&, BookRecord&);
    
    public:
        string book_id;//ID
        string book_title;//����
        string first_name;//��
        string last_name;//��
        int year_published{0};//�������
        int total{0};//�鱾�����������ѽ����
        int number_of_copies{total};//Ŀǰ�ɽ����鱾����
/************************************************
��Ҫ��飺1.book_id�Ƿ��Դ�д��ĸ��ͷ
         2.����Ƿ�Ϊ4λ�����ҿ�ͷΪ1��2
�����ִ��󣬸���һ��������Ϣ��Ȼ����ֹ��������
************************************************/
        BookRecord(){};
        ~BookRecord(){};
        string getID();//�����鱾��ID
        void display();//չʾ��Ϣ
        
};
#endif

#ifndef BORROWER_H
#define BORROWER_H
//������
class Borrower{
    //��������������ʵ��display()�����Ĺ���
    friend ostream& operator<<(ostream&, Borrower&);
    public:
        string borrower_id;//������ID��һ��5λ��
        string first_name;//��
        string last_name;//��
        int number_of_books_on_loan{0};//��ǰ����鱾����
        string book_ids[5];//������ID,���5����
        int number_of_copies{5};//�����˵�ǰ�ɽ��ĵ��鱾����
/************************************************
��Ҫ��飺1.borrower_id�Ƿ�Ϊһ��5λ��
�����ִ��󣬸���һ��������Ϣ��Ȼ����ֹ��������
************************************************/
        Borrower(){};
        ~Borrower(){};
        void display();//չʾ��Ϣ
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
        int total_book{0};//���������������������������δ�����
        int num{0};//���е��������
        std::map<std::string, BookRecord>BookRecords;//���鱾����������鱾
        
        Catalogue(){};
        ~Catalogue(){};
        void display();
};
#endif

#ifndef LIBRARY_H
#define LIBRARY_H
class Library{
    private:
        //�鱾�Ļ�����Ϣ
        Catalogue contents;
        int total_book_on_loan{0};//������鱾����
        //������
        std::map<std::string, Borrower>Borrowers;//��id��������
        int total_brrower{0};//����������
        
/************************************************
7.displays the total number of books on loan, the 
total number of book records and displays the 
individual book records.
************************************************/
    public:
        //չʾ
        void display_books();//ʵ�������鱾����Ϣ 
        void display_brrowers();//չʾ���н�����
        Library();//��ʼ��: 1.����Ŀ¼ 2.����������
        ~Library(){};
};
#endif
