/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\homework\assignment\ass3\main.cpp
 * Date: 2020-04-18 22:06:54
 * LastEditTime: 2020-04-19 12:05:35
************************************************/
#include"Matrix.h"
using namespace std;
int main(){
	//3�ֲ�ͬ�ĳ�ʼ����ʽ
	Matrix a, b(1,2,3,4), c(b);

	//ʹ�����ص������������
	cout<<"\na��"<<'\n'<<a
		<<"\nb��"<<'\n'<<b
		<<"\nc��"<<'\n'<<c;
	
	//��������
	cout<<"\n��������a��ֵ��";
	cin>>a;

	cout<<"\na+b=\n";
	cout<<(a+b);

	cout<<"\n\na-b=\n";
	cout<<(a-b);

	cout<<"\n\na*b=\n";
	cout<<(a*b);

	double d=5;
	cout<<"\n\nd="<<d;
	cout<<"\na*d=\n";
	cout<<(a*d);
	
	cout<<"\n\na==b="<<(a==b);
	cout<<"\na!=b="<<(a!=b);

    cout<<"\n";
	system("pause");
	return 0;
}
