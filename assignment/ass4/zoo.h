/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass4\zoo.h
 * Date: 2020-04-28 18:14:06
 * LastEditTime: 2020-04-29 17:17:04
 * !��������: ������bug
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
        bool currentStatus;//0��ʾ�أ�1��ʾ��
        int close_days;//�ر�������
};

/************************************************
 ������
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
 ����
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
        //�����е�������Ŀ
        AnimalFood animal_food_have;
        money earning;//��ȡǮ��
        static float food_price_list[3];//��Ҫ��ʼ��
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
        Adult();//��ʼ�����в���
        money owned_money;//��ʼ���
        AnimalFood temp_food;//��ʱ���ڵ�ʳ��
        int child_number;//���Ķ�ͯ��
        Child *child_have;
};
class Zoo{//����������
    private:
        ZooKeeper keeper;
        FoodSeller seller;
        queue<int>now_cleaning;//�������������
        
        int elephants_number,
            giraffes_number,
            monkeys_number;
        
        Elephant elephants;
        Giraffe giraffes;
        Monkey monkeys;
        
        int exit_reason;//ֹͣ��ԭ��

        //�ο�������
        int total_adult,total_children;

        int open_days;//��������
    public:
        Zoo();//
        int run();//����һ�ξ�ģ�⶯��԰��һ�죬��ɺ���Խ��оͷ���0�������Ծͷ��ط�����
        void display();//չʾ����

};

#endif