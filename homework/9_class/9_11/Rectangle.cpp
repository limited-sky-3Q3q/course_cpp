//Rectangle.cpp
#include<iostream>
#include<exception>
#include"Rectangle.h"
using namespace std;
Rectangle::Rectangle(){
    setRectangle();
}

void Rectangle::setRectangle(){
    float l,w;
    cout<<"\n请输入长度：";
    cin>>l;
    cout<<"请输入宽度：";
    cin>>w;
    if(!check(l,w)){
        throw invalid_argument("\n输入的值不合法");
    }
    length=l;
    width=w;
    cout<<"\n初始化成功，初始值为：长度为"<<getLength()
        <<"，宽度为"<<getWidth();
}

bool Rectangle::check(float l,float w)const{
    return (l>0.f&&l<20.f && w>0.f&&w<20.f)?true:false;
}

float Rectangle::getPerimeter()const{
    return length*2.f+width*2.f;
}
float Rectangle::gerArea()const{
    return length*width;
}
float Rectangle::getLength()const{
    return length;
}
float Rectangle::getWidth()const{
    return width;
}