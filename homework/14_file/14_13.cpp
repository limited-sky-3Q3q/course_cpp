/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\14_file\14_13.cpp
 * Date: 2020-03-28 19:36:03
 * LastEditTime: 2020-03-28 20:02:22
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<iomanip>
using namespace std;

int main(){
	ofstream outFile("data-size.txt");

    if (!outFile){//判断是否存在文件
        cerr<<"目标文件不存在\n";
        exit(EXIT_FAILURE);
    }
    
    outFile<<left<<setw(23)<<"char"<<right<<setw(4)<<sizeof(char)<<'\n';
    outFile<<left<<setw(23)<<"unsigned char"<<right<<setw(4)<<sizeof(unsigned char)<<'\n';
    outFile<<left<<setw(23)<<"short int"<<right<<setw(4)<<sizeof(short int)<<'\n';
    outFile<<left<<setw(23)<<"unsigned short int"<<right<<setw(4)<<sizeof(unsigned short int)<<'\n';
    outFile<<left<<setw(23)<<"int"<<right<<setw(4)<<sizeof(int)<<'\n';
    outFile<<left<<setw(23)<<"unsigned int"<<right<<setw(4)<<sizeof(unsigned int)<<'\n';
    outFile<<left<<setw(23)<<"long int"<<right<<setw(4)<<sizeof(long int)<<'\n';
    outFile<<left<<setw(23)<<"unsigned long int"<<right<<setw(4)<<sizeof(unsigned long int)<<'\n';
    outFile<<left<<setw(23)<<"long long int"<<right<<setw(4)<<sizeof(long long int)<<'\n';
    outFile<<left<<setw(23)<<"unsigned long long int"<<right<<setw(4)<<sizeof(unsigned long long int)<<'\n';
    outFile<<left<<setw(23)<<"float"<<right<<setw(4)<<sizeof(float)<<'\n';
    outFile<<left<<setw(23)<<"double"<<right<<setw(4)<<sizeof(double)<<'\n';
    outFile<<left<<setw(23)<<"long double"<<right<<setw(4)<<sizeof(long double)<<'\n';
    
	return 0;
}
