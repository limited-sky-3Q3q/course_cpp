/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\assignment\ass3\Matrix.h
 * Date: 2020-04-18 19:05:54
 * LastEditTime: 2020-04-19 11:44:00
 * !��������: ������bug
************************************************/
#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
class Matrix{//2*2����
    private:
        double data[2][2];//00��01��10��11�ֱ���a,b,c,d
    public:
        Matrix();//Ӧ��ĿҪ�󣬴���ʱ�ͱ����ʼ��
        Matrix(double,double,double,double);

        Matrix(double);//ǿ������ת��,a=b=c=d=dobule

        //�������˳��Ϊa,b,c,d
        std::ostream friend &operator<<(std::ostream&, const Matrix&);
        std::istream friend &operator>>(std::istream&, Matrix&);

        //û�г���
        Matrix operator+(Matrix&);
        Matrix operator-(Matrix&);

        Matrix operator*(Matrix&);
        Matrix operator*(double&);//ֻ��double���͵ĳ˷��������أ��������͵�����ͬ��
        double friend operator*(Matrix &temp);
        
        bool operator==(Matrix&);
        bool operator!=(Matrix&);
};

#endif