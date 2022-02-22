/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\SearchArea.h
 * Date: 2020-05-04 11:06:42
 * LastEditTime: 2020-05-11 17:50:56
 * !今日运势: 吉，无bug
************************************************/
#ifndef SEARCH_AREA_H
#define SEARCH_AREA_H
#include<iostream>
#include<string.h>
using namespace std;
class SearchArea {//探索界面
public:
	SearchArea();

	int current_search_area{ 0 };//现在的搜索区域

	/************************************************
	 苍髯群峰 莽苍荒原 扼根沼泽 玻璃峡谷 远古遗址 火焰山洞
	************************************************/
	enum {
		HaleBeardPeak, TheGreatWild,
		RootStrangledMarshes, GrassRockCanyon,
		RuinedCityOfTheAncients, TheFireMaw
	};//6个地区的代号


	struct EnemyInfo {
			string name;//敌人名字
			int attack_and_hit[6];//1为攻击区，-1为受伤区
	};
	struct AreaInfo {
		string area_name;//地区名字
		
		string construct_name;//装置名字
		string component_name;//组件名字
		string treasure_name;//宝物名字
		
		EnemyInfo enemy[5];//level 1-5 
		
	}area[6];//6个地区

	int InitAreaInfo();//初始化探索区域的信息

	int GetIcePlate();//获得冰晶胸甲
	int GetTheMoltenSharo();//获得熔岩碎片
	int GetIcePlateAndTheMoltenSharo();//获得冰晶胸甲和熔岩碎片
	

	//int DrawSearchAreaInterface();//展示探索区域的选择界面
	//int SelectSearchAreaInterface();//选择探索区域的选择界面


	//int DrawSearchArea(int);//展示选中的搜索区域
	//int SelectSearchArea(int);//选择搜索区域

	//int SelectSearch();//选择进行搜索
	//int DrawSearch();//展示搜索的界面
	//int Search();//开始掷骰子进行搜索

	//搜索结果

	//int PercetSearch();//完美搜索,0
	//int FindConstruct();//发现装置，1-10
	//int FindComponent();//发现组件，11-99
	//int encounter();//遭遇敌人，100-555 or -1 - -555
	//int DrawBattle();//展示战斗界面
	//int Battle();//战斗
	//int Dead();//HP归零
	//int Victory();//战斗胜利

};
#endif