
#include"Rectangle.h"
#include<iostream>
using namespace std;
int main(){
    cout<<"???";
    Rectangle a;

    cout<<"\n调用getPerimeter()，输出："<<a.getPerimeter();
    cout<<"\n调用gerArea()，输出："<<a.gerArea();
    cout<<"\n调用getLength()，输出："<<a.getLength();
    cout<<"\n调用getWidth()，输出："<<a.getWidth();
    cout<<"\n调用setFillCharacter()，�?�置�?充字�?";a.setFillCharacter('0');
    cout<<"\n调用setPerimeterCharacter()，�?�置边缘字�??";a.setPerimeterCharacter('*');
    cout<<"\n调用draw()，输出：\n";a.draw();
    system("pause");
}