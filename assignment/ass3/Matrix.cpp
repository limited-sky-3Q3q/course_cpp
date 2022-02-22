/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\assignment\ass3\Matrix.cpp
 * Date: 2020-04-18 19:00:35
 * LastEditTime: 2020-04-19 11:49:53
 * !��������: ������bug
************************************************/
#include"Matrix.h"
using namespace std;

//Ӧ��ĿҪ�󣬴���ʱ�ͱ����ʼ��
Matrix::Matrix(){
	cout<<"\n������������ֵ����ֵ֮���Կո�ֿ���";
	for(int i=0; i<4; i++)
		cin>>data[i/2][i%2];
	cout<<"\n��ʼ���ɹ��������ֵΪ��";
	cout<<"\n"<<*this;
}


Matrix::Matrix(double a,double b,double c,double d)
:data{a,b,c,d}{}

Matrix::Matrix(double _double)
:data{_double,_double,_double,_double}{}

/************************************************
 a b
 c d
************************************************/
ostream& operator<<(ostream& out, const Matrix& temp){
	out<<temp.data[0][0]
		<<' '
		<<temp.data[0][1]
		<<'\n'
		<<temp.data[1][0]
		<<' '
		<<temp.data[1][1];
	return out;
}
istream &operator>>(istream &in, Matrix &temp){
	in>>temp.data[0][0]>>temp.data[0][1]
		>>temp.data[1][0]>>temp.data[1][1];
	return in;
}

Matrix Matrix::operator+(Matrix &temp){
	Matrix temp2=*this;
	for(int i=0; i<4; i++)
		temp2.data[i/2][i%2] += temp.data[i/2][i%2];
	return temp2;
}
Matrix Matrix::operator-(Matrix &temp){
	Matrix temp2=*this;
	for(int i=0; i<4; i++)
		temp2.data[i/2][i%2] -= temp.data[i/2][i%2];
	return temp2;
}
Matrix Matrix::operator*(Matrix &right){
	Matrix left=*this,ans(0,0,0,0);
	for(int i=0; i<2; i++)
		for(int j=0; j<2; j++)
			for(int k=0; k<2; k++)
				ans.data[i][j] += left.data[i][k]*right.data[k][j];
	return ans;
}
//�ҳ˵�����
Matrix Matrix::operator*(double &right){
	Matrix left=*this;
	for(int i=0; i<4; i++)
		left.data[i/2][i%2] *= right;
	return left;
}
//��˵�����ֻ��ת������������
double operator*(Matrix &temp){
	return temp.data[0][0];
}

bool Matrix::operator==(Matrix &temp){
	for(int i=0; i<4; i++)
		if(this->data[i/2][i%2] != temp.data[i/2][i%2])
			return false;
	return true;
}
bool Matrix::operator!=(Matrix &temp){
	return !(*this == temp);
}

