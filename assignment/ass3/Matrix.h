/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\assignment\ass3\Matrix.h
 * Date: 2020-04-18 19:05:54
 * LastEditTime: 2020-04-19 11:44:00
 * !今日运势: 吉，无bug
************************************************/
#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
class Matrix{//2*2矩阵
    private:
        double data[2][2];//00，01，10，11分别是a,b,c,d
    public:
        Matrix();//应题目要求，创建时就必须初始化
        Matrix(double,double,double,double);

        Matrix(double);//强制类型转换,a=b=c=d=dobule

        //输入输出顺序为a,b,c,d
        std::ostream friend &operator<<(std::ostream&, const Matrix&);
        std::istream friend &operator>>(std::istream&, Matrix&);

        //没有除法
        Matrix operator+(Matrix&);
        Matrix operator-(Matrix&);

        Matrix operator*(Matrix&);
        Matrix operator*(double&);//只对double类型的乘法进行重载，其他类型的做法同理
        double friend operator*(Matrix &temp);
        
        bool operator==(Matrix&);
        bool operator!=(Matrix&);
};

#endif