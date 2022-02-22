/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\controller.cpp
 * Date: 2020-05-03 14:59:47
 * LastEditTime: 2020-05-30 11:55:18
 * !今日运势: 吉，无bug
************************************************/
#include"controller.h"
#include<windows.h>
#include<iostream>
#include<time.h>
using namespace std;

/************************************************
//TODO 宝物的功能，时间系统，
//TODO 每次探索或链接消耗一天
************************************************/
int Controller::BeginGame(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	//隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    //cout<<cursorInfo.bVisible<<"\n";
    cout<<SetConsoleCursorInfo(hOut, &cursorInfo);
    cout<<"按回车";
	getchar();
	
	
	SetConsoleTextAttribute(hOut, 0x0007);

	//设置窗口大小
	cout<<SetConsoleScreenBufferSize(hOut, windows_size);
	SMALL_RECT rect = { 0, 0, 45 - 1, 20 - 1 };
	cout<<SetConsoleWindowInfo(hOut, true, &windows_rect);
	
	
	//调试
	cout<<"按回车";
	getchar();
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	//int LastAttribute{ 0 };//上次的文本属性
	
	

	while (1) {//一级循环

		//Init();//游戏内容初始化
		//Action();//开始界面的动画

		Clear();
		
		bag.current_state = SELECT_AREA;
		DrawSelectArea();
		

		while (1) {//二级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			
			//选择界面：工坊，冒险，背包，时间
			if (record.EventType == MOUSE_EVENT) {
				//调试函数
				/*
				SetConsoleCursorPosition(hOut, {0,0});
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				cout<<MousePos.X<<" "<<MousePos.Y<<" ";
				*/
				
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				//!用栈的结构来切换场景

				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//!注意Bottom和Top的大小关系
					(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					if(	(MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
						&&
						(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
							//落在在背包按钮上
							Rect = bag_position;
							LastArea = bag_position;
						}
					else if((MousePos.X >= select_search_area.Left && MousePos.X <= select_search_area.Right)
							&&
							(MousePos.Y <= select_search_area.Bottom && MousePos.Y >= select_search_area.Top)){
							//落在在探索按钮上
							Rect = select_search_area;
							LastArea = select_search_area;
						}
					else if((MousePos.X >= select_workshop_area.Left && MousePos.X <= select_workshop_area.Right)
							&&
							(MousePos.Y <= select_workshop_area.Bottom && MousePos.Y >= select_workshop_area.Top)){
							//落在在工坊按钮上
							Rect = select_workshop_area;
							LastArea = select_workshop_area;
						}
					else if(v>=6
							&&
							(MousePos.X >= final_activate_area.Left && MousePos.X <= final_activate_area.Right)
							&&
							(MousePos.Y <= final_activate_area.Bottom && MousePos.Y >= final_activate_area.Top)){
							Rect = final_activate_area;
							LastArea = final_activate_area;
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
						
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);

				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//进行选择,改变区域
					if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
						//进入背包界面
						bag.last_state = SELECT_AREA;
						bag.current_state = OPEN_BAG;
						IntoBag();

						v=0;
						for(int i=0; i<6; i++)
							v += bag.link_state[i];
							
						Clear();
						DrawSelectArea();
						bag.last_state = OPEN_BAG;
						bag.current_state = SELECT_AREA;
					}
					else if(LastArea.Left == select_search_area.Left && LastArea.Right == select_search_area.Right){
						//进入探索界面
						bag.last_state = SELECT_AREA;
						bag.current_state = SEARCH_AREA_INTERFACE;
						IntoSearchArea();

						v=0;
						for(int i=0; i<6; i++)
						v += bag.link_state[i];

						bag.last_state = SEARCH_AREA_INTERFACE;
						bag.current_state = SELECT_AREA;
						
						Clear();
						DrawSelectArea();
						
					}
					else if(LastArea.Left == select_workshop_area.Left && LastArea.Right == select_workshop_area.Right){
						//进入工坊界面
						bag.last_state = SELECT_AREA;
						bag.current_state = ARTIFACT_WORKSHOP;
						IntoWorkshop();

						v=0;
						for(int i=0; i<6; i++)
							v += bag.link_state[i];
						
						bag.last_state = ARTIFACT_WORKSHOP;
						bag.current_state = SELECT_AREA;
						
						Clear();
						DrawSelectArea();
					}
					else if(v>=6 
							&& 
							LastArea.Left == final_activate_area.Left && LastArea.Right == final_activate_area.Right){
						//!进入最终启动界面！
						Clear();
						bag.last_state = SELECT_AREA;
						bag.current_state = FINAL_ACTIVATE_AREA;
						IntoWarn();//最终启动得有牌面
						bag.last_state = FINAL_ACTIVATE_AREA;
						bag.current_state = SELECT_AREA;
						
						
						//Clear();
						
						//本局游戏结束
						//展示最终界面，和分数
						if(bag.win_or_lose == 1){
							Clear();
							DrawSelectArea();
							Sleep(500);
							continue;
						}
							
						if(EndGame() == 2){//退出游戏
							return 0;
						}
						else{//再来一局
							Init();
							continue;
						}

					}
					
					if(bag.win_or_lose == 2){
						if(EndGame() == 2){//退出游戏
							return 0;
						}
						else{//再来一局
							Init();
							continue;
						}
					}
					Sleep(500);
				}
			}
		}
	
	}
}

int Controller::Clear(){
	//Sleep(100);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	LPDWORD temp = new DWORD;
	//SetConsoleCursorPosition(hOut, {0,0})
	SetConsoleTextAttribute(hOut, 0x0007);
	FillConsoleOutputAttribute(hOut, 0x0007, windows_size.X*windows_size.Y, {0,0}, temp);
	FillConsoleOutputCharacter(hOut, ' ', windows_size.X*windows_size.Y, {0,0}, temp);
	
	return 0;
}

int Controller::DrawInformationBar() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, { 0, 0 });
	cout << "■■■■■■■■■■■■■■■■■■■■■■■";
	for (SHORT i = 1; i <= 4; i++) {
		SetConsoleCursorPosition(hOut, { 0, i });
		cout << "■";
		SetConsoleCursorPosition(hOut, { 44, i });
		cout << "■";
	}
	SetConsoleCursorPosition(hOut, { 0, 5 });
	cout << "■■■■■■■■■■■■■■■■■■■■■■■";
	SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
	cout << "背包  HP：" << bag.HP;
	SetConsoleCursorPosition(hOut, { 23, 1 });
	cout << "时间  上帝之手：" << bag.gods_hand;

	//前两行必定出现
	//TODO颜色还未加上
	int len=0;
	
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RGB(128,0,0)
	for(int i=1; i < time_system.day_now; i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ●";
	}

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//RGB(0,255,0)
	SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
	len++;
	cout<<" ●";

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);//RGB(0,128,0)
	for(int i=1; i<=(14 - time_system.day_now); i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ●";
	}

	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);//RGB(128,128,0)
	for(int i=1; i <= min(21-time_system.day_now - 7 + time_system.extra_time ,time_system.extra_time); i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ●";
	}
	/*
	SetConsoleCursorPosition(hOut, { 23, 2 });
	cout << "● ● ● ● ● ● ●";
	SetConsoleCursorPosition(hOut, { 23, 3 });
	cout << "● ● ● ● ● ● ●";

	SetConsoleCursorPosition(hOut, { 22, 4 });
	for (int i = 0; i < time_system.extra_time; i++)
		cout << " ●";
	*/

	SetConsoleTextAttribute(hOut, 0x0007);
	string now_area = "";
	switch (bag.current_state) {
	case INTRODUCE_BACKGROUND:
		now_area.clear(); break;
	case ACTION:
		now_area.clear(); break;
	case SELECT_AREA:
		now_area = "选择方向"; break;
	case OPEN_BAG:
		now_area = "打开背包"; break;
	case ARTIFACT_WORKSHOP:
		now_area = "神器工坊"; break;
	case ACTIVATE_AREA:
		now_area = "启动区域"; break;
	case ACTIVATE:
		now_area = "进行启动"; break;
	case LINK_AREA:
		now_area = "链接区域"; break;
	case LINK:
		now_area = "进行链接"; break;
	case FINAL_ACTIVATE_AREA:
		now_area = "所有装置已链接！"; break;
	case FINAL_ACTIVATE:
		now_area = "最终链接！"; break;
	case SEARCH_AREA_INTERFACE:
		now_area = "探索区域"; break;
	case SEARCH_AREA:
		switch (search_area.current_search_area) {
		case SearchArea::HaleBeardPeak:
			now_area = "苍髯群峰"; break;
		case SearchArea::TheGreatWild:
			now_area = "莽苍荒原"; break;
		case SearchArea::RootStrangledMarshes:
			now_area = "扼根沼泽"; break;
		case SearchArea::GrassRockCanyon:
			now_area = "玻璃峡谷"; break;
		case SearchArea::RuinedCityOfTheAncients:
			now_area = "远古遗址"; break;
		case SearchArea::TheFireMaw:
			now_area = "火焰洞穴"; break;
		default:
			now_area.clear(); break;
		}
		break;
	case SEARCH:
		now_area = "进行搜索"; break;
	case BATTLE:
		now_area = "进行战斗"; break;
	default:break;
	}
	SetConsoleCursorPosition(hOut, COORD{ current_state_position.Left, current_state_position.Top });
	cout<<now_area;
	return 0;
}

int Controller::DrawSelectArea() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DrawInformationBar();

	SetConsoleCursorPosition(hOut, COORD{ select_search_area.Left, select_search_area.Top });
	cout << "探索";
	SetConsoleCursorPosition(hOut, COORD{ select_workshop_area.Left, select_workshop_area.Top });
	cout << "工坊";

	int v=0;
	for(int i=0; i<6; i++)
		v += bag.link_state[i];
	if(v==6){
		SetConsoleCursorPosition(hOut, COORD{final_activate_area.Left, final_activate_area.Top});
		cout <<"最终启动!";
	}
	return 0;
}

int Controller::IntoBag(){
	Clear();
	DrawInformationBar();
	DrawBag();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义
	
	SMALL_RECT TheAncientRecordArea{30, 13, 37, 13};//远古记事的区域
	SMALL_RECT gods_hand_area{32, 15, 43, 15};//使用上帝之手区域

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= TheAncientRecordArea.Left && MousePos.X <= TheAncientRecordArea.Right)
						&&
						(MousePos.Y <= TheAncientRecordArea.Bottom && MousePos.Y >= TheAncientRecordArea.Top)
						&&
						bag.treasure[Bag::TheAncientRecord]==1){
						//远古记事
						Rect = TheAncientRecordArea;
						LastArea = TheAncientRecordArea;
					}
				else if((MousePos.X >= gods_hand_area.Left && MousePos.X <= gods_hand_area.Right)
						&&
						(MousePos.Y <= gods_hand_area.Bottom && MousePos.Y >= gods_hand_area.Top)
						&&
						bag.gods_hand >= 3){
						//上帝之手
						Rect = gods_hand_area;
						LastArea = gods_hand_area;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right
					&&
					LastArea.Bottom == bag_back_position.Bottom){
					Clear();
					
					//特殊赋值
					bag.current_state = bag.last_state;
					bag.last_state = OPEN_BAG;
					return 0;
				}
				else if(LastArea.Left == TheAncientRecordArea.Left 
						&& 
						LastArea.Right == TheAncientRecordArea.Right
						&&
						LastArea.Bottom == TheAncientRecordArea.Bottom
						&&
						bag.treasure[Bag::TheAncientRecord]==1){
					bag.current_state = LINK_AREA;
					bag.last_state = OPEN_BAG;
					IntoAncientRecord();//进入使用远古记事的区域
					bag.current_state = OPEN_BAG;
					bag.last_state = LINK_AREA;
					Clear();
					DrawInformationBar();
					DrawBag();
				}
				else if(LastArea.Left == gods_hand_area.Left 
						&& 
						LastArea.Right == gods_hand_area.Right
						&&
						LastArea.Bottom == gods_hand_area.Bottom
						&&//使用上帝之手
						bag.gods_hand >= 3){
					bag.gods_hand -= 3;
					time_system.extra_time = min(time_system.extra_time + 1, 7);
					DrawInformationBar();
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:异常返回
}

int Controller::DrawBag(){
	
	/************************************************
  enum { Silver银, Quartz石英, Gum橡胶, Silica硅土, Wax蜡, Lead铅 };//组件名
	int components_number[6]{0,0,0,0,0,0};//组件数量
 ************************************************/
	//6个组件数量
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { 2, 7 });//统一起点
	cout<<" 组件数量";
	SetConsoleCursorPosition(hOut, { 2, 8 });
	cout<<"石英:"<<bag.components_number[Bag::Quartz]<<" 银:"<<bag.components_number[Bag::Silver];
	SetConsoleCursorPosition(hOut, { 2, 9 });
	cout<<"橡胶:"<<bag.components_number[Bag::Gum]<<" 蜡:"<<bag.components_number[Bag::Wax];
	SetConsoleCursorPosition(hOut, { 2, 10 });
	cout<<"硅土:"<<bag.components_number[Bag::Silica]<<" 铅:"<<bag.components_number[Bag::Lead];
	
	//三个道具
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 7 });
	cout<<"     装备";
	SetConsoleCursorPosition(hOut, { 14, 8 });
	cout<<"探索权杖:";
	if(bag.tool_belt.dowing_rod){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已充能";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未充能";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 9 });
	cout<<"麻痹魔杖:";
	if(bag.tool_belt.paralysis_wand){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已充能";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未充能";
	}
	
	/*
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 10 });
	cout<<"聚焦护符:";
	if(bag.tool_belt.focus_charm){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已充能";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未充能";
	}
	*/

	//冰晶胸甲 雷神手镯 夜光草 无限之秤 熔岩碎片 远古计事
	//enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
	//	   ScaleOfTheInfinityWurm, TheMoltenSharo, TheAncientRecord};//宝物名
	//6个宝物

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 7 });//统一起点
	cout<<"   宝物";
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 8 });
	cout<<"冰晶胸甲:";
	if(bag.treasure[Bag::IcePlate]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 9 });
	cout<<"雷神手镯:";
	if(bag.treasure[Bag::BraceletOfLos]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 10 });
	cout<<"夜光荧丝:";
	if(bag.treasure[Bag::ShimmeringMoonlace]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 11 });
	cout<<"无限之秤:";
	if(bag.treasure[Bag::ScaleOfTheInfinityWurm]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 12 });
	cout<<"熔岩碎片:";
		if(bag.treasure[Bag::TheMoltenSharo]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 13 });
	cout<<"远古记事:";
		if(bag.treasure[Bag::TheAncientRecord]){//已获得
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"已获得";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 32, 15 });
	cout<<"使用上帝之手";

	//链接情况
	//水晶电池 黄金罗盘 占卜透镜 神秘之镜 平衡封印 虚空之门
	//enum { CrystalBattery, GoldenChassis, ScryingLens,
	//	   HermeticMirror, SealOfBalance, VoidGate};//装置名
	//bool construct[6]{0,0,0,0,0,0};//装置获得情况
	//?○
	/************************************************
	 水晶电池 黄金罗盘
	 神秘之镜 平衡封印
	 神秘之镜 虚空之门
	 平衡封印 黄金罗盘
	 占卜透镜 平衡封印
	 黄金罗盘 虚空之门
 ************************************************/
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 12 });//统一起点
	cout<<"      链接装置";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 13 });
	cout<<"铅:   ";
	if(bag.construct[Bag::CrystalBattery]){//已获得
		if(bag.construct_state[Bag::CrystalBattery]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"水晶电池";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 14 });
	cout<<"硅土: ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 15 });
	cout<<"蜡:   ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 16 });
	cout<<"石英: ";
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 17 });
	cout<<"银:   ";
	if(bag.construct[Bag::ScryingLens]){//已获得
		if(bag.construct_state[Bag::ScryingLens]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"占卜透镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 18 });
	cout<<"橡胶: ";
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";
	
	//返回按钮
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";

	return 0;
}

int Controller::IntoAncientRecord(){//进入使用远古记事的区域
	Clear();
	DrawInformationBar();
	DrawAncientRecord();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT button_pos[6];
	button_pos[0] = {23, 8, 24, 8};
	button_pos[1] = {23, 10, 24, 10};
	button_pos[2] = {23, 12, 24, 12};
	button_pos[3] = {23, 14, 24, 14};
	button_pos[4] = {23, 16, 24, 16};
	button_pos[5] = {23, 18, 24, 18};
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT){
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				//链接按钮
				else if((MousePos.X >= button_pos[0].Left && MousePos.X <= button_pos[0].Right)
						&&
						(MousePos.Y <= button_pos[0].Bottom && MousePos.Y >= button_pos[0].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//未链接
						!bag.link_state[0]
						&&//有铅
						(bag.components_number[Bag::Lead]>0)){
						Rect = button_pos[0];
						LastArea = button_pos[0];
					}
				else if((MousePos.X >= button_pos[1].Left && MousePos.X <= button_pos[1].Right)
						&&
						(MousePos.Y <= button_pos[1].Bottom && MousePos.Y >= button_pos[1].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//未链接
						!bag.link_state[1]
						&&//有硅土
						(bag.components_number[Bag::Silica]>0)){
						Rect = button_pos[1];
						LastArea = button_pos[1];
					}
				else if((MousePos.X >= button_pos[2].Left && MousePos.X <= button_pos[2].Right)
						&&
						(MousePos.Y <= button_pos[2].Bottom && MousePos.Y >= button_pos[2].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//未链接
						!bag.link_state[2]
						&&//有蜡
						(bag.components_number[Bag::Wax]>0)){
						Rect = button_pos[2];
						LastArea = button_pos[2];
					}
				else if((MousePos.X >= button_pos[3].Left && MousePos.X <= button_pos[3].Right)
						&&
						(MousePos.Y <= button_pos[3].Bottom && MousePos.Y >= button_pos[3].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//未链接
						!bag.link_state[3]
						&&//有石英
						(bag.components_number[Bag::Quartz]>0)){
						Rect = button_pos[3];
						LastArea = button_pos[3];
					}
				else if((MousePos.X >= button_pos[4].Left && MousePos.X <= button_pos[4].Right)
						&&
						(MousePos.Y <= button_pos[4].Bottom && MousePos.Y >= button_pos[4].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//未链接
						!bag.link_state[4]
						&&//有银
						(bag.components_number[Bag::Silver]>0)){
						Rect = button_pos[4];
						LastArea = button_pos[4];
					}
				else if((MousePos.X >= button_pos[5].Left && MousePos.X <= button_pos[5].Right)
						&&
						(MousePos.Y <= button_pos[5].Bottom && MousePos.Y >= button_pos[5].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//未链接
						!bag.link_state[5]
						&&//有橡胶
						(bag.components_number[Bag::Gum]>0)){
						Rect = button_pos[5];
						LastArea = button_pos[5];
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					
					bag.last_state = LINK_AREA;
					return 0;
				}
				//链接按钮
				else if(LastArea.Left == button_pos[0].Left
						&&
						LastArea.Right == button_pos[0].Right
						&&
						LastArea.Bottom == button_pos[0].Bottom
						&&
						LastArea.Top == button_pos[0].Top
						&&//有装置且已充能
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&
						!bag.link_state[0]
						&&
						bag.components_number[Bag::Lead]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[0] = true;
					return 0;
				}
				else if(LastArea.Left == button_pos[1].Left
						&&
						LastArea.Right == button_pos[1].Right
						&&
						LastArea.Bottom == button_pos[1].Bottom
						&&
						LastArea.Top == button_pos[1].Top
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&
						!bag.link_state[1]
						&&
						bag.components_number[Bag::Silica]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[1] = true;
					return 0;
				}
				else if(LastArea.Left == button_pos[2].Left
						&&
						LastArea.Right == button_pos[2].Right
						&&
						LastArea.Bottom == button_pos[2].Bottom
						&&
						LastArea.Top == button_pos[2].Top
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&
						!bag.link_state[2]
						&&
						bag.components_number[Bag::Wax]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[2] = true;
					return 0;
				}
				else if(LastArea.Left == button_pos[3].Left
						&&
						LastArea.Right == button_pos[3].Right
						&&
						LastArea.Bottom == button_pos[3].Bottom
						&&
						LastArea.Top == button_pos[3].Top
						&&//有装置且已充能
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&
						!bag.link_state[3]
						&&
						bag.components_number[Bag::Quartz]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[3] = true;
					return 0;
				}
				else if(LastArea.Left == button_pos[4].Left
						&&
						LastArea.Right == button_pos[4].Right
						&&
						LastArea.Bottom == button_pos[4].Bottom
						&&
						LastArea.Top == button_pos[4].Top
						&&//有装置且已充能
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&
						!bag.link_state[4]
						&&
						bag.components_number[Bag::Silver]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[4] = true;
					return 0;
				}
				else if(LastArea.Left == button_pos[5].Left
						&&
						LastArea.Right == button_pos[5].Right
						&&
						LastArea.Bottom == button_pos[5].Bottom
						&&
						LastArea.Top == button_pos[5].Top
						&&//有装置且已充能
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&
						!bag.link_state[5]
						&&
						bag.components_number[Bag::Gum]>0){
					bag.treasure[Bag::TheAncientRecord] = 2;
					bag.link_state[5] = true;
					return 0;
				}
			}
		}
	}
	return 1;//1:异常返回










}

int Controller::DrawAncientRecord(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 7 });//统一起点
	cout<<"      使用远古记事";

	//SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"铅:   ";
	if(bag.construct[Bag::CrystalBattery]){//已获得
		if(bag.construct_state[Bag::CrystalBattery]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"水晶电池";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"硅土: ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"蜡:   ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"石英: ";
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"银:   ";
	if(bag.construct[Bag::ScryingLens]){//已获得
		if(bag.construct_state[Bag::ScryingLens]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"占卜透镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"橡胶: ";
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";
	
	//返回按钮
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";
	
	return 0;


}

int Controller::IntoSearchArea(){
	Clear();
	DrawInformationBar();
	DrawSearchArea();

	//按钮效果
	//6个地区的按钮和返回按钮
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域

	SMALL_RECT area[6];
	area[SearchArea::HaleBeardPeak]={8, 7, 15, 7};
	area[SearchArea::TheGreatWild]={22, 7, 29, 7,};
	area[SearchArea::RootStrangledMarshes]={36, 7, 43,7};
	area[SearchArea::GrassRockCanyon]={8, 12, 15, 12};
	area[SearchArea::RuinedCityOfTheAncients]={22, 12, 29, 12};
	area[SearchArea::TheFireMaw]={36, 12, 43,12};
	
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						// 背包按钮
						Rect = bag_position;
						LastArea = bag_position;
					}
					//{8,7,15,7} {22, 7, 29, 7,} {36, 7, 43,7}
					//{8,12,15,12} {22, 12, 29, 12,} {36, 12, 43,12}
				else if((MousePos.X >= area[SearchArea::HaleBeardPeak].Left && MousePos.X <= area[SearchArea::HaleBeardPeak].Right)
					&&
					(MousePos.Y <= area[SearchArea::HaleBeardPeak].Bottom && MousePos.Y >= area[SearchArea::HaleBeardPeak].Top)){
						Rect = area[SearchArea::HaleBeardPeak];
						LastArea = area[SearchArea::HaleBeardPeak];
					}
				else if((MousePos.X >= area[SearchArea::TheGreatWild].Left && MousePos.X <= area[SearchArea::TheGreatWild].Right)
					&&
					(MousePos.Y <= area[SearchArea::TheGreatWild].Bottom && MousePos.Y >= area[SearchArea::TheGreatWild].Top)){
						Rect = area[SearchArea::TheGreatWild];
						LastArea = area[SearchArea::TheGreatWild];
					}
				else if((MousePos.X >= area[SearchArea::RootStrangledMarshes].Left && MousePos.X <= area[SearchArea::RootStrangledMarshes].Right)
					&&
					(MousePos.Y <= area[SearchArea::RootStrangledMarshes].Bottom && MousePos.Y >= area[SearchArea::RootStrangledMarshes].Top)){
						Rect = area[SearchArea::RootStrangledMarshes];
						LastArea = area[SearchArea::RootStrangledMarshes];
					}
				else if((MousePos.X >= area[SearchArea::GrassRockCanyon].Left && MousePos.X <= area[SearchArea::GrassRockCanyon].Right)
					&&
					(MousePos.Y <= area[SearchArea::GrassRockCanyon].Bottom && MousePos.Y >= area[SearchArea::GrassRockCanyon].Top)){
						Rect = area[SearchArea::GrassRockCanyon];
						LastArea = area[SearchArea::GrassRockCanyon];
					}
				else if((MousePos.X >= area[SearchArea::RuinedCityOfTheAncients].Left && MousePos.X <= area[SearchArea::RuinedCityOfTheAncients].Right)
					&&
					(MousePos.Y <= area[SearchArea::RuinedCityOfTheAncients].Bottom && MousePos.Y >= area[SearchArea::RuinedCityOfTheAncients].Top)){
						Rect = area[SearchArea::RuinedCityOfTheAncients];
						LastArea = area[SearchArea::RuinedCityOfTheAncients];
					}
				else if((MousePos.X >= area[SearchArea::TheFireMaw].Left && MousePos.X <= area[SearchArea::TheFireMaw].Right)
					&&
					(MousePos.Y <= area[SearchArea::TheFireMaw].Bottom && MousePos.Y >= area[SearchArea::TheFireMaw].Top)){
						Rect = area[SearchArea::TheFireMaw];
						LastArea = area[SearchArea::TheFireMaw];
					}
				
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				//与bag_back_position的区域一样
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = SEARCH_AREA_INTERFACE;
					return 0;
				}
				//打开背包
				else if(LastArea.Left == bag_position.Left 
					&& 
					LastArea.Right == bag_position.Right){
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = OPEN_BAG;
					Clear();
					IntoBag();
					bag.last_state = OPEN_BAG;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}

				//选择探索区域
				
				else if(LastArea.Left == area[SearchArea::HaleBeardPeak].Left
						&&
						LastArea.Right == area[SearchArea::HaleBeardPeak].Right
						&&
						LastArea.Bottom == area[SearchArea::HaleBeardPeak].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::HaleBeardPeak);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				else if(LastArea.Left == area[SearchArea::TheGreatWild].Left
						&&
						LastArea.Right == area[SearchArea::TheGreatWild].Right
						&&
						LastArea.Bottom == area[SearchArea::TheGreatWild].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::TheGreatWild);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				else if(LastArea.Left == area[SearchArea::RootStrangledMarshes].Left
						&&
						LastArea.Right == area[SearchArea::RootStrangledMarshes].Right
						&&
						LastArea.Bottom == area[SearchArea::RootStrangledMarshes].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::RootStrangledMarshes);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				else if(LastArea.Left == area[SearchArea::GrassRockCanyon].Left
						&&
						LastArea.Right == area[SearchArea::GrassRockCanyon].Right
						&&
						LastArea.Bottom == area[SearchArea::GrassRockCanyon].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::GrassRockCanyon);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				else if(LastArea.Left == area[SearchArea::RuinedCityOfTheAncients].Left
						&&
						LastArea.Right == area[SearchArea::RuinedCityOfTheAncients].Right
						&&
						LastArea.Bottom == area[SearchArea::RuinedCityOfTheAncients].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::RuinedCityOfTheAncients);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				else if(LastArea.Left == area[SearchArea::TheFireMaw].Left
						&&
						LastArea.Right == area[SearchArea::TheFireMaw].Right
						&&
						LastArea.Bottom == area[SearchArea::TheFireMaw].Bottom){
					Clear();
					
					bag.last_state = SEARCH_AREA_INTERFACE;
					bag.current_state = SEARCH_AREA;
					IntoSelectedSearchArea(SearchArea::TheFireMaw);

					bag.last_state = SEARCH_AREA;
					bag.current_state = SEARCH_AREA_INTERFACE;
				}
				
				if(bag.win_or_lose == 2){
					return 0;
				}
				Clear();
				DrawInformationBar();
				DrawSearchArea();
				

				
				Sleep(500);

				
			}
		}
	}
	return 1;//1:异常返回
}

int Controller::DrawSearchArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { 2, 7 });//统一起点
	cout<<"      苍髯群峰      莽苍荒原      扼根沼泽";
	SetConsoleCursorPosition(hOut, { 2, 8 });
	cout<<"装置: 平衡封印      神秘之镜      虚空之门";
	SetConsoleCursorPosition(hOut, { 2, 9 });
	cout<<"组件: 银            石英          橡胶";
	SetConsoleCursorPosition(hOut, { 2, 10 });
	cout<<"宝物: 冰晶胸甲      雷神手镯      夜光荧丝";

	SetConsoleCursorPosition(hOut, { 2, 12 });//统一起点
	cout<<"      玻璃峡谷      远古遗址      火焰山洞";
	SetConsoleCursorPosition(hOut, { 2, 13 });
	cout<<"装置: 黄金罗盘      占卜透镜      水晶电池";
	SetConsoleCursorPosition(hOut, { 2, 14 });
	cout<<"组件: 硅土          蜡            铅";
	SetConsoleCursorPosition(hOut, { 2, 15 });
	cout<<"宝物: 无限之秤      远古记事      熔岩碎片";

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";
	return 0;
}

int Controller::IntoSelectedSearchArea(int chose_area){
	search_area.current_search_area = chose_area;
	Clear();
	DrawInformationBar();
	DrawSelectedSearchArea();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//背包按钮
						Rect = bag_position;
						LastArea = bag_position;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//开始搜索按钮
						Rect = search_button;
						LastArea = search_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = SEARCH_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left 
						&& 
						LastArea.Right == bag_position.Right){
					// 背包
					bag.current_state = OPEN_BAG;
					bag.last_state = SEARCH_AREA;
					Clear();
					IntoBag();

					bag.current_state = SEARCH_AREA;
					bag.last_state = OPEN_BAG;
					
					Clear();
					DrawInformationBar();
					DrawSelectedSearchArea();
					
				}
				else if(LastArea.Left == search_button.Left 
						&& 
						LastArea.Right == search_button.Right){
					//进行搜索
					//!不用清空屏幕
					bag.current_state = SEARCH;
					bag.last_state = SEARCH_AREA;
					SetConsoleTextAttribute(hOut, 0x0007);
					SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
					cout<<"                       ";
					BeginSearch();
					bag.current_state = SEARCH_AREA;
					bag.last_state = SEARCH;
					
					Clear();
					DrawInformationBar();

					DrawSelectedSearchArea();
					SetConsoleTextAttribute(hOut, 0x0007);
					SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
					cout<<"继续搜索";
				}

				if(bag.win_or_lose == 2){
					return 0;
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:异常返回
}

int Controller::DrawSelectedSearchArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"开始搜索";
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"返回";
	
	return 0;
}

int Controller::BeginSearch(){
	//!不用清空屏幕
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域


	//设置输出文本属性
	SetConsoleTextAttribute(hOut, 0x0070);
	
	DrawSearch();
	//投掷3次2个骰子
	int a,b;
	int board[6]{0,0,0,0,0,0};
	SMALL_RECT botton_pos[6];
	botton_pos[0] = {17, 10, 19, 10};
	botton_pos[1] = {21, 10, 23, 10};
	botton_pos[2] = {25, 10, 27, 10};
	botton_pos[3] = {17, 12, 19, 12};
	botton_pos[4] = {21, 12, 23, 12};
	botton_pos[5] = {25, 12, 27, 12};
	
	srand(time(NULL));
	//循环3次
	for(int i=0; i<3; i++){
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		

		while (1) {//一级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//6个按钮
					if(	(MousePos.X >= botton_pos[0].Left && MousePos.X <= botton_pos[0].Right)
						&&
						(MousePos.Y <= botton_pos[0].Bottom && MousePos.Y >= botton_pos[0].Top)){
							Rect = botton_pos[0];
							LastArea = botton_pos[0];
						}
					else if((MousePos.X >= botton_pos[1].Left && MousePos.X <= botton_pos[1].Right)
							&&
							(MousePos.Y <= botton_pos[1].Bottom && MousePos.Y >= botton_pos[1].Top)){
							
							Rect = botton_pos[1];
							LastArea = botton_pos[1];
						}
					else if((MousePos.X >= botton_pos[2].Left && MousePos.X <= botton_pos[2].Right)
							&&
							(MousePos.Y <= botton_pos[2].Bottom && MousePos.Y >= botton_pos[2].Top)){
							
							Rect = botton_pos[2];
							LastArea = botton_pos[2];
						}
					else if((MousePos.X >= botton_pos[3].Left && MousePos.X <= botton_pos[3].Right)
							&&
							(MousePos.Y <= botton_pos[3].Bottom && MousePos.Y >= botton_pos[3].Top)){
							
							Rect = botton_pos[3];
							LastArea = botton_pos[3];
						}
					else if((MousePos.X >= botton_pos[4].Left && MousePos.X <= botton_pos[4].Right)
							&&
							(MousePos.Y <= botton_pos[4].Bottom && MousePos.Y >= botton_pos[4].Top)){
							
							Rect = botton_pos[4];
							LastArea = botton_pos[4];
						}
					else if((MousePos.X >= botton_pos[5].Left && MousePos.X <= botton_pos[5].Right)
							&&
							(MousePos.Y <= botton_pos[5].Bottom && MousePos.Y >= botton_pos[5].Top)){
							
							Rect = botton_pos[5];
							LastArea = botton_pos[5];
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//填格子
					if(	LastArea.Left == botton_pos[0].Left 
						&& 
						LastArea.Right == botton_pos[0].Right
						&&
                        LastArea.Bottom == botton_pos[0].Bottom
						&&
                        !board[0]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[0].Left, botton_pos[0].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[0]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[0]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(LastArea.Left == botton_pos[1].Left 
						&& 
						LastArea.Right == botton_pos[1].Right
						&&
                        LastArea.Bottom == botton_pos[1].Bottom
						&&
						!board[1]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[1].Left, botton_pos[1].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[1]=a;
								a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[1]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[2].Left 
						&& 
						LastArea.Right == botton_pos[2].Right
						&&
                        LastArea.Bottom == botton_pos[2].Bottom
						&&
                        
						!board[2]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[2].Left, botton_pos[2].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[2]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[2]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[3].Left 
						&& 
						LastArea.Right == botton_pos[3].Right
						&&
                        LastArea.Bottom == botton_pos[3].Bottom
						&&
                        
						!board[3]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[3].Left, botton_pos[3].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[3] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[3] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[4].Left 
						&& 
						LastArea.Right == botton_pos[4].Right
						&&
                        LastArea.Bottom == botton_pos[4].Bottom
						&&
                        
						!board[4]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[4].Left, botton_pos[4].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[4] = a;a=0;
                                
							}
							else if(b!=0){
								cout<<" "<<b;
                                board[4] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[5].Left 
						&& 
						LastArea.Right == botton_pos[5].Right
						&&
                        LastArea.Bottom == botton_pos[5].Bottom
						&&
                        
						!board[5]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[5].Left, botton_pos[5].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[5] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
                                board[5] = b;
                                b=0;
								break;
							}
							else
								break;
					}
					Sleep(500);
				}
			}
		}

	}



	a = board[0]*100 + board[1]*10 + board[2];
	b = board[3]*100 + board[4]*10 + board[5];
	int result = a-b;
	SetConsoleCursorPosition(hOut, {16, 14});
	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
	cout<<" 探索结果为"<<result;
	
	if(bag.tool_belt.dowing_rod){//探索权杖已充能
		SetConsoleCursorPosition(hOut, { 10, 15 });
		cout<<"是否使用探索权杖 是 否";//27 30
		
		SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
		LastArea={ 0,0,-1,-1 };//初始化区域
		while (1) {//一级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//2个按钮
					if(	(MousePos.X >= yes.Left && MousePos.X <= yes.Right)
						&&
						(MousePos.Y <= yes.Bottom && MousePos.Y >= yes.Top)){
							Rect = yes;
							LastArea = yes;
						}
					else if((MousePos.X >= no.Left && MousePos.X <= no.Right)
							&&
							(MousePos.Y <= no.Bottom && MousePos.Y >= no.Top)){
							
							Rect = no;
							LastArea = no;
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					
					if(	LastArea.Left == yes.Left 
						&& 
						LastArea.Right == yes.Right
						&&
                        LastArea.Bottom == yes.Bottom){
						//使用探索权杖
						if(result <= 100)
							result = 0;
						else
							result -= 100;
						bag.tool_belt.dowing_rod = false;
						
						break;
					}
					else if(LastArea.Left == no.Left 
						&& 
						LastArea.Right == no.Right
						&&
                        LastArea.Bottom == no.Bottom){
						//不使用
						
						break;
					}
				
					Sleep(500);
				}
			}
		}
		
	}


	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
	SetConsoleCursorPosition(hOut, { 10, 15 });
	cout<<"                         ";
	SetConsoleCursorPosition(hOut, { 16, 14 });
	cout<<"               ";
	SetConsoleCursorPosition(hOut, {16, 14});
	cout<<" 探索结果为"<<result;

	SetConsoleCursorPosition(hOut, {14, 15});
	//输出敌人或宝物
	
	if(result == 0){
		SetConsoleCursorPosition(hOut, {10, 15});
		cout<<"完美探索，获得已充能的装置"<<search_area.area[search_area.current_search_area].construct_name;
		
		bag.construct[search_area.current_search_area]=true;
		bag.construct_state[search_area.current_search_area]=true;
		
		SetConsoleCursorPosition(hOut, {14, 16});
		cout<<"上帝之手增加5点";
		bag.gods_hand += 5;
		Sleep(3000);
	}
	else if(result > 0 && result <= 10){//发现装置
		cout<<"发现装置 "<<search_area.area[search_area.current_search_area].construct_name;
		bag.construct[search_area.current_search_area]=true;
		Sleep(3000);
	}
	else if(result > 10 && result <= 100){
		//发现组件
		SetConsoleCursorPosition(hOut, {16, 15});
		cout<<"发现组件 "<<search_area.area[search_area.current_search_area].component_name;
		bag.components_number[search_area.current_search_area]++;
		Sleep(3000);
	}
	//遭遇敌人
	else{
		
		//荧光艹
		bool flag =false;
		if(bag.treasure[Bag::ShimmeringMoonlace]){//夜光荧丝已获得
			SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
			SetConsoleCursorPosition(hOut, { 10, 15 });
			cout<<"是否使用夜光荧丝 是 否";//27 30
			Sleep(500);
			SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
			LastArea={ 0,0,-1,-1 };//初始化区域
			while (1) {//一级循环
				ReadConsoleInput(hIn, &record, 1, temp);
				if (record.EventType == MOUSE_EVENT) {
					//cout<<"k";
					COORD MousePos = record.Event.MouseEvent.dwMousePosition;
					//判断鼠标位置
					if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
						||//注意Bottom和Top的大小关系
						(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
						) {//光标所处区域发生改变
						//改变按钮的发亮状态
						//原本位置变暗
						FillConsoleOutputAttribute(	hOut, 0x0007, 
													LastArea.Right - LastArea.Left + 1, 
													COORD{LastArea.Left, LastArea.Top}, temp);

						SMALL_RECT Rect;
						//2个按钮
						if(	(MousePos.X >= yes.Left && MousePos.X <= yes.Right)
							&&
							(MousePos.Y <= yes.Bottom && MousePos.Y >= yes.Top)){
								Rect = yes;
								LastArea = yes;
							}
						else if((MousePos.X >= no.Left && MousePos.X <= no.Right)
								&&
								(MousePos.Y <= no.Bottom && MousePos.Y >= no.Top)){
								
								Rect = no;
								LastArea = no;
							}
						else{
							LastArea = {0, 0, -1, -1};
							continue;
						}
						//新的位置变亮
						FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
					}
					
					//按下左键
					if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
						if(LastArea.Right == -1 && LastArea.Bottom == -1)
							continue;
						
						
						if(	LastArea.Left == yes.Left 
							&& 
							LastArea.Right == yes.Right
							&&
							LastArea.Bottom == yes.Bottom){
							//使用夜光荧丝
							flag = true;
							break;
						}
						else if(LastArea.Left == no.Left 
							&& 
							LastArea.Right == no.Right
							&&
							LastArea.Bottom == no.Bottom){
							//不使用
							flag = false;
							break;
						}
					
						Sleep(500);
					}
				}
			}
		}

		if(flag)//避免遭遇
			{}
		else{//不避免遭遇
			int level=1;

			SetConsoleCursorPosition(hOut, {10, 15});
			cout<<"                                                     ";
			SetConsoleCursorPosition(hOut, {14, 15});
			cout<<"遭遇敌人 ";
			//level 1
			if((result >=100 && result <= 199)||(result <= -1 && result >= -100)){
				cout<<search_area.area[search_area.current_search_area].enemy[0].name
					<<"(level 1)";
				level = 1;
			}
			//level 2
			else if((result >=200 && result <= 299)||(result <= -101 && result >= -200)){
				cout<<search_area.area[search_area.current_search_area].enemy[1].name
					<<"(level 2)";
				level = 2;
			}
			//level 3
			else if((result >=300 && result <= 399)||(result <= -201 && result >= -300)){
				cout<<search_area.area[search_area.current_search_area].enemy[2].name
					<<"(level 3)";
				level = 3;
			}
			//level 4
			else if((result >=400 && result <= 499)||(result <= -301 && result >= -400)){
				cout<<search_area.area[search_area.current_search_area].enemy[3].name
					<<"(level 4)";
				level = 4;
			}
			//level 5
			else if((result >=500 && result <= 555)||(result <= -401 && result >= -555)){
				cout<<search_area.area[search_area.current_search_area].enemy[4].name
					<<"(level 5)";
				level = 5;
			}

			Sleep(5000);
			//开始战斗
			Battle(level);
		}
	}
	
	DayEnd();//消耗一天
	
	return 0;
}

int Controller::Battle(int level){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域

	//SetConsoleTextAttribute(hOut, 0x0000);

	SetConsoleCursorPosition(hOut, {11, 10});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 12});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 14});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 15});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 16});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {search_button.Left, search_button.Top});
	cout<<"        ";
	
	bool use_paralysis_wand = false;

	if(bag.tool_belt.paralysis_wand){//探索权杖已充能
		SetConsoleCursorPosition(hOut, { 10, 15 });
		cout<<"是否使用麻痹魔杖 是 否";//27 30
		
		SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
		LastArea={ 0,0,-1,-1 };//初始化区域
		while (1) {//一级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//2个按钮
					if(	(MousePos.X >= yes.Left && MousePos.X <= yes.Right)
						&&
						(MousePos.Y <= yes.Bottom && MousePos.Y >= yes.Top)){
							Rect = yes;
							LastArea = yes;
						}
					else if((MousePos.X >= no.Left && MousePos.X <= no.Right)
							&&
							(MousePos.Y <= no.Bottom && MousePos.Y >= no.Top)){
							
							Rect = no;
							LastArea = no;
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					
					if(	LastArea.Left == yes.Left 
						&& 
						LastArea.Right == yes.Right
						&&
                        LastArea.Bottom == yes.Bottom){
						//使用麻痹魔杖
						
						use_paralysis_wand = true;
						bag.tool_belt.dowing_rod = false;
						
						break;
					}
					else if(LastArea.Left == no.Left 
						&& 
						LastArea.Right == no.Right
						&&
                        LastArea.Bottom == no.Bottom){
						//不使用
						use_paralysis_wand = false;
						break;
					}
				
					Sleep(500);
				}
			}
		}
	}
	SetConsoleCursorPosition(hOut, { 10, 15 });
	cout<<"                                 ";
	
	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"继续";//只有一个按钮
	
	srand(time(NULL));

	bool defeat = false;//是否打败敌人

	while(1){// 战斗循环
		
		//掷骰子

		int a,b;
		if(use_paralysis_wand){
			a = min((rand()%6 + 1 + 2), 6);
			b = min((rand()%6 + 1 + 2), 6);
		}
		else{
			a = rand()%6 + 1;
			b = rand()%6 + 1;
		}
		//展示骰子
		//*********************************************************************
		//*需要添加颜色模块
		SetConsoleTextAttribute(hOut, 0x0070);//设置输出文本属性

		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		//*********************************************************************
		SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
		//判断
		//if(	search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1
		//	||//受伤
		//	search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1){
		
		//每次都输出
			SetConsoleCursorPosition(hOut, {17, 10});
			cout<<"受到"
				<<	((search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1)
					+
					(search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1))
				<<"点伤害";

			bag.HP -= ((search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1)
					  +
					  (search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1));
		//}

		//TODO 更新血量
		SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
		cout << "背包  HP：" << bag.HP;

		if(search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==1
			||//打倒敌人
			search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==1){
			SetConsoleCursorPosition(hOut, {14, 11});
			cout<<"成功击败 "<<search_area.area[search_area.current_search_area].enemy[level-1].name;
			defeat = true;
			break;
		}
		//Sleep(2000);
		if(bag.HP <= 0)//昏迷了
			break;
		
		//活着，继续

		//按钮
		while (1) {//一级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
						&&
						(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
							//落在在返回按钮上
							Rect = bag_back_position;
							LastArea = bag_back_position;
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//退出界面
					if(	LastArea.Left == bag_back_position.Left 
						&& 
						LastArea.Right == bag_back_position.Right){
						break;//继续掷骰子
					}
				}
			}
		}
	}

	Sleep(2000);

	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
	
	SetConsoleCursorPosition(hOut, {11, 10});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 12});
	cout<<"                                 ";
	//结果判断
	SetConsoleCursorPosition(hOut, {14, 12});
	if(defeat && bag.HP){//打败敌人且活着
		cout<<"获得";
		if(level == 5){//获得宝物
			cout<<"宝物 "<<search_area.area[search_area.current_search_area].treasure_name;
			if(search_area.current_search_area != Bag::TheAncientRecord)//获得远古记事以外的宝物
				bag.treasure[search_area.current_search_area] = true;
			else{//获得远古记事
				if(bag.treasure[search_area.current_search_area] !=2)//远古记事未使用过
					bag.treasure[search_area.current_search_area] = 1;
				else//远古记事已使用过
					bag.treasure[search_area.current_search_area] = 2;
			}
				
					
			if(search_area.current_search_area == Bag::IcePlate){
				if(bag.treasure[Bag::TheMoltenSharo])//两个都获得了
					search_area.GetIcePlateAndTheMoltenSharo();
				else//只有一个
					search_area.GetIcePlate();
			}
			else if(search_area.current_search_area == Bag::TheMoltenSharo){
				if(bag.treasure[Bag::IcePlate])//两个都获得了
					search_area.GetIcePlateAndTheMoltenSharo();
				else//只有一个
					search_area.GetTheMoltenSharo();
			}
		}
		else{//获得组件
			cout<<"组件 "<<search_area.area[search_area.current_search_area].component_name;
			bag.components_number[search_area.current_search_area]++;
		}
	}
	else if(defeat){//打败敌人且死了
		cout<<"获得";
		if(level == 5){//获得宝物
			cout<<"宝物 "<<search_area.area[search_area.current_search_area].treasure_name;
			bag.treasure[search_area.current_search_area] = true;
			
		}
		else{//获得组件
			cout<<"组件 "<<search_area.area[search_area.current_search_area].component_name;
			bag.components_number[search_area.current_search_area]++;
		}
		
		SetConsoleCursorPosition(hOut, {17, 13});
		cout<<" 陷入昏迷";
		//额外消耗5天
		for(int i=0; i<6; i++)
			DayEnd();
		bag.HP = 6;//血量回满
		//time_system.day_now += 6;
	}
	else{//死了
		SetConsoleCursorPosition(hOut, {18, 12});
		cout<<" 战斗失败";
		
		//额外消耗5天
		for(int i=0; i<6; i++)
			DayEnd();
		bag.HP = 6;//血量回满
		//time_system.day_now += 6;
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"返回";
	
	//按钮
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					bag.current_state = BATTLE;
					return 0;//返回
				}
			}
		}
	}
	
	return 1;//异常退出
}

int Controller::DrawSearch(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//没有实际意义
	//掷色子界面
	// SetConsoleTextAttribute(hOut, 0x0070);

	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {19,8}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {23,8}, temp);
    
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,12}, temp);
	
	return 0;
}

int Controller::IntoWorkshop(){
	Clear();
	DrawInformationBar();
	DrawWorkshop();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//!注意Bottom和Top的大小关系
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//落在在背包按钮上
						Rect = bag_position;
						LastArea = bag_position;
					}
				else if((MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
						&&
						(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//返回
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= activate_area_button.Left && MousePos.X <= activate_area_button.Right)
						&&
						(MousePos.Y <= activate_area_button.Bottom && MousePos.Y >= activate_area_button.Top)){
						//启动装置按钮
						Rect = activate_area_button;
						LastArea = activate_area_button;
					}
				else if((MousePos.X >= link_area_button.Left && MousePos.X <= link_area_button.Right)
						&&
						(MousePos.Y <= link_area_button.Bottom && MousePos.Y >= link_area_button.Top)){
						//链接区域按钮
						Rect = link_area_button;
						LastArea = link_area_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
					
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//进行选择,改变区域
				if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
					//进入背包界面
					bag.last_state = ARTIFACT_WORKSHOP;
					bag.current_state = OPEN_BAG;
					IntoBag();
					Clear();
	
					bag.last_state = OPEN_BAG;
					bag.current_state = ARTIFACT_WORKSHOP;
				
					DrawWorkshop();
				}
				else if(LastArea.Left == bag_back_position.Left && LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = ARTIFACT_WORKSHOP;
					bag.current_state = SELECT_AREA;
					return 0;
				}
				else if(LastArea.Left == activate_area_button.Left 
						&& 
						LastArea.Right == activate_area_button.Right
						&&
						LastArea.Bottom == activate_area_button.Bottom){
						//进入启动装置界面
						bag.last_state = ARTIFACT_WORKSHOP;
						bag.current_state = ACTIVATE_AREA;
						IntoActivateArea();
						
						bag.last_state = ACTIVATE_AREA;
						bag.current_state = ARTIFACT_WORKSHOP;
						
						Clear();
						DrawWorkshop();
				}
				else if(LastArea.Left == link_area_button.Left 
						&& 
						LastArea.Right == link_area_button.Right
						&&
						LastArea.Bottom == link_area_button.Bottom){
						//进入链接区域界面
						bag.last_state = ARTIFACT_WORKSHOP;
						bag.current_state = LINK_AREA;
						IntoLinkArea();
						
						bag.last_state = LINK_AREA;
						bag.current_state = ARTIFACT_WORKSHOP;
						
						Clear();
						DrawWorkshop();
				}
				else if(LastArea.Left == bag_back_position.Left && LastArea.Right == bag_back_position.Right){
					//返回
					bag.last_state = ARTIFACT_WORKSHOP;
					return 0;
				}

				if(bag.win_or_lose == 2){
					return 0;
				}

				Sleep(500);
			}
		}
	}
	
	return 1;//异常退出
}

int Controller::DrawWorkshop(){
	DrawInformationBar();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hOut, COORD{ activate_area_button.Left, activate_area_button.Top });
	cout << "启动装置";
	SetConsoleCursorPosition(hOut, COORD{ link_area_button.Left, link_area_button.Top });
	cout << "链接区域";

	//返回按钮
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";

	return 0;
}

int Controller::IntoActivateArea(){
	Clear();
	DrawInformationBar();
	DrawActivateArea();

	//按钮效果
	//6个装置的按钮和返回按钮
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域

	SMALL_RECT area[6];
	area[Bag::SealOfBalance]={6, 9, 13, 9};//+7
	area[Bag::HermeticMirror]={24, 9, 31, 9,};
	area[Bag::VoidGate]={6, 11, 13, 11};
	area[Bag::GoldenChassis]={24, 11, 31, 11,};
	area[Bag::ScryingLens]={6, 13, 13, 13};
	area[Bag::CrystalBattery]={24, 13, 31, 13,};
	
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((	MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//落在在背包按钮上
						Rect = bag_position;
						LastArea = bag_position;
					}
					//{8,7,15,7} {22, 7, 29, 7,} {36, 7, 43,7}
					//{8,12,15,12} {22, 12, 29, 12,} {36, 12, 43,12}
				else if((MousePos.X >= area[Bag::SealOfBalance].Left && MousePos.X <= area[Bag::SealOfBalance].Right)
					&&
					(MousePos.Y <= area[Bag::SealOfBalance].Bottom && MousePos.Y >= area[Bag::SealOfBalance].Top)){
						Rect = area[Bag::SealOfBalance];
						LastArea = area[Bag::SealOfBalance];
					}
				else if((MousePos.X >= area[Bag::HermeticMirror].Left && MousePos.X <= area[Bag::HermeticMirror].Right)
					&&
					(MousePos.Y <= area[Bag::HermeticMirror].Bottom && MousePos.Y >= area[Bag::HermeticMirror].Top)){
						Rect = area[Bag::HermeticMirror];
						LastArea = area[Bag::HermeticMirror];
					}
				else if((MousePos.X >= area[Bag::VoidGate].Left && MousePos.X <= area[Bag::VoidGate].Right)
					&&
					(MousePos.Y <= area[Bag::VoidGate].Bottom && MousePos.Y >= area[Bag::VoidGate].Top)){
						Rect = area[Bag::VoidGate];
						LastArea = area[Bag::VoidGate];
					}
				else if((MousePos.X >= area[Bag::GoldenChassis].Left && MousePos.X <= area[Bag::GoldenChassis].Right)
					&&
					(MousePos.Y <= area[Bag::GoldenChassis].Bottom && MousePos.Y >= area[Bag::GoldenChassis].Top)){
						Rect = area[Bag::GoldenChassis];
						LastArea = area[Bag::GoldenChassis];
					}
				else if((MousePos.X >= area[Bag::ScryingLens].Left && MousePos.X <= area[Bag::ScryingLens].Right)
					&&
					(MousePos.Y <= area[Bag::ScryingLens].Bottom && MousePos.Y >= area[Bag::ScryingLens].Top)){
						Rect = area[Bag::ScryingLens];
						LastArea = area[Bag::ScryingLens];
					}
				else if((MousePos.X >= area[Bag::CrystalBattery].Left && MousePos.X <= area[Bag::CrystalBattery].Right)
					&&
					(MousePos.Y <= area[Bag::CrystalBattery].Bottom && MousePos.Y >= area[Bag::CrystalBattery].Top)){
						Rect = area[Bag::CrystalBattery];
						LastArea = area[Bag::CrystalBattery];
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				//与bag_back_position的区域一样
				if(	LastArea.Left == bag_back_position.Left 
					&& //返回
					LastArea.Right == bag_back_position.Right){
					//Sleep(1000);
					Clear();
					bag.last_state = ACTIVATE_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left 
						&& 
						LastArea.Right == bag_position.Right){
						// 背包
						bag.current_state = OPEN_BAG;
						bag.last_state = ACTIVATE_AREA;
						Clear();
						IntoBag();
						bag.current_state = ACTIVATE_AREA;
						bag.last_state = OPEN_BAG;
				}

				//选择启动装置
				else if(LastArea.Left == area[Bag::SealOfBalance].Left
						&&
						LastArea.Right == area[Bag::SealOfBalance].Right
						&&
						LastArea.Bottom == area[Bag::SealOfBalance].Bottom
						&&// 已获得装置
						bag.construct[Bag::SealOfBalance]
						&&//未充能
						!bag.construct_state[Bag::SealOfBalance]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::SealOfBalance);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				else if(LastArea.Left == area[Bag::HermeticMirror].Left
						&&
						LastArea.Right == area[Bag::HermeticMirror].Right
						&&
						LastArea.Bottom == area[Bag::HermeticMirror].Bottom
						&&// 已获得装置
						bag.construct[Bag::HermeticMirror]
						&&//未充能
						!bag.construct_state[Bag::HermeticMirror]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::HermeticMirror);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				else if(LastArea.Left == area[Bag::VoidGate].Left
						&&
						LastArea.Right == area[Bag::VoidGate].Right
						&&
						LastArea.Bottom == area[Bag::VoidGate].Bottom
						&&// 已获得装置
						bag.construct[Bag::VoidGate]
						&&//未充能
						!bag.construct_state[Bag::VoidGate]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::VoidGate);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				else if(LastArea.Left == area[Bag::GoldenChassis].Left
						&&
						LastArea.Right == area[Bag::GoldenChassis].Right
						&&
						LastArea.Bottom == area[Bag::GoldenChassis].Bottom
						&&// 已获得装置
						bag.construct[Bag::GoldenChassis]
						&&//未充能
						!bag.construct_state[Bag::GoldenChassis]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::GoldenChassis);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				else if(LastArea.Left == area[Bag::ScryingLens].Left
						&&
						LastArea.Right == area[Bag::ScryingLens].Right
						&&
						LastArea.Bottom == area[Bag::ScryingLens].Bottom
						&&// 已获得装置
						bag.construct[Bag::ScryingLens]
						&&//未充能
						!bag.construct_state[Bag::ScryingLens]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::ScryingLens);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				else if(LastArea.Left == area[Bag::CrystalBattery].Left
						&&
						LastArea.Right == area[Bag::CrystalBattery].Right
						&&
						LastArea.Bottom == area[Bag::CrystalBattery].Bottom
						&&// 已获得装置
						bag.construct[Bag::CrystalBattery]
						&&//未充能
						!bag.construct_state[Bag::CrystalBattery]){
					bag.last_state = ACTIVATE_AREA;
					bag.current_state = ACTIVATE;
					IntoActivate(Bag::CrystalBattery);
					bag.last_state = ACTIVATE;
					bag.current_state = ACTIVATE_AREA;
					Clear();
					DrawInformationBar();
					DrawActivateArea();
				}
				
				Clear();
				DrawInformationBar();
				DrawActivateArea();
				Sleep(500);
			}
		}
		
	}
	return 1;//1:异常返回
}

int Controller::DrawActivateArea(){

	SMALL_RECT area[6];
	area[Bag::SealOfBalance]={6, 9, 13, 9};//+7
	area[Bag::HermeticMirror]={24, 9, 31, 9,};
	area[Bag::VoidGate]={6, 11, 13, 11};
	area[Bag::GoldenChassis]={24, 11, 31, 11,};
	area[Bag::ScryingLens]={6, 13, 13, 13};
	area[Bag::CrystalBattery]={24, 13, 31, 13,};
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::SealOfBalance].Left, area[Bag::SealOfBalance].Top });//统一起点
	cout<<"平衡封印:";
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}
		
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::HermeticMirror].Left, area[Bag::HermeticMirror].Top });
	cout<<"神秘之镜:";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::VoidGate].Left, area[Bag::VoidGate].Top });//统一起点
	cout<<"虚空之门:";
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::GoldenChassis].Left, area[Bag::GoldenChassis].Top });
	cout<<"黄金罗盘:";
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::ScryingLens].Left, area[Bag::ScryingLens].Top });//统一起点
	cout<<"占卜透镜:";
	if(bag.construct[Bag::ScryingLens]){//已获得
		if(bag.construct_state[Bag::ScryingLens]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::CrystalBattery].Left, area[Bag::CrystalBattery].Top });
	cout<<"水晶电池:";
	if(bag.construct[Bag::CrystalBattery]){//已获得
		if(bag.construct_state[Bag::CrystalBattery]){//已充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"已充能";
		}
		else{//未充能
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"未充能";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"未获得";
	}
	
	//返回按钮
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";
	return 0;
}

int Controller::IntoActivate(int chose_construct){
	Clear();
	DrawInformationBar();
	DrawActivate(chose_construct);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域

	SetConsoleTextAttribute(hOut, 0x0070);//设置输出文本属性

	
	int a,b;
	int board[6]{0,0,0,0,0,0};
	SMALL_RECT botton_pos[6];
	botton_pos[0] = {17, 10, 19, 10};
	botton_pos[1] = {21, 10, 23, 10};
	botton_pos[2] = {25, 10, 27, 10};
	botton_pos[3] = {17, 12, 19, 12};
	botton_pos[4] = {21, 12, 23, 12};
	botton_pos[5] = {25, 12, 27, 12};
	
	srand(time(NULL));
	//循环多次，多次掷骰子
	for(int i=0; i<3; i++){//一级循环
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		
		//填骰子
		while (1) {//二级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//7个按钮
					if(	(MousePos.X >= botton_pos[0].Left && MousePos.X <= botton_pos[0].Right)
						&&
						(MousePos.Y <= botton_pos[0].Bottom && MousePos.Y >= botton_pos[0].Top)){
							Rect = botton_pos[0];
							LastArea = botton_pos[0];
						}
					else if((MousePos.X >= botton_pos[1].Left && MousePos.X <= botton_pos[1].Right)
							&&
							(MousePos.Y <= botton_pos[1].Bottom && MousePos.Y >= botton_pos[1].Top)){
							
							Rect = botton_pos[1];
							LastArea = botton_pos[1];
						}
					else if((MousePos.X >= botton_pos[2].Left && MousePos.X <= botton_pos[2].Right)
							&&
							(MousePos.Y <= botton_pos[2].Bottom && MousePos.Y >= botton_pos[2].Top)){
							
							Rect = botton_pos[2];
							LastArea = botton_pos[2];
						}
					else if((MousePos.X >= botton_pos[3].Left && MousePos.X <= botton_pos[3].Right)
							&&
							(MousePos.Y <= botton_pos[3].Bottom && MousePos.Y >= botton_pos[3].Top)){
							
							Rect = botton_pos[3];
							LastArea = botton_pos[3];
						}
					else if((MousePos.X >= botton_pos[4].Left && MousePos.X <= botton_pos[4].Right)
							&&
							(MousePos.Y <= botton_pos[4].Bottom && MousePos.Y >= botton_pos[4].Top)){
							
							Rect = botton_pos[4];
							LastArea = botton_pos[4];
						}
					else if((MousePos.X >= botton_pos[5].Left && MousePos.X <= botton_pos[5].Right)
							&&
							(MousePos.Y <= botton_pos[5].Bottom && MousePos.Y >= botton_pos[5].Top)){
							
							Rect = botton_pos[5];
							LastArea = botton_pos[5];
						}
					else if((MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
							&&
							(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//填格子
					if(	LastArea.Left == botton_pos[0].Left 
						&& 
						LastArea.Right == botton_pos[0].Right
						&&
                        LastArea.Bottom == botton_pos[0].Bottom
						&&
                        !board[0]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[0].Left, botton_pos[0].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
								
                                board[0]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
								
                                board[0]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(LastArea.Left == botton_pos[1].Left 
						&& 
						LastArea.Right == botton_pos[1].Right
						&&
                        LastArea.Bottom == botton_pos[1].Bottom
						&&
						!board[1]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[1].Left, botton_pos[1].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
                                board[1]=a;
								a=0;
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
								
                                board[1]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[2].Left 
						&& 
						LastArea.Right == botton_pos[2].Right
						&&
                        LastArea.Bottom == botton_pos[2].Bottom
						&&
                        
						!board[2]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[2].Left, botton_pos[2].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
								
                                board[2]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
								
                                board[2]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[3].Left 
						&& 
						LastArea.Right == botton_pos[3].Right
						&&
                        LastArea.Bottom == botton_pos[3].Bottom
						&&
                        
						!board[3]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[3].Left, botton_pos[3].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
								
                                board[3] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
								
                                board[3] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[4].Left 
						&& 
						LastArea.Right == botton_pos[4].Right
						&&
                        LastArea.Bottom == botton_pos[4].Bottom
						&&
                        
						!board[4]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[4].Left, botton_pos[4].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
                                board[4] = a;a=0;
                                
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
                                board[4] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(LastArea.Left == botton_pos[5].Left 
							&& 
							LastArea.Right == botton_pos[5].Right
							&&
							LastArea.Bottom == botton_pos[5].Bottom
							&&
							!board[5]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[5].Left, botton_pos[5].Top});
							if(a!=0){
								cout<<" "<<a<<" ";
                                board[5] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b<<" ";
                                board[5] = b;
                                b=0;
								break;
							}
							else
								break;
					}
					Sleep(300);
				}
			}
			
		}
	}

	SetConsoleCursorPosition(hOut, {17, 14});
	
	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性

	
	a = board[0] - board[3];
	if(a<0){
		cout<<"1号链接短路，减少1生命值";
		bag.HP--;
	}
	else{
		cout<<"1号链接成功";
	}

	SetConsoleCursorPosition(hOut, {17, 15});
	a = board[1] - board[4];
	if(a<0){
		cout<<"2号链接短路，减少1生命值";
		bag.HP--;
	}
	else{
		cout<<"2号链接成功";
	}
	
	SetConsoleCursorPosition(hOut, {17, 16});
	a = board[2] - board[5];
	if(a<0){
		cout<<"3号链接短路，减少1生命值";
		bag.HP--;
	}
	else{
		cout<<"3号链接成功";
	}
	
	SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
	cout << "背包  HP：" << bag.HP<<" ";

	bag.construct_state[chose_construct] = true;

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";

	LastArea = {0, 0, -1, -1};
	//返回按钮
	while (1) {//二级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)) {
				//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				//返回按钮
				if((MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
						&&
						(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
					Rect = bag_back_position;
					LastArea = bag_back_position;
				}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}

				//新的位置变亮
				FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//返回
				if(	LastArea.Left == bag_back_position.Left 
						&& 
					LastArea.Right == bag_back_position.Right){
						return 0;
				}
			}
		}
	}
	return 1;
}

int Controller::DrawActivate(int chose_construct){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//没有实际意义

	SetConsoleTextAttribute(hOut, 0x0007);
	// SetConsoleCursorPosition(hOut, {2, 7});
	// cout<<"当前启动值:"<<bag.construct_state[chose_construct];
	//掷色子界面
	// SetConsoleTextAttribute(hOut, 0x0070);

	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {19,8}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {23,8}, temp);
    
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,12}, temp);
	
	//垃圾桶按钮
	//SetConsoleCursorPosition(hOut, { 36, 17 });
	//cout<<"丢弃";
	
	return 0;
}

int Controller::IntoLinkArea(){
	Clear();
	DrawInformationBar();
	DrawLinkArea();
	
	//TODO
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT button_pos[6];
	button_pos[0] = {23, 8, 24, 8};
	button_pos[1] = {23, 10, 24, 10};
	button_pos[2] = {23, 12, 24, 12};
	button_pos[3] = {23, 14, 24, 14};
	button_pos[4] = {23, 16, 24, 16};
	button_pos[5] = {23, 18, 24, 18};
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
						&&
						(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
							//落在在背包按钮上
							Rect = bag_position;
							LastArea = bag_position;
						}
				//链接按钮
				else if((MousePos.X >= button_pos[0].Left && MousePos.X <= button_pos[0].Right)
						&&
						(MousePos.Y <= button_pos[0].Bottom && MousePos.Y >= button_pos[0].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//未链接
						!bag.link_state[0]
						&&//有铅
						(bag.components_number[Bag::Lead]>0)){
						Rect = button_pos[0];
						LastArea = button_pos[0];
					}
				else if((MousePos.X >= button_pos[1].Left && MousePos.X <= button_pos[1].Right)
						&&
						(MousePos.Y <= button_pos[1].Bottom && MousePos.Y >= button_pos[1].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//未链接
						!bag.link_state[1]
						&&//有硅土
						(bag.components_number[Bag::Silica]>0)){
						Rect = button_pos[1];
						LastArea = button_pos[1];
					}
				else if((MousePos.X >= button_pos[2].Left && MousePos.X <= button_pos[2].Right)
						&&
						(MousePos.Y <= button_pos[2].Bottom && MousePos.Y >= button_pos[2].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//未链接
						!bag.link_state[2]
						&&//有蜡
						(bag.components_number[Bag::Wax]>0)){
						Rect = button_pos[2];
						LastArea = button_pos[2];
					}
				else if((MousePos.X >= button_pos[3].Left && MousePos.X <= button_pos[3].Right)
						&&
						(MousePos.Y <= button_pos[3].Bottom && MousePos.Y >= button_pos[3].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//未链接
						!bag.link_state[3]
						&&//有石英
						(bag.components_number[Bag::Quartz]>0)){
						Rect = button_pos[3];
						LastArea = button_pos[3];
					}
				else if((MousePos.X >= button_pos[4].Left && MousePos.X <= button_pos[4].Right)
						&&
						(MousePos.Y <= button_pos[4].Bottom && MousePos.Y >= button_pos[4].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//未链接
						!bag.link_state[4]
						&&//有银
						(bag.components_number[Bag::Silver]>0)){
						Rect = button_pos[4];
						LastArea = button_pos[4];
					}
				else if((MousePos.X >= button_pos[5].Left && MousePos.X <= button_pos[5].Right)
						&&
						(MousePos.Y <= button_pos[5].Bottom && MousePos.Y >= button_pos[5].Top)
						&&//有装置且已充能
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//未链接
						!bag.link_state[5]
						&&//有橡胶
						(bag.components_number[Bag::Gum]>0)){
						Rect = button_pos[5];
						LastArea = button_pos[5];
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					
					bag.last_state = LINK_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
					//进入背包界面
					bag.last_state = LINK_AREA;
					bag.current_state = OPEN_BAG;
					IntoBag();
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK_AREA;
				}
				//链接按钮
				else if(LastArea.Left == button_pos[0].Left
						&&
						LastArea.Right == button_pos[0].Right
						&&
						LastArea.Bottom == button_pos[0].Bottom
						&&
						LastArea.Top == button_pos[0].Top
						&&//有装置且已充能
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&
						!bag.link_state[0]
						&&
						bag.components_number[Bag::Lead]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(0);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}
				else if(LastArea.Left == button_pos[1].Left
						&&
						LastArea.Right == button_pos[1].Right
						&&
						LastArea.Bottom == button_pos[1].Bottom
						&&
						LastArea.Top == button_pos[1].Top
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&
						!bag.link_state[1]
						&&
						bag.components_number[Bag::Silica]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(1);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}
				else if(LastArea.Left == button_pos[2].Left
						&&
						LastArea.Right == button_pos[2].Right
						&&
						LastArea.Bottom == button_pos[2].Bottom
						&&
						LastArea.Top == button_pos[2].Top
						&&//有装置且已充能
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&
						!bag.link_state[2]
						&&
						bag.components_number[Bag::Wax]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(2);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}
				else if(LastArea.Left == button_pos[3].Left
						&&
						LastArea.Right == button_pos[3].Right
						&&
						LastArea.Bottom == button_pos[3].Bottom
						&&
						LastArea.Top == button_pos[3].Top
						&&//有装置且已充能
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&
						!bag.link_state[3]
						&&
						bag.components_number[Bag::Quartz]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(3);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}
				else if(LastArea.Left == button_pos[4].Left
						&&
						LastArea.Right == button_pos[4].Right
						&&
						LastArea.Bottom == button_pos[4].Bottom
						&&
						LastArea.Top == button_pos[4].Top
						&&//有装置且已充能
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&
						!bag.link_state[4]
						&&
						bag.components_number[Bag::Silver]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(4);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}
				else if(LastArea.Left == button_pos[5].Left
						&&
						LastArea.Right == button_pos[5].Right
						&&
						LastArea.Bottom == button_pos[5].Bottom
						&&
						LastArea.Top == button_pos[5].Top
						&&//有装置且已充能
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&
						!bag.link_state[5]
						&&
						bag.components_number[Bag::Gum]>0){
					bag.last_state = LINK_AREA;
					bag.current_state = LINK;
					IntoLink(5);
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK;
				}

				if(bag.win_or_lose == 2){
					//失败
					return 0;
				}
			}
		}
	}
	return 1;//1:异常返回
}

int Controller::DrawLinkArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/************************************************
	 水晶电池 黄金罗盘
	 神秘之镜 平衡封印
	 神秘之镜 虚空之门
	 平衡封印 黄金罗盘
	 占卜透镜 平衡封印
	 黄金罗盘 虚空之门
 ************************************************/
/*
	SetConsoleCursorPosition(hOut, { 9, 7 });//统一起点
	cout<<"      链接装置";
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"铅:   水晶电池"<<(bag.link_state[0]?"■":"□")<<"黄金罗盘";
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"硅土: 神秘之镜"<<(bag.link_state[1]?"■":"□")<<"平衡封印";
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"蜡:   神秘之镜"<<(bag.link_state[2]?"■":"□")<<"虚空之门";
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"石英: 平衡封印"<<(bag.link_state[3]?"■":"□")<<"黄金罗盘";
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"银:   占卜透镜"<<(bag.link_state[4]?"■":"□")<<"平衡封印";
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"橡胶: 黄金罗盘"<<(bag.link_state[5]?"■":"□")<<"虚空之门";
	*/

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, {2, 6});
	cout<<"当前启动值:"<<bag.activate_hard_level;

	SetConsoleCursorPosition(hOut, { 9, 7 });//统一起点
	cout<<"      链接装置";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"铅:   ";
	if(bag.construct[Bag::CrystalBattery]){//已获得
		if(bag.construct_state[Bag::CrystalBattery]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"水晶电池";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"硅土: ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"蜡:   ";
	if(bag.construct[Bag::HermeticMirror]){//已获得
		if(bag.construct_state[Bag::HermeticMirror]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"神秘之镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"石英: ";
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"■":"□");
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"银:   ";
	if(bag.construct[Bag::ScryingLens]){//已获得
		if(bag.construct_state[Bag::ScryingLens]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"占卜透镜";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"■":"□");
	if(bag.construct[Bag::SealOfBalance]){//已获得
		if(bag.construct_state[Bag::SealOfBalance]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"平衡封印";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"橡胶: ";
	if(bag.construct[Bag::GoldenChassis]){//已获得
		if(bag.construct_state[Bag::GoldenChassis]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"黄金罗盘";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"■":"□");
	if(bag.construct[Bag::VoidGate]){//已获得
		if(bag.construct_state[Bag::VoidGate]){//已连接
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//未获得
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"虚空之门";
	
	//返回按钮
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";
	
	return 0;
}

int Controller::IntoLink(int chose_link){
	Clear();
	DrawInformationBar();
	DrawLink(chose_link);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域

	SetConsoleTextAttribute(hOut, 0x0070);//设置输出文本属性

	
	int a,b;
	int board[6]{0,0,0,0,0,0};
	SMALL_RECT botton_pos[6];
	botton_pos[0] = {17, 10, 19, 10};
	botton_pos[1] = {21, 10, 23, 10};
	botton_pos[2] = {25, 10, 27, 10};
	botton_pos[3] = {17, 12, 19, 12};
	botton_pos[4] = {21, 12, 23, 12};
	botton_pos[5] = {25, 12, 27, 12};
	
	srand(time(NULL));
	//循环3次
	for(int i=0; i<3; i++){//一级循环
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		
		//填骰子
		while (1) {//二级循环
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//判断鼠标位置
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//注意Bottom和Top的大小关系
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//光标所处区域发生改变
					//改变按钮的发亮状态
					//原本位置变暗
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//7个按钮
					if(	(MousePos.X >= botton_pos[0].Left && MousePos.X <= botton_pos[0].Right)
						&&
						(MousePos.Y <= botton_pos[0].Bottom && MousePos.Y >= botton_pos[0].Top)){
							Rect = botton_pos[0];
							LastArea = botton_pos[0];
						}
					else if((MousePos.X >= botton_pos[1].Left && MousePos.X <= botton_pos[1].Right)
							&&
							(MousePos.Y <= botton_pos[1].Bottom && MousePos.Y >= botton_pos[1].Top)){
							
							Rect = botton_pos[1];
							LastArea = botton_pos[1];
						}
					else if((MousePos.X >= botton_pos[2].Left && MousePos.X <= botton_pos[2].Right)
							&&
							(MousePos.Y <= botton_pos[2].Bottom && MousePos.Y >= botton_pos[2].Top)){
							
							Rect = botton_pos[2];
							LastArea = botton_pos[2];
						}
					else if((MousePos.X >= botton_pos[3].Left && MousePos.X <= botton_pos[3].Right)
							&&
							(MousePos.Y <= botton_pos[3].Bottom && MousePos.Y >= botton_pos[3].Top)){
							
							Rect = botton_pos[3];
							LastArea = botton_pos[3];
						}
					else if((MousePos.X >= botton_pos[4].Left && MousePos.X <= botton_pos[4].Right)
							&&
							(MousePos.Y <= botton_pos[4].Bottom && MousePos.Y >= botton_pos[4].Top)){
							
							Rect = botton_pos[4];
							LastArea = botton_pos[4];
						}
					else if((MousePos.X >= botton_pos[5].Left && MousePos.X <= botton_pos[5].Right)
							&&
							(MousePos.Y <= botton_pos[5].Bottom && MousePos.Y >= botton_pos[5].Top)){
							
							Rect = botton_pos[5];
							LastArea = botton_pos[5];
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//新的位置变亮
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//按下左键
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//填格子
					if(	LastArea.Left == botton_pos[0].Left 
						&& 
						LastArea.Right == botton_pos[0].Right
						&&
                        LastArea.Bottom == botton_pos[0].Bottom
						&&
                        !board[0]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[0].Left, botton_pos[0].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[0]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[0]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(LastArea.Left == botton_pos[1].Left 
						&& 
						LastArea.Right == botton_pos[1].Right
						&&
                        LastArea.Bottom == botton_pos[1].Bottom
						&&
						!board[1]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[1].Left, botton_pos[1].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[1]=a;
								a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[1]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[2].Left 
						&& 
						LastArea.Right == botton_pos[2].Right
						&&
                        LastArea.Bottom == botton_pos[2].Bottom
						&&
                        
						!board[2]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[2].Left, botton_pos[2].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[2]=a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[2]=b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[3].Left 
						&& 
						LastArea.Right == botton_pos[3].Right
						&&
                        LastArea.Bottom == botton_pos[3].Bottom
						&&
                        
						!board[3]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[3].Left, botton_pos[3].Top});
							if(a!=0){
								cout<<" "<<a;
								
                                board[3] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
								
                                board[3] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(	LastArea.Left == botton_pos[4].Left 
						&& 
						LastArea.Right == botton_pos[4].Right
						&&
                        LastArea.Bottom == botton_pos[4].Bottom
						&&
                        
						!board[4]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[4].Left, botton_pos[4].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[4] = a;a=0;
                                
							}
							else if(b!=0){
								cout<<" "<<b;
                                board[4] = b;b=0;
								break;
							}
							else
								break;
					}
					else if(LastArea.Left == botton_pos[5].Left 
							&& 
							LastArea.Right == botton_pos[5].Right
							&&
							LastArea.Bottom == botton_pos[5].Bottom
							&&
							!board[5]){
							SetConsoleCursorPosition(hOut, COORD{botton_pos[5].Left, botton_pos[5].Top});
							if(a!=0){
								cout<<" "<<a;
                                board[5] = a;a=0;
							}
							else if(b!=0){
								cout<<" "<<b;
                                board[5] = b;
                                b=0;
								break;
							}
							else
								break;
					}
					Sleep(500);
				}
			}
		}
	}

	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,12}, temp);

	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性

	bool SuccessfulLink = true;
	SetConsoleCursorPosition(hOut, {17, 14});
	a = board[0] - board[3];
	if(a<0){
		cout<<"1号链接短路，链接失败";
		SuccessfulLink = false;
	}
	else{
		cout<<"1号链接成功";
	}

	SetConsoleCursorPosition(hOut, {17, 15});
	a = board[1] - board[4];
	if(a<0){
		cout<<"2号链接短路，链接失败";
		SuccessfulLink = false;
	}
	else{
		cout<<"2号链接成功";
	}
	
	SetConsoleCursorPosition(hOut, {17, 16});
	a = board[3] - board[5];
	if(a<0){
		cout<<"3号链接短路，链接失败";
		SuccessfulLink = false;
	}
	else{
		cout<<"3号链接成功";
	}
	
	SetConsoleCursorPosition(hOut, {17, 17});
	if(SuccessfulLink){
		cout<<"链接成功，";
		SetConsoleCursorPosition(hOut, {17, 18});
		cout<<"启动值增加"<<board[0]+board[1]+board[2]-board[3]-board[4]-board[5];
		bag.activate_hard_level += (board[0]+board[1]+board[2]-board[3]-board[4]-board[5]);
		bag.link_state[chose_link] = true;
		a=1;//用来扣除组件
	}
	else{
		cout<<"链接失败，";
		SetConsoleCursorPosition(hOut, {17, 18});
		cout<<"额外扣除1个组件";
		a=2;
	}

	//扣除相应组件
	if(chose_link==0){
		bag.components_number[Bag::Lead] -= a;
	}
	if(chose_link==1){
		bag.components_number[Bag::Silica] -= a;
	}
	if(chose_link==2){
		bag.components_number[Bag::Wax] -= a;
	}
	if(chose_link==3){
		bag.components_number[Bag::Quartz] -= a;
	}
	if(chose_link==4){
		bag.components_number[Bag::Silver] -= a;
	}
	if(chose_link==5){
		bag.components_number[Bag::Gum] -= a;
	}
	//消耗1天
	DayEnd();

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"返回";


	//返回按钮
	LastArea={ 0,0,-1,-1 };//初始化
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = LINK;
					return 0;
				}
			}
		}
	}
	
	return 1;
}

int Controller::DrawLink(int chose_link){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//没有实际意义


	
	//掷色子界面
	// SetConsoleTextAttribute(hOut, 0x0070);

	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {19,8}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {23,8}, temp);
    
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,12}, temp);
	
	return 0;
}

int Controller::IntoWarn(){
	Clear();
	DrawInformationBar();
	DrawWarn();
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED);//设置输出文本属性
	for(int i=0; i<=10; i++){
		SetConsoleCursorPosition(hOut, {12, 17});
		cout<<10-i<<' ';
		Sleep(1000);
	}
	SetConsoleCursorPosition(hOut, {12, 17});
		cout<<"   ";

	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	int color = 0x0007;
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, color, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//落在在返回按钮上
						Rect = bag_back_position;
						LastArea = bag_back_position;
						color = 0x0007;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//背包按钮
						Rect = bag_position;
						LastArea = bag_position;
						color = 0x0007;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//确认继续按钮
						Rect = search_button;
						LastArea = search_button;
						color = FOREGROUND_RED | FOREGROUND_INTENSITY;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | color, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//退出界面
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = FINAL_ACTIVATE_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left 
						&& 
						LastArea.Right == bag_position.Right){
					// 背包
					bag.current_state = OPEN_BAG;
					bag.last_state = FINAL_ACTIVATE_AREA;
					Clear();
					IntoBag();

					bag.current_state = FINAL_ACTIVATE_AREA;
					bag.last_state = OPEN_BAG;
					
					Clear();
					DrawInformationBar();
					DrawWarn();
					Sleep(500);
				}
				else if(LastArea.Left == search_button.Left 
						&& //确认继续
						LastArea.Right == search_button.Right){

					bag.current_state = FINAL_ACTIVATE_AREA;;
					bag.last_state = FINAL_ACTIVATE;
					IntoFinalActivate();

					bag.current_state = FINAL_ACTIVATE;
					bag.last_state = FINAL_ACTIVATE_AREA;

					if(bag.win_or_lose!=1){//已进行最终启动
						return 0;//直接返回
					}

					//未进行最终启动
					
					Clear();
					DrawInformationBar();
					DrawWarn();
					Sleep(500);
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:异常返回

}

int Controller::DrawWarn(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
/************************************************
	               警告！
 	  	一旦开始最终启动，便不能停止，结果
	只有成功启动或者死亡，是否开始最终启动？
************************************************/	
	//rgb(255,0,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x0000);//设置输出文本属性

	SetConsoleCursorPosition(hOut, { 5, 8 });
	cout<<"               警告！";
	SetConsoleCursorPosition(hOut, { 5, 9 });
	cout<<"一旦开始最终启动，便不能停止，结果只";
	SetConsoleCursorPosition(hOut, { 5, 10 });
	cout<<"有成功启动或者死亡，是否开始最终启动？";

	
	SetConsoleTextAttribute(hOut, 0x0007);//rgb(180,180,180)
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"怂了";

	//rgb(255,0,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED | 0x0000);//设置输出文本属性
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"确认继续";
	
	
	return 0;
}

int Controller::IntoFinalActivate(){
	Clear();
	DrawInformationBar();
	DrawFinalActivate();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	
	while (1) {
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= sacrifice_button.Left && MousePos.X <= sacrifice_button.Right)
					&&
					(MousePos.Y <= sacrifice_button.Bottom && MousePos.Y >= sacrifice_button.Top)){
						//献祭按钮
						Rect = sacrifice_button;
						LastArea = sacrifice_button;
					}
				else if((MousePos.X >= final_activate_button.Left && MousePos.X <= final_activate_button.Right)
						&&
						(MousePos.Y <= final_activate_button.Bottom && MousePos.Y >= final_activate_button.Top)){
						//启动按钮
						Rect = final_activate_button;
						LastArea = final_activate_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
					
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);

			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				//进行选择,改变区域
				if(	LastArea.Left == sacrifice_button.Left && LastArea.Right == sacrifice_button.Right){
					//献祭
					
					if(bag.HP>0){
						//可以献祭
						bag.HP--;
						bag.activate_hard_level--;
						
						Clear();
						DrawInformationBar();
						DrawFinalActivate();
						SetConsoleCursorPosition(hOut, {10, 12});
						cout<<"献祭成功，启动值减少1点";
					}
					else{
						//没血了
						SetConsoleCursorPosition(hOut, {10, 12});					
						cout<<"  生命值不够，献祭失败 ";
					}
					
					Sleep(500);
					
				}
				else if(LastArea.Left == final_activate_button.Left && LastArea.Right == final_activate_button.Right){
					//!最终启动
					
					if(FinalActivate() == 2){//启动失败
						bag.win_or_lose = 2;
					}
					else{//启动成功
						bag.win_or_lose = 0;
					}

					return 0;
					
				};

				Sleep(500);
			}
		}
	}
	


}

int Controller::DrawFinalActivate(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//没有实际意义

	SetConsoleCursorPosition(hOut, {16, 8});
	cout<<"启动难度："<<bag.activate_hard_level;

	SetConsoleCursorPosition(hOut, {14, 14});
	cout<<"献祭";

	SetConsoleCursorPosition(hOut, {26, 14});
	cout<<"启动";

	return 0;
}

int Controller::FinalActivate(){
	//TODO必须给段帅气的动画
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//没有实际意义
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, {26, 14});
	cout<<"启动";
	
	//rgb(180,180,180)
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, {10, 8});
	cout<<"            			";

	//
	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            			";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"开始启动";
	
	Sleep(1000);
	//rgb(180,180,180)
	SetConsoleTextAttribute(hOut, 0x0007);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {19,8}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {23,8}, temp);

	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"仪表盘开启";
	Sleep(1000);

	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"开始投掷第一颗骰子";
	Sleep(1000);
	
	srand(time(NULL));
	int a = rand()%6 + 1;

	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"第一颗骰子结果为"<<a;

	SetConsoleTextAttribute(hOut, 0x0070);
	SetConsoleCursorPosition(hOut, {20, 8});
	cout<<a;
		
	Sleep(1000);


	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"开始投掷第二颗骰子";
	Sleep(1000);
	
	srand(time(NULL));
	int b = rand()%6 + 1;

	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	cout<<"第二颗骰子结果为"<<b;
	SetConsoleTextAttribute(hOut, 0x0070);
	SetConsoleCursorPosition(hOut, {24, 8});
	cout<<b;
	Sleep(1000);

	// rgb(0,128,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut, {10, 12});
	cout<<"            				";
	SetConsoleCursorPosition(hOut, {10, 12});
	for(int i=0; i<4; i++){
		cout<<'.';
		Sleep(300);
	}
	
	cout<<"最终结果为"<<a+b<<"，启动"<<( (a+b>=bag.activate_hard_level) ? "成功" : "失败");
	Sleep(3000);

	//判断是否成功启动
	if(a+b >= bag.activate_hard_level){//成功启动
		return 0;
	}
	else{//启动失败
		return 2;
	}
	return 1;
}

int Controller::EndGame(){
	Clear();
	//{14,11}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性

	
	SetConsoleCursorPosition(hOut, { 10, 11 });
	
	if(bag.win_or_lose==2){//失败
		cout<<"游戏失败";
		Sleep(444);
		cout<<"，你没能拯救世界";
	}
	else{//成功
		cout<<"引擎成功启动，你拯救了世界！";
	}

	Sleep(1000);
	

	
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"再来一局";
	SMALL_RECT back = {19, 17, 41, 17};
	SetConsoleCursorPosition(hOut, { back.Left, back.Top });

	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//设置输出文本属性
	cout<<"我学习通动了，我不玩了";
	SetConsoleTextAttribute(hOut, 0x0007);//设置输出文本属性

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//用来记录监控鼠标状态
	LPDWORD temp = new DWORD;//没有实际意义

	SMALL_RECT LastArea{ 0,0,-1,-1 };//之前鼠标所处的区域
	int color = 0x0007;

	while (1) {//一级循环
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//判断鼠标位置
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//注意Bottom和Top的大小关系
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//光标所处区域发生改变
				//改变按钮的发亮状态
				//原本位置变暗
				FillConsoleOutputAttribute(	hOut, color, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= back.Left && MousePos.X <= back.Right)
					&&
					(MousePos.Y <= back.Bottom && MousePos.Y >= back.Top)){
						//不玩了
						Rect = back;
						LastArea = back;
						color = FOREGROUND_RED;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//再来一局
						Rect = search_button;
						LastArea = search_button;
						color = 0x0007;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//新的位置变亮
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | color, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//按下左键
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//不玩了
				if(	LastArea.Left == back.Left 
					&& 
					LastArea.Right == back.Right){
					return 2;
				}
				else if(LastArea.Left == search_button.Left 
						&& 
						LastArea.Right == search_button.Right){
						// 再来一局
					return 0;
				}
				Sleep(500);
			}
		}
	}

	return 1;
}

int Controller::Init(){
	//Action();//开始界面的动画

	Clear();

	/************************************************
	 * Bag 初始化
 	************************************************/
	bag.tool_belt.dowing_rod = true;
	bag.tool_belt.paralysis_wand = true;
	//bag.tool_belt.focus_charm = true;
	for(int i=0; i<6; i++){
		bag.components_number[i] = 0;
		bag.treasure[i] = 0;
		bag.construct[i] = 0;
		bag.construct_state[i] = 0;
		//?下方0改为1，即可看见最终启动界面
		bag.link_state[i] = 0;
	}
	
	bag.activate_hard_level = 0;
	bag.gods_hand = 0;
	bag.HP = 6;
	bag.current_state = SELECT_AREA;
	bag.win_or_lose = 1;

	/************************************************
	 * TimeSystem 初始化
 	************************************************/
	time_system.day_now = 1;
	time_system.basic_time = 14;
	time_system.extra_time = 0;
	//time_system.event_cycle = 3;
	
	/************************************************
	 * Controller 初始化
 	************************************************/
	v = 0;
	
	/************************************************
	 * SearchArea 初始化
 	************************************************/
	search_area.InitAreaInfo();
	
	//DrawSelectArea();
	return 0;
}

int Controller::DayEnd(){
	time_system.day_now++;

	if(bag.treasure[Bag::BraceletOfLos]){//已获得雷神手镯
		//上帝之手+1
		bag.gods_hand++;
	}
	
	if(bag.treasure[Bag::ScaleOfTheInfinityWurm]){//已获得无限之秤
		//HP+1
		bag.HP = min(bag.HP + 1, 6);
	}

	if(time_system.day_now > time_system.basic_time + time_system.extra_time){
		//时间用尽
		bag.win_or_lose = 2;//游戏失败
	}
	return 0;
}



