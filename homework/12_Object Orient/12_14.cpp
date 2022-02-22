/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\12_Object Orient\12_14.cpp
 * Date: 2020-04-11 19:51:00
 * LastEditTime: 2020-04-11 21:33:35
 * !今日运势: 吉，无bug
************************************************/

#include<string>
#include<iostream>
#include<vector>
using namespace std;

/************************************************
    声明部分
************************************************/
class Employee {
    private:
        string firstName;//名
        string lastName;//姓
        string socialSecurityNumber;//社保号
    public:
    
        Employee(const string&, const string&, const string &);
        virtual ~Employee() = default;

        void setFirstName(const string&);
        string getFirstName() const;

        void setLastName(const string&);
        string getLastName() const;

        void setSocialSecurityNumber(const string&);
        string getSocialSecurityNumber() const;
        
        //只进行声明，无实际意义
        double earnings(){};
        Employee(){};
        virtual double getWage(){};
        virtual double getHours(){};
        virtual int getPieces(){};
        /*
        double wage;
        int pieces;
        double hours;
        */
}; 

class PieceWorker:virtual public Employee{
    
    private:
        double wage{0};//每件的工资
        int pieces{0};//完成的件数
    public:
        double getWage();
        int getPieces();
        PieceWorker(const string&, const string&, const string &, const double, const int);
        double earnings();//计算工资
};

class HourlyWorker:virtual public Employee{
    private:
        double wage{0};//时薪
        double hours{0};//工作的时间
    public:
        virtual double getWage();
        virtual double getHours();
        HourlyWorker(const string&, const string&, const string &, const double, const double);
        double earnings();//计算工资，超过40小时后时薪增加
};

/************************************************
 定义部分
************************************************/
/************************************************
 Employee部分
************************************************/
Employee::Employee(const string &fN, const string &lN, const string &sSN){
    setFirstName(fN);
    setLastName(lN);
    setSocialSecurityNumber(sSN);
}
void Employee::setFirstName(const string &fN){
    firstName=fN;
    return;
}
string Employee::getFirstName()const{
    return firstName;
}

void Employee::setLastName(const string &lN){
    lastName=lN;
    return;
}
string Employee::getLastName()const{
    return lastName;
}

void Employee::setSocialSecurityNumber(const string &sSN){
    socialSecurityNumber=sSN;
    return;
}
string Employee::getSocialSecurityNumber()const{
    return socialSecurityNumber;
}

/************************************************
 PieceWorker部分
************************************************/
PieceWorker::PieceWorker(const string &fN, const string &lN, const string &sSN, const double w, const int p){
    setFirstName(fN);
    setLastName(lN);
    setSocialSecurityNumber(sSN);
    wage=w;
    pieces=1;
}
double PieceWorker::earnings(){
    return getWage()*getPieces();
}
double PieceWorker::getWage(){
    return wage;
}
int PieceWorker::getPieces(){
    return pieces;
}
/************************************************
 HourlyWorker部分
************************************************/
HourlyWorker::HourlyWorker(const string &fN, const string &lN, const string &sSN, const double w, const double h){
    setFirstName(fN);
    setLastName(lN);
    setSocialSecurityNumber(sSN);
    wage=w;
    hours=h;
}
double HourlyWorker::earnings(){
    if(hours <= 40.0){
        return getHours()*getWage();
    }
    else{
        return getWage()*40 + getWage()*1.5*(getHours()-40);
    }
}
double HourlyWorker::getWage(){
    return wage;
}
double HourlyWorker::getHours(){
    return hours;
}
/************************************************
 展示部分
 请随意修改数据
************************************************/
int main(){
    Employee *test0 = new Employee("本伟", "卢", "得得得得得得得得得");
    PieceWorker *test1 = new PieceWorker("乙己", "孔", "读书人的社保号怎么能叫社保号呢？", 0.1, 2);
    HourlyWorker *test2 = new HourlyWorker("格瓦拉", "窃", "打工是不可能打工的，这辈子都不可能打工的。", 300, 0);

    cout<<"\n\n第1组数据：";
    cout<<"\n未来科技公司员工姓名："<<test0->getLastName()<<' '<<test0->getFirstName()
        <<"\n社保号："<<test0->getSocialSecurityNumber();

    cout<<"\n\n第2组数据：";
    cout<<"\n未来科技公司员工姓名："<<test1->getLastName()<<' '<<test1->getFirstName()
        <<"\n社保号："<<test1->getSocialSecurityNumber()
        <<"\n每件的工资："<<test1->getWage()
        <<"\n完成的件数："<<test1->getPieces()
        <<"\n获得的工资："<<test1->earnings();

    cout<<"\n\n第3组数据：";
    cout<<"\n未来科技公司员工姓名："<<test2->getLastName()<<' '<<test2->getFirstName()
        <<"\n社保号："<<test2->getSocialSecurityNumber()
        <<"\n时薪："<<test2->getWage()
        <<"\n工时："<<test2->getHours()
        <<"\n获得的工资："<<test2->earnings();
    
    return 0;
}