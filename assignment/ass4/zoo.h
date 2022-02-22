/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass4\zoo.h
 * Date: 2020-04-28 18:14:06
 * LastEditTime: 2020-04-29 17:17:04
 * !今日运势: 吉，无bug
************************************************/
#ifndef ZOO_H
#define ZOO_H
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
typedef float money;
class AnimalFood{
    public:
    float peanuts, carrots, bananas;
};
class AnimalEnclosure{
    public:
        AnimalEnclosure();
        float dirtLevel;
        bool currentStatus;//0表示关，1表示开
        int close_days;//关闭总天数
};

/************************************************
 动物类
************************************************/
class Animal{
    public:
        Animal();
        float weight, amount_of_food_eaten;
        AnimalEnclosure enclosure;
};
class Elephant:public Animal{
    public:
        float trunk_length;
};
class Giraffe:public Animal{
    public:
        float neck_length;
};
class Monkey:public Animal{
    public:
        float arm_length;
};

/************************************************
 人类
************************************************/
class Person{
    public:
        string name;
        int age;
};
class ZooKeeper: public Person{
    public:
        int private_of_days_spent_cleaning_enclosures;
};
class FoodSeller: public Person{
    public:
        //现在有的饲料数目
        AnimalFood animal_food_have;
        money earning;//收取钱数
        static float food_price_list[3];//需要初始化
};
class Vistor: public Person{
    public:
        string vistor_pass_ID;
};
class Child: public Vistor{
    public:
        Child();
        AnimalFood animal_food_have;
};
class Adult: public Vistor{
    public:
        Adult();//初始化下列参数
        money owned_money;//初始金额
        AnimalFood temp_food;//暂时存在的食物
        int child_number;//带的儿童数
        Child *child_have;
};
class Zoo{//包含所有类
    private:
        ZooKeeper keeper;
        FoodSeller seller;
        queue<int>now_cleaning;//正在清理的区域
        
        int elephants_number,
            giraffes_number,
            monkeys_number;
        
        Elephant elephants;
        Giraffe giraffes;
        Monkey monkeys;
        
        int exit_reason;//停止的原因

        //游客总数量
        int total_adult,total_children;

        int open_days;//开放天数
    public:
        Zoo();//
        int run();//调用一次就模拟动物园的一天，完成后可以进行就返回0，不可以就返回非零数
        void display();//展示数据

};

#endif