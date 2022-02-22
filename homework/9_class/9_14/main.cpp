#include"HugeInteger.h"
#include<iostream>
using namespace std;

int main(){
    HugeInteger a;
    char c[40]="100000000000000000001234567891000000456";
    a.input(c);
    char b[40]="000000000000000000000000000000000000123";
    a.add(b);
    a.output();
}