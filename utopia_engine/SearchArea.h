/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\SearchArea.h
 * Date: 2020-05-04 11:06:42
 * LastEditTime: 2020-05-11 17:50:56
 * !��������: ������bug
************************************************/
#ifndef SEARCH_AREA_H
#define SEARCH_AREA_H
#include<iostream>
#include<string.h>
using namespace std;
class SearchArea {//̽������
public:
	SearchArea();

	int current_search_area{ 0 };//���ڵ���������

	/************************************************
	 ����Ⱥ�� ç�Ի�ԭ ������� ����Ͽ�� Զ����ַ ����ɽ��
	************************************************/
	enum {
		HaleBeardPeak, TheGreatWild,
		RootStrangledMarshes, GrassRockCanyon,
		RuinedCityOfTheAncients, TheFireMaw
	};//6�������Ĵ���


	struct EnemyInfo {
			string name;//��������
			int attack_and_hit[6];//1Ϊ��������-1Ϊ������
	};
	struct AreaInfo {
		string area_name;//��������
		
		string construct_name;//װ������
		string component_name;//�������
		string treasure_name;//��������
		
		EnemyInfo enemy[5];//level 1-5 
		
	}area[6];//6������

	int InitAreaInfo();//��ʼ��̽���������Ϣ

	int GetIcePlate();//��ñ����ؼ�
	int GetTheMoltenSharo();//���������Ƭ
	int GetIcePlateAndTheMoltenSharo();//��ñ����ؼ׺�������Ƭ
	

	//int DrawSearchAreaInterface();//չʾ̽�������ѡ�����
	//int SelectSearchAreaInterface();//ѡ��̽�������ѡ�����


	//int DrawSearchArea(int);//չʾѡ�е���������
	//int SelectSearchArea(int);//ѡ����������

	//int SelectSearch();//ѡ���������
	//int DrawSearch();//չʾ�����Ľ���
	//int Search();//��ʼ�����ӽ�������

	//�������

	//int PercetSearch();//��������,0
	//int FindConstruct();//����װ�ã�1-10
	//int FindComponent();//���������11-99
	//int encounter();//�������ˣ�100-555 or -1 - -555
	//int DrawBattle();//չʾս������
	//int Battle();//ս��
	//int Dead();//HP����
	//int Victory();//ս��ʤ��

};
#endif