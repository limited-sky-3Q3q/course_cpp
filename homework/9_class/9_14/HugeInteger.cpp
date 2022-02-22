#include"HugeInteger.h"
#include<iostream>
#include<string.h>
using namespace std;
void HugeInteger::input(char str[]){
    int pos=40;
    for(int i=strlen(str)-1; i>=0; i--){
        num[pos--]=str[i]-'0';
    }
    cout<<"ok";
}
void HugeInteger::output(){
    for(int i=1; i<=40; i++){
        cout<<num[i];
    }
}

void HugeInteger::add(char str[]){
    int temp[41],pos=40;
    for(int i=strlen(str)-1; i>=0; i--){
        temp[pos--]=str[i]-'0';
    }
    int a=0;
    for(int i=40; i>=0; i--){
        num[i]+=temp[i]+a;
        a=num[i]/10;
        num[i]%=10;
    }
}

void HugeInteger::subtract(char str[]){
    int temp[41],pos=40;
    for(int i=strlen(str)-1; i>=0; i--){
        temp[pos--]=str[i]-'0';
    }
    int a=0;
    for(int i=40; i>=0; i--){
        num[i] = num[i]-temp[i]+a;
        if(num[i]>=0)continue;
        else{
            if(i!=0)num[i-1]--;
            num[i]+=10;
        }
    }
}

bool HugeInteger::isEqualTo(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    for(int i=1; i<=40; i++){
        if(a.num[i]!=0)return false;
    }
    return true;
}
bool HugeInteger::isNotEqualTo(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    for(int i=1; i<=40; i++){
        if(a.num[i]!=0)return true;
    }
    return false;
}

bool HugeInteger::isGreaterThan(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    if(a.num[0]==1)return false;
    else return true;
}

bool HugeInteger::isLessThan(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    if(a.num[0]==1)return true;
    else return false;
}

bool HugeInteger::isGreaterThanOrEqualTo(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    if(a.num[0]==1)return false;
    for(int i=1; i<=40; i++){
        if(a.num[i]!=0)return false;
    }
    return true;
}
bool HugeInteger::isLessThanOrEqualTo(HugeInteger a){
    char temp[40];
    for(int i=0; i<40; i++){
        temp[i]=num[i]+'0';
    }
    a.subtract(temp);
    if(a.num[0]==0)return false;
    for(int i=1; i<=40; i++){
        if(a.num[i]!=0)return false;
    }
    return true;
}