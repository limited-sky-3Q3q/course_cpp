//main.cpp
#include<iostream>
#include"Time.h"
using namespace std;
int main(){
    Time a;
	int b;
	cout<<"请输入要进行多少次+1S的操作:";
	cin>>b;
	for(int i=1; i<=b; i++){
		cout<<"现在进行第"<<i<<"次+1S的操作\n";
		a.tick();
		cout<<"\n";
	}
	return 0;
}