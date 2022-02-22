/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\2020\homework\13_iosream\13_17.cpp
 * Date: 2020-03-28 17:53:57
 * LastEditTime: 2020-03-28 18:19:05
 * !今日运势: 吉，无bug
************************************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
#include<iomanip>
using namespace std;
typedef long long ll;

int main(){
    //cout<<setfill('*');
/************************************************
    从左到右依次是第i位，十进制的i，
    八进制的i，十六进制的i，相应的字符
************************************************/
    cout<<' '<<setw(5)<<left<<"i"
        <<setw(6)<<"dec"
        <<setw(6)<<"oct"
        <<setw(6)<<"hex"
        <<"cha\n";
        cout<<right;
	for(int i=33; i<=126; i++){
        cout<<setw(3)<<dec<<i
            <<setw(6)<<i
            <<setw(6)<<oct<<i
            <<setw(6)<<hex<<i
            <<setw(6)<<char(i)<<'\n';

    }
	return 0;
}
