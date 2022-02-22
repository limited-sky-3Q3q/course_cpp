/************************************************
 * TODO Auther: by SR
 * FilePath: \vscodefile\2020\assignment\ass4\zoo.cpp
 * Date: 2020-04-28 18:14:13
 * LastEditTime: 2020-04-29 17:30:38
 * !��������: ������bug
************************************************/
#include"zoo.h"
#include<time.h>
AnimalEnclosure::AnimalEnclosure(){
	dirtLevel=0;
    currentStatus=true;
	close_days=0;
}

Animal::Animal(){
	amount_of_food_eaten=0;
}

Adult::Adult(){
	srand(time(NULL));
	owned_money = float(rand()%1001+1000)/100;
	child_number = rand()%3+1;
	child_have = new Child[child_number];
	temp_food={0,0,0};
}
Child::Child()
:animal_food_have{0,0,0}
{}

float FoodSeller::food_price_list[3]={0.2, 0.3, 0.5};

Zoo::Zoo(){
	//������Ա��ʼ��
	keeper.private_of_days_spent_cleaning_enclosures=0;
	seller.animal_food_have={10000, 7000, 4000};
	seller.earning=0;
	while(!now_cleaning.empty())now_cleaning.pop();
	//����������ʼ��
	elephants_number=1;
    giraffes_number=2;
    monkeys_number=3;
	//�ο�������ʼ��
	total_adult=total_children=0;
	//����������ʼ��
	open_days=0;
}
int Zoo::run(){
	/*
	//��ʼ�������θ��
	elephants.amount_of_food_eaten=0;
	giraffes.amount_of_food_eaten=0;
	monkeys.amount_of_food_eaten=0;
	*/

	open_days++;
	//�����ο�
	srand(time(NULL));
	Adult *adult=NULL;
	int adult_number = rand()%21+20;
	//���ɳ���ʱ��ͬʱ������Ӧ�Ķ�ͯ
	adult = new Adult[adult_number];
	
	//�ӵ���������
	total_adult += adult_number;
	for(int i=0; i<adult_number; i++){
		total_children += adult[i].child_number;
	}
	
	//��Ʊ��ʳ��
	for(int i=0; i<adult_number; i++){
		//Ʊ
		adult[i].owned_money -= 1.0 + 0.4*adult[i].child_number;
		//��ʳ��
		
		//����
		seller.animal_food_have.peanuts -= (adult[i].owned_money/3)/seller.food_price_list[0];
		adult[i].temp_food.peanuts = (adult[i].owned_money/3)/seller.food_price_list[0];
		if(seller.animal_food_have.peanuts<=0){
			seller.earning += seller.animal_food_have.peanuts*seller.food_price_list[0];
			exit_reason=3;
			return 3;//�������
		}
		//����ܲ�
		seller.animal_food_have.carrots -= (adult[i].owned_money/3)/seller.food_price_list[1];
		adult[i].temp_food.carrots = (adult[i].owned_money/3)/seller.food_price_list[1];
		if(seller.animal_food_have.carrots<=0){
			seller.earning += seller.animal_food_have.carrots*seller.food_price_list[1];
			exit_reason=4;
			return 4;//���ܲ�����
		}
		//���㽶
		seller.animal_food_have.bananas -= (adult[i].owned_money/3)/seller.food_price_list[2];
		adult[i].temp_food.bananas = (adult[i].owned_money/3)/seller.food_price_list[2];
		if(seller.animal_food_have.bananas<=0){
			seller.earning += seller.animal_food_have.bananas*seller.food_price_list[2];
			exit_reason=5;
			return 5;//�㽶����
		}

		seller.earning +=adult[i].owned_money;
		
		//��ʳ��jianguo
		for(int j=0; j<adult[i].child_number; j++){
			adult[i].child_have[j].animal_food_have=
			{adult[i].temp_food.peanuts/3, adult[i].temp_food.carrots/3, adult[i].temp_food.bananas/3};
		}
		adult[i].temp_food={0,0,0};
		adult[i].owned_money=0;
	}
	
	//��ͯͶι
	for(int i=0; i<adult_number; i++)
		for(int j=0; j<adult[i].child_number; j++){
			/************************************************
			������ͼ����������
			************************************************/
			if(elephants.enclosure.currentStatus){//�п���
				//ι��ͱ���
				if(elephants.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts >= 750*elephants_number){
					elephants.enclosure.dirtLevel += elephants.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts - 750*elephants_number;
					elephants.amount_of_food_eaten=0;
				}
				else{//ι�껹����
					elephants.amount_of_food_eaten += adult[i].child_have[j].animal_food_have.peanuts;
				}
			}

			if(giraffes.enclosure.currentStatus){//�п���
				//ι��ͱ���
				if(giraffes.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts >= 500*giraffes_number){
					giraffes.enclosure.dirtLevel += giraffes.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts - 500*giraffes_number;
					giraffes.amount_of_food_eaten=0;
				}
				else{//ι�껹����
					giraffes.amount_of_food_eaten += adult[i].child_have[j].animal_food_have.peanuts;
				}
			}

			if(monkeys.enclosure.currentStatus){//�п���
				//ι��ͱ���
				if(monkeys.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts >= 300*monkeys_number){
					monkeys.enclosure.dirtLevel += monkeys.amount_of_food_eaten + adult[i].child_have[j].animal_food_have.peanuts - 300*monkeys_number;
					monkeys.amount_of_food_eaten=0;
				}
				else{//ι�껹����
					monkeys.amount_of_food_eaten += adult[i].child_have[j].animal_food_have.peanuts;
				}
			}
		}
	
	//keeper���
	if(!now_cleaning.empty()){//����ϴ����
		switch(now_cleaning.front()){
			case 0:elephants.enclosure.currentStatus=true,
				   elephants.enclosure.dirtLevel=0;
				   break;
			case 1:giraffes.enclosure.currentStatus=true,
				   giraffes.enclosure.dirtLevel=0;
				   break;
			case 2:monkeys.enclosure.currentStatus=true,
				   monkeys.enclosure.dirtLevel=0;
				   break;
			
		}
		now_cleaning.pop();
		keeper.private_of_days_spent_cleaning_enclosures++;
		if(keeper.private_of_days_spent_cleaning_enclosures>=10){
			exit_reason=2;
			return 2;//��ְ��ֹͣ
		}
	}
	
	//������״��
	if(elephants.enclosure.dirtLevel>2000){
		elephants.enclosure.currentStatus=false;
		elephants.enclosure.close_days++;
		now_cleaning.push(0);
	}
	if(giraffes.enclosure.dirtLevel>2000){
		giraffes.enclosure.currentStatus=false;
		giraffes.enclosure.close_days++;
		now_cleaning.push(1);
	}
	if(monkeys.enclosure.dirtLevel>2000){
		monkeys.enclosure.currentStatus=false;
		monkeys.enclosure.close_days++;
		now_cleaning.push(2);
	}
	return 1;//˳�������һ��
}

void Zoo::display(){
	cout<<"\nThe number of days the zoo was opened for is "<<open_days<<" days"
		<<"\nThe reason why the zoo closed is: ";
	switch(exit_reason){
		case 2 : 
			cout<<"The zoo closed because the zoo keeper had enough of cleaning and quit!";
			break;
		case 3 : 
			cout<<"The zoo closed because the seller ran out of peanuts.";
			break;
		case 4 : 
			cout<<"The zoo closed because the seller ran out of carrots.";
			break;
		case 5 : 
			cout<<"The zoo closed because the seller ran out of bananas.";
			break;
	}
	
	cout<<"\nThe total number of adult visitors is "<<total_adult
		<<"\nThe total number of children visitors is "<<total_children
		<<"\nThe total amount of money made by the seller is "<<seller.earning<<"dollars"
		<<"\nthe number of days the zoo keeper spent cleaning is "<<keeper.private_of_days_spent_cleaning_enclosures
		<<"\nThe number of days each animal enclosure was closed for is"
		<<"\n\telephants: "<<elephants.enclosure.close_days
		<<"\n\tgiraffes: "<<giraffes.enclosure.close_days
		<<"\n\tmonkeys: "<<monkeys.enclosure.close_days;
		
	
}

