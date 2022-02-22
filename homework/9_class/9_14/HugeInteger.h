#include<iostream>
#ifndef HI_H
#define HI_H

class HugeInteger{
    public:
        void input(char[]);
        void output();
        void add(char[]);
        void subtract(char[]);

        bool isEqualTo(HugeInteger);
        bool isNotEqualTo(HugeInteger);
        bool isGreaterThan(HugeInteger);
        bool isLessThan(HugeInteger);
        bool isGreaterThanOrEqualTo(HugeInteger);
        bool isLessThanOrEqualTo(HugeInteger);

    private:
        int num[41]={0};
};

#endif