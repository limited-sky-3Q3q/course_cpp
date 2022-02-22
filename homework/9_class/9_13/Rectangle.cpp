
//Rectangle.cpp
#include<iostream>
#include<exception>
#include<cmath>
#include<memory.h>
#include"Rectangle.h"
using namespace std;
Rectangle::Rectangle(){
    setRectangle();
}

void Rectangle::setRectangle(){
    float x,y;
    for(int i=0; i<4; i++){
        cout<<"\n请输入第"<<i+1<<"个坐标:";
        cin>>x>>y;
        if(!check(x,y)){
            throw invalid_argument("\n输入的值不在规定的范围");
        }
        coordinate[i][0]=x;
        coordinate[i][1]=y;
    }
    if(!checkRectangle()){
        throw invalid_argument("\n输入的值无法构成长方形");
    }
    cout<<"\n初始化成功，初始值为：";
    for(int i=0; i<4; i++){
        cout<<"("<<coordinate[i][0]<<","<<coordinate[i][1]<<") ";
    }
    float a,b,s=1000000,temp=0;
    
    for(int i=1; i<=3; i++){
        a=pow((coordinate[0][0]-coordinate[i][0]),2);
        b=pow((coordinate[0][1]-coordinate[i][1]),2);
        s=min(s, float(pow(a+b, 0.5)));
        temp=max(temp, float(pow(a+b, 0.5)));
    }

    width=s;
    for(int i=1; i<=3; i++){
        a=pow((coordinate[0][0]-coordinate[i][0]),2);
        b=pow((coordinate[0][1]-coordinate[i][1]),2);
        if(float(pow(a+b, 0.5)) != s && float(pow(a+b, 0.5)) != temp){
            length=float(pow(a+b, 0.5));
            break;
        }
    }

    if(checkSquare()){
        cout<<"\n输入的值可以构成正方形";
    }
    else{
        cout<<"\n输入的值无法构成正方形";
    }

}

void Rectangle::setFillCharacter(const char ch){
    fillCharecter=ch;
    return;
}
void Rectangle::setPerimeterCharacter(const char ch){
    perimeterCharacter=ch;
    return;
}


void Rectangle::draw(){
    //float x1,y1,x2,y2;
    int pos[4];//按顺序存储坐标
    pos[0]=0;
    float dis[4]={0,0,0,0};
    for(int i=1; i<=3; i++){
        float u=pow((coordinate[0][0]-coordinate[i][0]),2);
        float v=pow((coordinate[0][1]-coordinate[i][1]),2);
        dis[i]=pow(u+v, 0.5);
    }
    if(dis[1]<dis[2]&&dis[1]<dis[3]){
        pos[1]=1;
        if(dis[2]<dis[3]){
            pos[2]=3;pos[3]=2;
        }
        else{
            pos[2]=2;pos[3]=3;
        }
    }
    else{
        if(dis[2]<dis[3]){
            pos[1]=2;
            if(dis[1]<dis[3]){
                pos[2]=3;pos[3]=1;
            }
            else{
                pos[2]=1;pos[3]=3;
            }
        }
        else{
            pos[1]=3;
            if(dis[1]<dis[2]){
                pos[2]=2;pos[3]=1;
            }
            else{
                pos[2]=1;pos[3]=2;
            }
        }
    }
    memset(picture,' ',sizeof(picture));
    float MAX=0,MIN=10000000000;
    int y;
    for(int k=0; k<=3; k++){
        MAX=max(coordinate[pos[k]][0],coordinate[pos[(k+1)%4]][0]);
        MIN=min(coordinate[pos[k]][0],coordinate[pos[(k+1)%4]][0]);
        if(double(abs(MAX-MIN))<0.01){
            MAX=max(coordinate[pos[k]][1],coordinate[pos[(k+1)%4]][1]);
            MIN=min(coordinate[pos[k]][1],coordinate[pos[(k+1)%4]][1]);
            for(int j=MIN*4.0; j<=MAX*4.0; j++){
                picture[int(coordinate[pos[k]][0])*4][j]=perimeterCharacter;
            }
            continue;
        }

        for(int i=MIN*4; i<=MAX*4; i++){
            if(abs(coordinate[pos[k]][1]-coordinate[pos[(k+1)%4]][1])<0.01)y=coordinate[pos[k]][1]*4;
            else y=((coordinate[pos[k]][1]-coordinate[pos[(k+1)%4]][1])
                 /(coordinate[pos[k]][0]-coordinate[pos[(k+1)%4]][0]))
                 *(i-4.0*coordinate[pos[k]][0])+4.0*coordinate[pos[k]][1];
            picture[i][y]=perimeterCharacter;
        }
    }
    int l,r;
    for(int i=1; i<=51; i++){
        l=51;r=0;
        for(int j=1; j<=51; j++){
            if(picture[i][j]==perimeterCharacter){
                l=j;
                for(int k=51; k>=l; k--){
                    if(picture[i][k]==perimeterCharacter){
                        r=k;
                        break;
                    }
                }
                break;
            }
        }
        for(int j=l+1; j<r; j++){
            if(picture[i][j]!=perimeterCharacter)
                picture[i][j]=fillCharecter;
        }
    }

    for(int i=50; i>=1; i--){
        for(int j=1; j<=50; j++){
            cout<<' '<<picture[j][i];
        }
        cout<<"\n";
    }
}

bool Rectangle::check(float x,float y)const{
    return (x>0.f&&x<20.f && y>0.f&&y<20.f)?true:false;
}
bool Rectangle::checkRectangle()const{
    float s1,a1,b1,s2,a2,b2;

    for(int i=1; i<=3; i++){
        a1=pow((coordinate[0][0]-coordinate[i][0]),2);
        b1=pow((coordinate[0][1]-coordinate[i][1]),2);
        s1=pow(a1+b1, 0.5);
        a2=pow((coordinate[i%3+1][0]-coordinate[(i+1)%3+1][0]),2);
        b2=pow((coordinate[i%3+1][1]-coordinate[(i+1)%3+1][1]),2);
        s2=pow(a2+b2, 0.5);
        if(abs(s1-s2)>0.01){
            return false;
        }
    }
    return true;
}
bool Rectangle::checkSquare()const{
    if(abs(length-width)<0.01){
        return true;
    }
    else{
        return false;
    }
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