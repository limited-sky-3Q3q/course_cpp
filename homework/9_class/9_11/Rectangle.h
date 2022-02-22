//Rectangle.h

#ifndef REC_H
#define REC_H
class Rectangle{
    public:
    explicit Rectangle();
    void setRectangle();
    bool check(float,float)const;

    float getPerimeter()const;
    float gerArea()const;
    float getLength()const;
    float getWidth()const;

    private:
    float length{1},width{1};
};

#endif