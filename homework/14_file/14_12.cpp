/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\14_file\14_12.cpp
 * Date: 2020-03-28 20:01:41
 * LastEditTime: 2020-03-28 21:08:28
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string.h>
using namespace std;

int len=0;
char ans[17001][9]={0};//4^7=16384
//string temp[8]={0};
char temp[8];
char number[8];

char Letter[10][4]={
    0, 0, 0, 0,
    0, 0, 0, 0,
    65,66,67,0,//2
    68,69,70,0,
    71,72,73,0,
    74,75,76,0,
    77,78,79,0,
    80,81,82,83,//7
    84,85,86,0,
    87,88,89,90//9
};

void out(int now){//递归枚举
    if(now == 7)return;
    
    int end=3;
    if(number[now]-'0' == 7 || number[now]-'0' == 9)
        end=4;
    
    for(int i=0; i<end; i++){
        temp[now]=Letter[number[now]-'0'][i];
        if(now==6){
            for(int j=0; j<7; j++){
                ans[len][j]=temp[j];
            }
            ans[len++][7]='\0';
        }
        out(now+1);
    }
    return;
}

int main(){
	ofstream outFile("telephone_name.txt");

    if (!outFile){//判断是否存在文件
        cerr<<"目标文件不存在\n";
        exit(EXIT_FAILURE);
    }  

    cout<<"请输入一个7位数的电话号码";
    cin>>number;
    out(0);//用递归枚举所有可能情况

    for(int i=0; i<len; i++){
        outFile<<ans[i]<<'\n';
    }
	return 0;
}
