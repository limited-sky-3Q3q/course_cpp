/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass4\main.cpp
 * Date: 2020-04-28 18:14:20
 * LastEditTime: 2020-04-29 17:41:09
 * !今日运势: 吉，无bug
************************************************/
#include"zoo.h"
using namespace std;

int main(){
	Zoo test;

	while(test.run()==1)
		continue;
	
	test.display();
	cout<<"\n";
	system("pause");
	return 0;
}
