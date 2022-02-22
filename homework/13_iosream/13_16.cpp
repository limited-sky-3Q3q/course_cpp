
/************************************************
 判断思路：以空格为分隔，分成三部分进行判断
************************************************/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
typedef long long ll;

class Complex{
    private:
        int real{0};//实数部分
        int imaginary{0};//虚数部分
        bool failBit{false};//错误位默认为false
    public:
        friend istream &operator>>(istream&, Complex&);
        friend ostream &operator<<(ostream&, Complex&);
};
/************************************************
 判断思路：以空格为分隔，分成三部分进行判断
************************************************/
istream &operator>>(istream &in, Complex &temp){
    string str;
    int s;//用于判断正负
    in>>str;
    for(int i=0; i<str.length(); i++){
        if(isdigit(str[i])){
            temp.real=temp.real*10+(str[i]-'0');
        }
        else{//数据不合法时
            temp.failBit=true;
            break;
        }
    }
    in>>str;
    if(str=="-"){
        s=-1;
    }
    else if(str=="+"){
        s=1;
    }
    else{//非法输入
        temp.failBit=true;
    }

    in>>str;
    bool flag=true;//判断虚数时默认是非法的
    for(int i=0; i<str.length(); i++){
        if(isdigit(str[i])){
            temp.imaginary=temp.imaginary*10+(str[i]-'0');
        }
        else if(str[i]=='i' && i == str.length()-1){//最后一位是i
            flag=false;
        }
        else{//数据不合法时
            break;
        }
    }
    if(flag){//判断虚数是否合法的
        temp.failBit=true;
    }
    temp.imaginary *= s;
    return in;
}
ostream &operator<<(ostream &out, Complex &temp){
    if(temp.failBit)return out;
    cout<<temp.real<<' ';
    if(temp.imaginary == 0)return out;
    else if(temp.imaginary<0){
        cout<<"- "<<abs(temp.imaginary)<<'i';
    }
    else{//大于零
        cout<<"+ "<<temp.imaginary<<'i';
    }
    return out;
}

int main(){
	Complex test1,test2,test3;
    cout<<"请输入三组测试数据";
    cin>>test1>>test2>>test3;
    cout<<"现在输出test1:"<<test1<<"\n";
    cout<<"现在输出test2:"<<test2<<"\n";
    cout<<"现在输出test3:"<<test3<<"\n";
	return 0;
}
