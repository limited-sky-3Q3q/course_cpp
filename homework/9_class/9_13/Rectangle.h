
//Rectangle.h
#include<algorithm>
#ifndef REC_H
#define REC_H
class Rectangle{
    public:
    explicit Rectangle();
    void setRectangle();
    bool check(float,float)const;
    bool checkRectangle()const;
    bool checkSquare()const;

    void draw();
    void setFillCharacter(const char);
    void setPerimeterCharacter(const char);

    float getPerimeter()const;
    float gerArea()const;
    float getLength()const;
    float getWidth()const;

    private:
    float coordinate[4][2]={0};
    float length{1},width{1};
    char fillCharecter{' '};
    char perimeterCharacter{'*'};
    char picture[101][101]={0};//扩大图像，更细节一些
};

#endif