/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\Bag.h
 * Date: 2020-05-04 11:04:34
 * LastEditTime: 2020-05-29 15:04:47
 * !今日运势: 吉，无bug
************************************************/

#ifndef BAG_H
#define BAG_H
class ToolBelt {//三个工具
/************************************************
	初始值全部已充能
************************************************/
public:
	bool dowing_rod{ true };//探索权杖
	bool paralysis_wand{ true };//麻痹权杖
	//bool focus_charm{ true };//聚焦护符
};


class Bag {//背包
public:
	Bag(){};
	ToolBelt tool_belt;//工具带
	//银，石英，橡胶，硅土，蜡，铅
	enum { Silver, Quartz, Gum, Silica, Wax, Lead };//组件名
	int components_number[6]{2,3,0,3,3,3};//组件数量
	
	//冰晶胸甲 雷神手镯 夜光荧丝 无限之秤 远古记事 熔岩碎片 
	enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
		   ScaleOfTheInfinityWurm, TheAncientRecord, TheMoltenSharo};//宝物名
	int treasure[6]{1,1,0,0,1,0};//宝物获得情况
	
	//平衡封印 神秘之镜 虚空之门 黄金罗盘 占卜透镜 水晶电池 
	//SealOfBalance, HermeticMirror, VoidGate, GoldenChassis, ScryingLens, CrystalBattery
	enum { SealOfBalance, HermeticMirror, VoidGate, 
			GoldenChassis, ScryingLens, CrystalBattery };//装置名
	bool construct[6]{1,1,1,1,1,1};//装置获得情况
	bool construct_state[6]{1,1,1,0,1,0};//装置充能状态

	/************************************************
	 水晶电池 黄金罗盘
	 神秘之镜 平衡封印
	 神秘之镜 虚空之门
	 平衡封印 黄金罗盘
	 占卜透镜 平衡封印
	 黄金罗盘 虚空之门
 ************************************************/
	bool link_state[6]{0,1,1,1,1,0};//链接情况

	int activate_hard_level{8};//启动难度

	int gods_hand{ 7 };//上帝之手的点数
	int HP{ 6 };//生命值，初始值6点
	
	int current_state{ 0 };//现在的状态，包括所处区域和是否死亡
	int last_state{0};//上个状态

	int win_or_lose{1};//0为胜利，2为失败，1为未发生
};
#endif