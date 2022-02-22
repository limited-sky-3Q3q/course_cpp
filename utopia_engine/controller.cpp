/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\controller.cpp
 * Date: 2020-05-03 14:59:47
 * LastEditTime: 2020-05-30 11:55:18
 * !��������: ������bug
************************************************/
#include"controller.h"
#include<windows.h>
#include<iostream>
#include<time.h>
using namespace std;

/************************************************
//TODO ����Ĺ��ܣ�ʱ��ϵͳ��
//TODO ÿ��̽������������һ��
************************************************/
int Controller::BeginGame(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	//���ع��
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    //cout<<cursorInfo.bVisible<<"\n";
    cout<<SetConsoleCursorInfo(hOut, &cursorInfo);
    cout<<"���س�";
	getchar();
	
	
	SetConsoleTextAttribute(hOut, 0x0007);

	//���ô��ڴ�С
	cout<<SetConsoleScreenBufferSize(hOut, windows_size);
	SMALL_RECT rect = { 0, 0, 45 - 1, 20 - 1 };
	cout<<SetConsoleWindowInfo(hOut, true, &windows_rect);
	
	
	//����
	cout<<"���س�";
	getchar();
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	//int LastAttribute{ 0 };//�ϴε��ı�����
	
	

	while (1) {//һ��ѭ��

		//Init();//��Ϸ���ݳ�ʼ��
		//Action();//��ʼ����Ķ���

		Clear();
		
		bag.current_state = SELECT_AREA;
		DrawSelectArea();
		

		while (1) {//����ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			
			//ѡ����棺������ð�գ�������ʱ��
			if (record.EventType == MOUSE_EVENT) {
				//���Ժ���
				/*
				SetConsoleCursorPosition(hOut, {0,0});
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				cout<<MousePos.X<<" "<<MousePos.Y<<" ";
				*/
				
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				//!��ջ�Ľṹ���л�����

				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//!ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					if(	(MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
						&&
						(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
							//�����ڱ�����ť��
							Rect = bag_position;
							LastArea = bag_position;
						}
					else if((MousePos.X >= select_search_area.Left && MousePos.X <= select_search_area.Right)
							&&
							(MousePos.Y <= select_search_area.Bottom && MousePos.Y >= select_search_area.Top)){
							//������̽����ť��
							Rect = select_search_area;
							LastArea = select_search_area;
						}
					else if((MousePos.X >= select_workshop_area.Left && MousePos.X <= select_workshop_area.Right)
							&&
							(MousePos.Y <= select_workshop_area.Bottom && MousePos.Y >= select_workshop_area.Top)){
							//�����ڹ�����ť��
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
						
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);

				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//����ѡ��,�ı�����
					if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
						//���뱳������
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
						//����̽������
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
						//���빤������
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
						//!���������������棡
						Clear();
						bag.last_state = SELECT_AREA;
						bag.current_state = FINAL_ACTIVATE_AREA;
						IntoWarn();//����������������
						bag.last_state = FINAL_ACTIVATE_AREA;
						bag.current_state = SELECT_AREA;
						
						
						//Clear();
						
						//������Ϸ����
						//չʾ���ս��棬�ͷ���
						if(bag.win_or_lose == 1){
							Clear();
							DrawSelectArea();
							Sleep(500);
							continue;
						}
							
						if(EndGame() == 2){//�˳���Ϸ
							return 0;
						}
						else{//����һ��
							Init();
							continue;
						}

					}
					
					if(bag.win_or_lose == 2){
						if(EndGame() == 2){//�˳���Ϸ
							return 0;
						}
						else{//����һ��
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
	cout << "����������������������������������������������";
	for (SHORT i = 1; i <= 4; i++) {
		SetConsoleCursorPosition(hOut, { 0, i });
		cout << "��";
		SetConsoleCursorPosition(hOut, { 44, i });
		cout << "��";
	}
	SetConsoleCursorPosition(hOut, { 0, 5 });
	cout << "����������������������������������������������";
	SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
	cout << "����  HP��" << bag.HP;
	SetConsoleCursorPosition(hOut, { 23, 1 });
	cout << "ʱ��  �ϵ�֮�֣�" << bag.gods_hand;

	//ǰ���бض�����
	//TODO��ɫ��δ����
	int len=0;
	
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RGB(128,0,0)
	for(int i=1; i < time_system.day_now; i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ��";
	}

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//RGB(0,255,0)
	SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
	len++;
	cout<<" ��";

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);//RGB(0,128,0)
	for(int i=1; i<=(14 - time_system.day_now); i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ��";
	}

	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);//RGB(128,128,0)
	for(int i=1; i <= min(21-time_system.day_now - 7 + time_system.extra_time ,time_system.extra_time); i++){
		SetConsoleCursorPosition(hOut, { 3*((len)%7)+22, len/7+2 });
		len++;
		cout<<" ��";
	}
	/*
	SetConsoleCursorPosition(hOut, { 23, 2 });
	cout << "�� �� �� �� �� �� ��";
	SetConsoleCursorPosition(hOut, { 23, 3 });
	cout << "�� �� �� �� �� �� ��";

	SetConsoleCursorPosition(hOut, { 22, 4 });
	for (int i = 0; i < time_system.extra_time; i++)
		cout << " ��";
	*/

	SetConsoleTextAttribute(hOut, 0x0007);
	string now_area = "";
	switch (bag.current_state) {
	case INTRODUCE_BACKGROUND:
		now_area.clear(); break;
	case ACTION:
		now_area.clear(); break;
	case SELECT_AREA:
		now_area = "ѡ����"; break;
	case OPEN_BAG:
		now_area = "�򿪱���"; break;
	case ARTIFACT_WORKSHOP:
		now_area = "��������"; break;
	case ACTIVATE_AREA:
		now_area = "��������"; break;
	case ACTIVATE:
		now_area = "��������"; break;
	case LINK_AREA:
		now_area = "��������"; break;
	case LINK:
		now_area = "��������"; break;
	case FINAL_ACTIVATE_AREA:
		now_area = "����װ�������ӣ�"; break;
	case FINAL_ACTIVATE:
		now_area = "�������ӣ�"; break;
	case SEARCH_AREA_INTERFACE:
		now_area = "̽������"; break;
	case SEARCH_AREA:
		switch (search_area.current_search_area) {
		case SearchArea::HaleBeardPeak:
			now_area = "����Ⱥ��"; break;
		case SearchArea::TheGreatWild:
			now_area = "ç�Ի�ԭ"; break;
		case SearchArea::RootStrangledMarshes:
			now_area = "�������"; break;
		case SearchArea::GrassRockCanyon:
			now_area = "����Ͽ��"; break;
		case SearchArea::RuinedCityOfTheAncients:
			now_area = "Զ����ַ"; break;
		case SearchArea::TheFireMaw:
			now_area = "���涴Ѩ"; break;
		default:
			now_area.clear(); break;
		}
		break;
	case SEARCH:
		now_area = "��������"; break;
	case BATTLE:
		now_area = "����ս��"; break;
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
	cout << "̽��";
	SetConsoleCursorPosition(hOut, COORD{ select_workshop_area.Left, select_workshop_area.Top });
	cout << "����";

	int v=0;
	for(int i=0; i<6; i++)
		v += bag.link_state[i];
	if(v==6){
		SetConsoleCursorPosition(hOut, COORD{final_activate_area.Left, final_activate_area.Top});
		cout <<"��������!";
	}
	return 0;
}

int Controller::IntoBag(){
	Clear();
	DrawInformationBar();
	DrawBag();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������
	
	SMALL_RECT TheAncientRecordArea{30, 13, 37, 13};//Զ�ż��µ�����
	SMALL_RECT gods_hand_area{32, 15, 43, 15};//ʹ���ϵ�֮������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= TheAncientRecordArea.Left && MousePos.X <= TheAncientRecordArea.Right)
						&&
						(MousePos.Y <= TheAncientRecordArea.Bottom && MousePos.Y >= TheAncientRecordArea.Top)
						&&
						bag.treasure[Bag::TheAncientRecord]==1){
						//Զ�ż���
						Rect = TheAncientRecordArea;
						LastArea = TheAncientRecordArea;
					}
				else if((MousePos.X >= gods_hand_area.Left && MousePos.X <= gods_hand_area.Right)
						&&
						(MousePos.Y <= gods_hand_area.Bottom && MousePos.Y >= gods_hand_area.Top)
						&&
						bag.gods_hand >= 3){
						//�ϵ�֮��
						Rect = gods_hand_area;
						LastArea = gods_hand_area;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right
					&&
					LastArea.Bottom == bag_back_position.Bottom){
					Clear();
					
					//���⸳ֵ
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
					IntoAncientRecord();//����ʹ��Զ�ż��µ�����
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
						&&//ʹ���ϵ�֮��
						bag.gods_hand >= 3){
					bag.gods_hand -= 3;
					time_system.extra_time = min(time_system.extra_time + 1, 7);
					DrawInformationBar();
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:�쳣����
}

int Controller::DrawBag(){
	
	/************************************************
  enum { Silver��, QuartzʯӢ, Gum��, Silica����, Wax��, LeadǦ };//�����
	int components_number[6]{0,0,0,0,0,0};//�������
 ************************************************/
	//6���������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { 2, 7 });//ͳһ���
	cout<<" �������";
	SetConsoleCursorPosition(hOut, { 2, 8 });
	cout<<"ʯӢ:"<<bag.components_number[Bag::Quartz]<<" ��:"<<bag.components_number[Bag::Silver];
	SetConsoleCursorPosition(hOut, { 2, 9 });
	cout<<"��:"<<bag.components_number[Bag::Gum]<<" ��:"<<bag.components_number[Bag::Wax];
	SetConsoleCursorPosition(hOut, { 2, 10 });
	cout<<"����:"<<bag.components_number[Bag::Silica]<<" Ǧ:"<<bag.components_number[Bag::Lead];
	
	//��������
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 7 });
	cout<<"     װ��";
	SetConsoleCursorPosition(hOut, { 14, 8 });
	cout<<"̽��Ȩ��:";
	if(bag.tool_belt.dowing_rod){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѳ���";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ����";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 9 });
	cout<<"���ħ��:";
	if(bag.tool_belt.paralysis_wand){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѳ���";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ����";
	}
	
	/*
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 14, 10 });
	cout<<"�۽�����:";
	if(bag.tool_belt.focus_charm){
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѳ���";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ����";
	}
	*/

	//�����ؼ� �������� ҹ��� ����֮�� ������Ƭ Զ�ż���
	//enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
	//	   ScaleOfTheInfinityWurm, TheMoltenSharo, TheAncientRecord};//������
	//6������

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 7 });//ͳһ���
	cout<<"   ����";
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 8 });
	cout<<"�����ؼ�:";
	if(bag.treasure[Bag::IcePlate]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 9 });
	cout<<"��������:";
	if(bag.treasure[Bag::BraceletOfLos]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 10 });
	cout<<"ҹ��ӫ˿:";
	if(bag.treasure[Bag::ShimmeringMoonlace]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 11 });
	cout<<"����֮��:";
	if(bag.treasure[Bag::ScaleOfTheInfinityWurm]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 12 });
	cout<<"������Ƭ:";
		if(bag.treasure[Bag::TheMoltenSharo]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 30, 13 });
	cout<<"Զ�ż���:";
		if(bag.treasure[Bag::TheAncientRecord]){//�ѻ��
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<"�ѻ��";
	}
	else{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 32, 15 });
	cout<<"ʹ���ϵ�֮��";

	//�������
	//ˮ����� �ƽ����� ռ��͸�� ����֮�� ƽ���ӡ ���֮��
	//enum { CrystalBattery, GoldenChassis, ScryingLens,
	//	   HermeticMirror, SealOfBalance, VoidGate};//װ����
	//bool construct[6]{0,0,0,0,0,0};//װ�û�����
	//?��
	/************************************************
	 ˮ����� �ƽ�����
	 ����֮�� ƽ���ӡ
	 ����֮�� ���֮��
	 ƽ���ӡ �ƽ�����
	 ռ��͸�� ƽ���ӡ
	 �ƽ����� ���֮��
 ************************************************/
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 12 });//ͳһ���
	cout<<"      ����װ��";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 13 });
	cout<<"Ǧ:   ";
	if(bag.construct[Bag::CrystalBattery]){//�ѻ��
		if(bag.construct_state[Bag::CrystalBattery]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ˮ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 14 });
	cout<<"����: ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 15 });
	cout<<"��:   ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 16 });
	cout<<"ʯӢ: ";
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 17 });
	cout<<"��:   ";
	if(bag.construct[Bag::ScryingLens]){//�ѻ��
		if(bag.construct_state[Bag::ScryingLens]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ռ��͸��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 2, 18 });
	cout<<"��: ";
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";
	
	//���ذ�ť
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";

	return 0;
}

int Controller::IntoAncientRecord(){//����ʹ��Զ�ż��µ�����
	Clear();
	DrawInformationBar();
	DrawAncientRecord();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT button_pos[6];
	button_pos[0] = {23, 8, 24, 8};
	button_pos[1] = {23, 10, 24, 10};
	button_pos[2] = {23, 12, 24, 12};
	button_pos[3] = {23, 14, 24, 14};
	button_pos[4] = {23, 16, 24, 16};
	button_pos[5] = {23, 18, 24, 18};
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT){
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				//���Ӱ�ť
				else if((MousePos.X >= button_pos[0].Left && MousePos.X <= button_pos[0].Right)
						&&
						(MousePos.Y <= button_pos[0].Bottom && MousePos.Y >= button_pos[0].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//δ����
						!bag.link_state[0]
						&&//��Ǧ
						(bag.components_number[Bag::Lead]>0)){
						Rect = button_pos[0];
						LastArea = button_pos[0];
					}
				else if((MousePos.X >= button_pos[1].Left && MousePos.X <= button_pos[1].Right)
						&&
						(MousePos.Y <= button_pos[1].Bottom && MousePos.Y >= button_pos[1].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//δ����
						!bag.link_state[1]
						&&//�й���
						(bag.components_number[Bag::Silica]>0)){
						Rect = button_pos[1];
						LastArea = button_pos[1];
					}
				else if((MousePos.X >= button_pos[2].Left && MousePos.X <= button_pos[2].Right)
						&&
						(MousePos.Y <= button_pos[2].Bottom && MousePos.Y >= button_pos[2].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//δ����
						!bag.link_state[2]
						&&//����
						(bag.components_number[Bag::Wax]>0)){
						Rect = button_pos[2];
						LastArea = button_pos[2];
					}
				else if((MousePos.X >= button_pos[3].Left && MousePos.X <= button_pos[3].Right)
						&&
						(MousePos.Y <= button_pos[3].Bottom && MousePos.Y >= button_pos[3].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//δ����
						!bag.link_state[3]
						&&//��ʯӢ
						(bag.components_number[Bag::Quartz]>0)){
						Rect = button_pos[3];
						LastArea = button_pos[3];
					}
				else if((MousePos.X >= button_pos[4].Left && MousePos.X <= button_pos[4].Right)
						&&
						(MousePos.Y <= button_pos[4].Bottom && MousePos.Y >= button_pos[4].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//δ����
						!bag.link_state[4]
						&&//����
						(bag.components_number[Bag::Silver]>0)){
						Rect = button_pos[4];
						LastArea = button_pos[4];
					}
				else if((MousePos.X >= button_pos[5].Left && MousePos.X <= button_pos[5].Right)
						&&
						(MousePos.Y <= button_pos[5].Bottom && MousePos.Y >= button_pos[5].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//δ����
						!bag.link_state[5]
						&&//����
						(bag.components_number[Bag::Gum]>0)){
						Rect = button_pos[5];
						LastArea = button_pos[5];
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					
					bag.last_state = LINK_AREA;
					return 0;
				}
				//���Ӱ�ť
				else if(LastArea.Left == button_pos[0].Left
						&&
						LastArea.Right == button_pos[0].Right
						&&
						LastArea.Bottom == button_pos[0].Bottom
						&&
						LastArea.Top == button_pos[0].Top
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
	return 1;//1:�쳣����










}

int Controller::DrawAncientRecord(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 7 });//ͳһ���
	cout<<"      ʹ��Զ�ż���";

	//SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"Ǧ:   ";
	if(bag.construct[Bag::CrystalBattery]){//�ѻ��
		if(bag.construct_state[Bag::CrystalBattery]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ˮ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"����: ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"��:   ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"ʯӢ: ";
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"��:   ";
	if(bag.construct[Bag::ScryingLens]){//�ѻ��
		if(bag.construct_state[Bag::ScryingLens]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ռ��͸��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"��: ";
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";
	
	//���ذ�ť
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";
	
	return 0;


}

int Controller::IntoSearchArea(){
	Clear();
	DrawInformationBar();
	DrawSearchArea();

	//��ťЧ��
	//6�������İ�ť�ͷ��ذ�ť
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������

	SMALL_RECT area[6];
	area[SearchArea::HaleBeardPeak]={8, 7, 15, 7};
	area[SearchArea::TheGreatWild]={22, 7, 29, 7,};
	area[SearchArea::RootStrangledMarshes]={36, 7, 43,7};
	area[SearchArea::GrassRockCanyon]={8, 12, 15, 12};
	area[SearchArea::RuinedCityOfTheAncients]={22, 12, 29, 12};
	area[SearchArea::TheFireMaw]={36, 12, 43,12};
	
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						// ������ť
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
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				//��bag_back_position������һ��
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					bag.last_state = SEARCH_AREA_INTERFACE;
					return 0;
				}
				//�򿪱���
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

				//ѡ��̽������
				
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
	return 1;//1:�쳣����
}

int Controller::DrawSearchArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { 2, 7 });//ͳһ���
	cout<<"      ����Ⱥ��      ç�Ի�ԭ      �������";
	SetConsoleCursorPosition(hOut, { 2, 8 });
	cout<<"װ��: ƽ���ӡ      ����֮��      ���֮��";
	SetConsoleCursorPosition(hOut, { 2, 9 });
	cout<<"���: ��            ʯӢ          ��";
	SetConsoleCursorPosition(hOut, { 2, 10 });
	cout<<"����: �����ؼ�      ��������      ҹ��ӫ˿";

	SetConsoleCursorPosition(hOut, { 2, 12 });//ͳһ���
	cout<<"      ����Ͽ��      Զ����ַ      ����ɽ��";
	SetConsoleCursorPosition(hOut, { 2, 13 });
	cout<<"װ��: �ƽ�����      ռ��͸��      ˮ�����";
	SetConsoleCursorPosition(hOut, { 2, 14 });
	cout<<"���: ����          ��            Ǧ";
	SetConsoleCursorPosition(hOut, { 2, 15 });
	cout<<"����: ����֮��      Զ�ż���      ������Ƭ";

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";
	return 0;
}

int Controller::IntoSelectedSearchArea(int chose_area){
	search_area.current_search_area = chose_area;
	Clear();
	DrawInformationBar();
	DrawSelectedSearchArea();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//������ť
						Rect = bag_position;
						LastArea = bag_position;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//��ʼ������ť
						Rect = search_button;
						LastArea = search_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
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
					// ����
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
					//��������
					//!���������Ļ
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
					cout<<"��������";
				}

				if(bag.win_or_lose == 2){
					return 0;
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:�쳣����
}

int Controller::DrawSelectedSearchArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"��ʼ����";
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"����";
	
	return 0;
}

int Controller::BeginSearch(){
	//!���������Ļ
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������


	//��������ı�����
	SetConsoleTextAttribute(hOut, 0x0070);
	
	DrawSearch();
	//Ͷ��3��2������
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
	//ѭ��3��
	for(int i=0; i<3; i++){
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		

		while (1) {//һ��ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//6����ť
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
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//�����
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
	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
	cout<<" ̽�����Ϊ"<<result;
	
	if(bag.tool_belt.dowing_rod){//̽��Ȩ���ѳ���
		SetConsoleCursorPosition(hOut, { 10, 15 });
		cout<<"�Ƿ�ʹ��̽��Ȩ�� �� ��";//27 30
		
		SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
		LastArea={ 0,0,-1,-1 };//��ʼ������
		while (1) {//һ��ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//2����ť
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
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					
					if(	LastArea.Left == yes.Left 
						&& 
						LastArea.Right == yes.Right
						&&
                        LastArea.Bottom == yes.Bottom){
						//ʹ��̽��Ȩ��
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
						//��ʹ��
						
						break;
					}
				
					Sleep(500);
				}
			}
		}
		
	}


	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
	SetConsoleCursorPosition(hOut, { 10, 15 });
	cout<<"                         ";
	SetConsoleCursorPosition(hOut, { 16, 14 });
	cout<<"               ";
	SetConsoleCursorPosition(hOut, {16, 14});
	cout<<" ̽�����Ϊ"<<result;

	SetConsoleCursorPosition(hOut, {14, 15});
	//������˻���
	
	if(result == 0){
		SetConsoleCursorPosition(hOut, {10, 15});
		cout<<"����̽��������ѳ��ܵ�װ��"<<search_area.area[search_area.current_search_area].construct_name;
		
		bag.construct[search_area.current_search_area]=true;
		bag.construct_state[search_area.current_search_area]=true;
		
		SetConsoleCursorPosition(hOut, {14, 16});
		cout<<"�ϵ�֮������5��";
		bag.gods_hand += 5;
		Sleep(3000);
	}
	else if(result > 0 && result <= 10){//����װ��
		cout<<"����װ�� "<<search_area.area[search_area.current_search_area].construct_name;
		bag.construct[search_area.current_search_area]=true;
		Sleep(3000);
	}
	else if(result > 10 && result <= 100){
		//�������
		SetConsoleCursorPosition(hOut, {16, 15});
		cout<<"������� "<<search_area.area[search_area.current_search_area].component_name;
		bag.components_number[search_area.current_search_area]++;
		Sleep(3000);
	}
	//��������
	else{
		
		//ӫ��ܳ
		bool flag =false;
		if(bag.treasure[Bag::ShimmeringMoonlace]){//ҹ��ӫ˿�ѻ��
			SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
			SetConsoleCursorPosition(hOut, { 10, 15 });
			cout<<"�Ƿ�ʹ��ҹ��ӫ˿ �� ��";//27 30
			Sleep(500);
			SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
			LastArea={ 0,0,-1,-1 };//��ʼ������
			while (1) {//һ��ѭ��
				ReadConsoleInput(hIn, &record, 1, temp);
				if (record.EventType == MOUSE_EVENT) {
					//cout<<"k";
					COORD MousePos = record.Event.MouseEvent.dwMousePosition;
					//�ж����λ��
					if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
						||//ע��Bottom��Top�Ĵ�С��ϵ
						(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
						) {//��������������ı�
						//�ı䰴ť�ķ���״̬
						//ԭ��λ�ñ䰵
						FillConsoleOutputAttribute(	hOut, 0x0007, 
													LastArea.Right - LastArea.Left + 1, 
													COORD{LastArea.Left, LastArea.Top}, temp);

						SMALL_RECT Rect;
						//2����ť
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
						//�µ�λ�ñ���
						FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
					}
					
					//�������
					if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
						if(LastArea.Right == -1 && LastArea.Bottom == -1)
							continue;
						
						
						if(	LastArea.Left == yes.Left 
							&& 
							LastArea.Right == yes.Right
							&&
							LastArea.Bottom == yes.Bottom){
							//ʹ��ҹ��ӫ˿
							flag = true;
							break;
						}
						else if(LastArea.Left == no.Left 
							&& 
							LastArea.Right == no.Right
							&&
							LastArea.Bottom == no.Bottom){
							//��ʹ��
							flag = false;
							break;
						}
					
						Sleep(500);
					}
				}
			}
		}

		if(flag)//��������
			{}
		else{//����������
			int level=1;

			SetConsoleCursorPosition(hOut, {10, 15});
			cout<<"                                                     ";
			SetConsoleCursorPosition(hOut, {14, 15});
			cout<<"�������� ";
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
			//��ʼս��
			Battle(level);
		}
	}
	
	DayEnd();//����һ��
	
	return 0;
}

int Controller::Battle(int level){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������

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

	if(bag.tool_belt.paralysis_wand){//̽��Ȩ���ѳ���
		SetConsoleCursorPosition(hOut, { 10, 15 });
		cout<<"�Ƿ�ʹ�����ħ�� �� ��";//27 30
		
		SMALL_RECT yes{27,15, 28, 15}, no{30, 15, 31,15};
		LastArea={ 0,0,-1,-1 };//��ʼ������
		while (1) {//һ��ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                //cout<<"k";
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//2����ť
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
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO |0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					
					if(	LastArea.Left == yes.Left 
						&& 
						LastArea.Right == yes.Right
						&&
                        LastArea.Bottom == yes.Bottom){
						//ʹ�����ħ��
						
						use_paralysis_wand = true;
						bag.tool_belt.dowing_rod = false;
						
						break;
					}
					else if(LastArea.Left == no.Left 
						&& 
						LastArea.Right == no.Right
						&&
                        LastArea.Bottom == no.Bottom){
						//��ʹ��
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
	
	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"����";//ֻ��һ����ť
	
	srand(time(NULL));

	bool defeat = false;//�Ƿ��ܵ���

	while(1){// ս��ѭ��
		
		//������

		int a,b;
		if(use_paralysis_wand){
			a = min((rand()%6 + 1 + 2), 6);
			b = min((rand()%6 + 1 + 2), 6);
		}
		else{
			a = rand()%6 + 1;
			b = rand()%6 + 1;
		}
		//չʾ����
		//*********************************************************************
		//*��Ҫ�����ɫģ��
		SetConsoleTextAttribute(hOut, 0x0070);//��������ı�����

		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		//*********************************************************************
		SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
		//�ж�
		//if(	search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1
		//	||//����
		//	search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1){
		
		//ÿ�ζ����
			SetConsoleCursorPosition(hOut, {17, 10});
			cout<<"�ܵ�"
				<<	((search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1)
					+
					(search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1))
				<<"���˺�";

			bag.HP -= ((search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==-1)
					  +
					  (search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==-1));
		//}

		//TODO ����Ѫ��
		SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
		cout << "����  HP��" << bag.HP;

		if(search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[a-1]==1
			||//�򵹵���
			search_area.area[search_area.current_search_area].enemy[level-1].attack_and_hit[b-1]==1){
			SetConsoleCursorPosition(hOut, {14, 11});
			cout<<"�ɹ����� "<<search_area.area[search_area.current_search_area].enemy[level-1].name;
			defeat = true;
			break;
		}
		//Sleep(2000);
		if(bag.HP <= 0)//������
			break;
		
		//���ţ�����

		//��ť
		while (1) {//һ��ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0007, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
						&&
						(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
							//�����ڷ��ذ�ť��
							Rect = bag_back_position;
							LastArea = bag_back_position;
						}
					else{
						LastArea = {0, 0, -1, -1};
						continue;
					}
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//�˳�����
					if(	LastArea.Left == bag_back_position.Left 
						&& 
						LastArea.Right == bag_back_position.Right){
						break;//����������
					}
				}
			}
		}
	}

	Sleep(2000);

	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
	
	SetConsoleCursorPosition(hOut, {11, 10});
	cout<<"                                 ";
	SetConsoleCursorPosition(hOut, {11, 12});
	cout<<"                                 ";
	//����ж�
	SetConsoleCursorPosition(hOut, {14, 12});
	if(defeat && bag.HP){//��ܵ����һ���
		cout<<"���";
		if(level == 5){//��ñ���
			cout<<"���� "<<search_area.area[search_area.current_search_area].treasure_name;
			if(search_area.current_search_area != Bag::TheAncientRecord)//���Զ�ż�������ı���
				bag.treasure[search_area.current_search_area] = true;
			else{//���Զ�ż���
				if(bag.treasure[search_area.current_search_area] !=2)//Զ�ż���δʹ�ù�
					bag.treasure[search_area.current_search_area] = 1;
				else//Զ�ż�����ʹ�ù�
					bag.treasure[search_area.current_search_area] = 2;
			}
				
					
			if(search_area.current_search_area == Bag::IcePlate){
				if(bag.treasure[Bag::TheMoltenSharo])//�����������
					search_area.GetIcePlateAndTheMoltenSharo();
				else//ֻ��һ��
					search_area.GetIcePlate();
			}
			else if(search_area.current_search_area == Bag::TheMoltenSharo){
				if(bag.treasure[Bag::IcePlate])//�����������
					search_area.GetIcePlateAndTheMoltenSharo();
				else//ֻ��һ��
					search_area.GetTheMoltenSharo();
			}
		}
		else{//������
			cout<<"��� "<<search_area.area[search_area.current_search_area].component_name;
			bag.components_number[search_area.current_search_area]++;
		}
	}
	else if(defeat){//��ܵ���������
		cout<<"���";
		if(level == 5){//��ñ���
			cout<<"���� "<<search_area.area[search_area.current_search_area].treasure_name;
			bag.treasure[search_area.current_search_area] = true;
			
		}
		else{//������
			cout<<"��� "<<search_area.area[search_area.current_search_area].component_name;
			bag.components_number[search_area.current_search_area]++;
		}
		
		SetConsoleCursorPosition(hOut, {17, 13});
		cout<<" �������";
		//��������5��
		for(int i=0; i<6; i++)
			DayEnd();
		bag.HP = 6;//Ѫ������
		//time_system.day_now += 6;
	}
	else{//����
		SetConsoleCursorPosition(hOut, {18, 12});
		cout<<" ս��ʧ��";
		
		//��������5��
		for(int i=0; i<6; i++)
			DayEnd();
		bag.HP = 6;//Ѫ������
		//time_system.day_now += 6;
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"����";
	
	//��ť
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					bag.current_state = BATTLE;
					return 0;//����
				}
			}
		}
	}
	
	return 1;//�쳣�˳�
}

int Controller::DrawSearch(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//û��ʵ������
	//��ɫ�ӽ���
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
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//!ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//�����ڱ�����ť��
						Rect = bag_position;
						LastArea = bag_position;
					}
				else if((MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
						&&
						(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//����
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= activate_area_button.Left && MousePos.X <= activate_area_button.Right)
						&&
						(MousePos.Y <= activate_area_button.Bottom && MousePos.Y >= activate_area_button.Top)){
						//����װ�ð�ť
						Rect = activate_area_button;
						LastArea = activate_area_button;
					}
				else if((MousePos.X >= link_area_button.Left && MousePos.X <= link_area_button.Right)
						&&
						(MousePos.Y <= link_area_button.Bottom && MousePos.Y >= link_area_button.Top)){
						//��������ť
						Rect = link_area_button;
						LastArea = link_area_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
					
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//����ѡ��,�ı�����
				if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
					//���뱳������
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
						//��������װ�ý���
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
						//���������������
						bag.last_state = ARTIFACT_WORKSHOP;
						bag.current_state = LINK_AREA;
						IntoLinkArea();
						
						bag.last_state = LINK_AREA;
						bag.current_state = ARTIFACT_WORKSHOP;
						
						Clear();
						DrawWorkshop();
				}
				else if(LastArea.Left == bag_back_position.Left && LastArea.Right == bag_back_position.Right){
					//����
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
	
	return 1;//�쳣�˳�
}

int Controller::DrawWorkshop(){
	DrawInformationBar();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hOut, COORD{ activate_area_button.Left, activate_area_button.Top });
	cout << "����װ��";
	SetConsoleCursorPosition(hOut, COORD{ link_area_button.Left, link_area_button.Top });
	cout << "��������";

	//���ذ�ť
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";

	return 0;
}

int Controller::IntoActivateArea(){
	Clear();
	DrawInformationBar();
	DrawActivateArea();

	//��ťЧ��
	//6��װ�õİ�ť�ͷ��ذ�ť
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������

	SMALL_RECT area[6];
	area[Bag::SealOfBalance]={6, 9, 13, 9};//+7
	area[Bag::HermeticMirror]={24, 9, 31, 9,};
	area[Bag::VoidGate]={6, 11, 13, 11};
	area[Bag::GoldenChassis]={24, 11, 31, 11,};
	area[Bag::ScryingLens]={6, 13, 13, 13};
	area[Bag::CrystalBattery]={24, 13, 31, 13,};
	
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((	MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//�����ڱ�����ť��
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
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				//��bag_back_position������һ��
				if(	LastArea.Left == bag_back_position.Left 
					&& //����
					LastArea.Right == bag_back_position.Right){
					//Sleep(1000);
					Clear();
					bag.last_state = ACTIVATE_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left 
						&& 
						LastArea.Right == bag_position.Right){
						// ����
						bag.current_state = OPEN_BAG;
						bag.last_state = ACTIVATE_AREA;
						Clear();
						IntoBag();
						bag.current_state = ACTIVATE_AREA;
						bag.last_state = OPEN_BAG;
				}

				//ѡ������װ��
				else if(LastArea.Left == area[Bag::SealOfBalance].Left
						&&
						LastArea.Right == area[Bag::SealOfBalance].Right
						&&
						LastArea.Bottom == area[Bag::SealOfBalance].Bottom
						&&// �ѻ��װ��
						bag.construct[Bag::SealOfBalance]
						&&//δ����
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
						&&// �ѻ��װ��
						bag.construct[Bag::HermeticMirror]
						&&//δ����
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
						&&// �ѻ��װ��
						bag.construct[Bag::VoidGate]
						&&//δ����
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
						&&// �ѻ��װ��
						bag.construct[Bag::GoldenChassis]
						&&//δ����
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
						&&// �ѻ��װ��
						bag.construct[Bag::ScryingLens]
						&&//δ����
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
						&&// �ѻ��װ��
						bag.construct[Bag::CrystalBattery]
						&&//δ����
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
	return 1;//1:�쳣����
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
	SetConsoleCursorPosition(hOut, { area[Bag::SealOfBalance].Left, area[Bag::SealOfBalance].Top });//ͳһ���
	cout<<"ƽ���ӡ:";
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}
		
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::HermeticMirror].Left, area[Bag::HermeticMirror].Top });
	cout<<"����֮��:";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::VoidGate].Left, area[Bag::VoidGate].Top });//ͳһ���
	cout<<"���֮��:";
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::GoldenChassis].Left, area[Bag::GoldenChassis].Top });
	cout<<"�ƽ�����:";
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::ScryingLens].Left, area[Bag::ScryingLens].Top });//ͳһ���
	cout<<"ռ��͸��:";
	if(bag.construct[Bag::ScryingLens]){//�ѻ��
		if(bag.construct_state[Bag::ScryingLens]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { area[Bag::CrystalBattery].Left, area[Bag::CrystalBattery].Top });
	cout<<"ˮ�����:";
	if(bag.construct[Bag::CrystalBattery]){//�ѻ��
		if(bag.construct_state[Bag::CrystalBattery]){//�ѳ���
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout<<"�ѳ���";
		}
		else{//δ����
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"δ����";
		}
	}
	else{
		SetConsoleTextAttribute(hOut, 0x0007);
		cout<<"δ���";
	}
	
	//���ذ�ť
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";
	return 0;
}

int Controller::IntoActivate(int chose_construct){
	Clear();
	DrawInformationBar();
	DrawActivate(chose_construct);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������

	SetConsoleTextAttribute(hOut, 0x0070);//��������ı�����

	
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
	//ѭ����Σ����������
	for(int i=0; i<3; i++){//һ��ѭ��
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		
		//������
		while (1) {//����ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//7����ť
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
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//�����
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
	
	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����

	
	a = board[0] - board[3];
	if(a<0){
		cout<<"1�����Ӷ�·������1����ֵ";
		bag.HP--;
	}
	else{
		cout<<"1�����ӳɹ�";
	}

	SetConsoleCursorPosition(hOut, {17, 15});
	a = board[1] - board[4];
	if(a<0){
		cout<<"2�����Ӷ�·������1����ֵ";
		bag.HP--;
	}
	else{
		cout<<"2�����ӳɹ�";
	}
	
	SetConsoleCursorPosition(hOut, {17, 16});
	a = board[2] - board[5];
	if(a<0){
		cout<<"3�����Ӷ�·������1����ֵ";
		bag.HP--;
	}
	else{
		cout<<"3�����ӳɹ�";
	}
	
	SetConsoleCursorPosition(hOut, COORD{ bag_position.Left, bag_position.Top });
	cout << "����  HP��" << bag.HP<<" ";

	bag.construct_state[chose_construct] = true;

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";

	LastArea = {0, 0, -1, -1};
	//���ذ�ť
	while (1) {//����ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)) {
				//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				//���ذ�ť
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

				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, 0x0070, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//����
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
	LPDWORD temp = new DWORD;//û��ʵ������

	SetConsoleTextAttribute(hOut, 0x0007);
	// SetConsoleCursorPosition(hOut, {2, 7});
	// cout<<"��ǰ����ֵ:"<<bag.construct_state[chose_construct];
	//��ɫ�ӽ���
	// SetConsoleTextAttribute(hOut, 0x0070);

	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {19,8}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {23,8}, temp);
    
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,10}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {17,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {21,12}, temp);
	FillConsoleOutputAttribute(	hOut, 0x0070, 3, {25,12}, temp);
	
	//����Ͱ��ť
	//SetConsoleCursorPosition(hOut, { 36, 17 });
	//cout<<"����";
	
	return 0;
}

int Controller::IntoLinkArea(){
	Clear();
	DrawInformationBar();
	DrawLinkArea();
	
	//TODO
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT button_pos[6];
	button_pos[0] = {23, 8, 24, 8};
	button_pos[1] = {23, 10, 24, 10};
	button_pos[2] = {23, 12, 24, 12};
	button_pos[3] = {23, 14, 24, 14};
	button_pos[4] = {23, 16, 24, 16};
	button_pos[5] = {23, 18, 24, 18};
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
						&&
						(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
							//�����ڱ�����ť��
							Rect = bag_position;
							LastArea = bag_position;
						}
				//���Ӱ�ť
				else if((MousePos.X >= button_pos[0].Left && MousePos.X <= button_pos[0].Right)
						&&
						(MousePos.Y <= button_pos[0].Bottom && MousePos.Y >= button_pos[0].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::CrystalBattery]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//δ����
						!bag.link_state[0]
						&&//��Ǧ
						(bag.components_number[Bag::Lead]>0)){
						Rect = button_pos[0];
						LastArea = button_pos[0];
					}
				else if((MousePos.X >= button_pos[1].Left && MousePos.X <= button_pos[1].Right)
						&&
						(MousePos.Y <= button_pos[1].Bottom && MousePos.Y >= button_pos[1].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//δ����
						!bag.link_state[1]
						&&//�й���
						(bag.components_number[Bag::Silica]>0)){
						Rect = button_pos[1];
						LastArea = button_pos[1];
					}
				else if((MousePos.X >= button_pos[2].Left && MousePos.X <= button_pos[2].Right)
						&&
						(MousePos.Y <= button_pos[2].Bottom && MousePos.Y >= button_pos[2].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::HermeticMirror]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//δ����
						!bag.link_state[2]
						&&//����
						(bag.components_number[Bag::Wax]>0)){
						Rect = button_pos[2];
						LastArea = button_pos[2];
					}
				else if((MousePos.X >= button_pos[3].Left && MousePos.X <= button_pos[3].Right)
						&&
						(MousePos.Y <= button_pos[3].Bottom && MousePos.Y >= button_pos[3].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::SealOfBalance]
						&& 
						bag.construct_state[Bag::GoldenChassis]
						&&//δ����
						!bag.link_state[3]
						&&//��ʯӢ
						(bag.components_number[Bag::Quartz]>0)){
						Rect = button_pos[3];
						LastArea = button_pos[3];
					}
				else if((MousePos.X >= button_pos[4].Left && MousePos.X <= button_pos[4].Right)
						&&
						(MousePos.Y <= button_pos[4].Bottom && MousePos.Y >= button_pos[4].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::ScryingLens]
						&& 
						bag.construct_state[Bag::SealOfBalance]
						&&//δ����
						!bag.link_state[4]
						&&//����
						(bag.components_number[Bag::Silver]>0)){
						Rect = button_pos[4];
						LastArea = button_pos[4];
					}
				else if((MousePos.X >= button_pos[5].Left && MousePos.X <= button_pos[5].Right)
						&&
						(MousePos.Y <= button_pos[5].Bottom && MousePos.Y >= button_pos[5].Top)
						&&//��װ�����ѳ���
						bag.construct_state[Bag::GoldenChassis]
						&& 
						bag.construct_state[Bag::VoidGate]
						&&//δ����
						!bag.link_state[5]
						&&//����
						(bag.components_number[Bag::Gum]>0)){
						Rect = button_pos[5];
						LastArea = button_pos[5];
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
				if(	LastArea.Left == bag_back_position.Left 
					&& 
					LastArea.Right == bag_back_position.Right){
					Clear();
					
					bag.last_state = LINK_AREA;
					return 0;
				}
				else if(LastArea.Left == bag_position.Left && LastArea.Right == bag_position.Right){
					//���뱳������
					bag.last_state = LINK_AREA;
					bag.current_state = OPEN_BAG;
					IntoBag();
					
					Clear();
					DrawInformationBar();
					DrawLinkArea();

					bag.last_state = OPEN_BAG;
					bag.current_state = LINK_AREA;
				}
				//���Ӱ�ť
				else if(LastArea.Left == button_pos[0].Left
						&&
						LastArea.Right == button_pos[0].Right
						&&
						LastArea.Bottom == button_pos[0].Bottom
						&&
						LastArea.Top == button_pos[0].Top
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
						&&//��װ�����ѳ���
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
					//ʧ��
					return 0;
				}
			}
		}
	}
	return 1;//1:�쳣����
}

int Controller::DrawLinkArea(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/************************************************
	 ˮ����� �ƽ�����
	 ����֮�� ƽ���ӡ
	 ����֮�� ���֮��
	 ƽ���ӡ �ƽ�����
	 ռ��͸�� ƽ���ӡ
	 �ƽ����� ���֮��
 ************************************************/
/*
	SetConsoleCursorPosition(hOut, { 9, 7 });//ͳһ���
	cout<<"      ����װ��";
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"Ǧ:   ˮ�����"<<(bag.link_state[0]?"��":"��")<<"�ƽ�����";
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"����: ����֮��"<<(bag.link_state[1]?"��":"��")<<"ƽ���ӡ";
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"��:   ����֮��"<<(bag.link_state[2]?"��":"��")<<"���֮��";
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"ʯӢ: ƽ���ӡ"<<(bag.link_state[3]?"��":"��")<<"�ƽ�����";
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"��:   ռ��͸��"<<(bag.link_state[4]?"��":"��")<<"ƽ���ӡ";
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"��: �ƽ�����"<<(bag.link_state[5]?"��":"��")<<"���֮��";
	*/

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, {2, 6});
	cout<<"��ǰ����ֵ:"<<bag.activate_hard_level;

	SetConsoleCursorPosition(hOut, { 9, 7 });//ͳһ���
	cout<<"      ����װ��";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 8 });
	cout<<"Ǧ:   ";
	if(bag.construct[Bag::CrystalBattery]){//�ѻ��
		if(bag.construct_state[Bag::CrystalBattery]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ˮ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[0]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";

	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 10 });
	cout<<"����: ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[1]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 12 });
	cout<<"��:   ";
	if(bag.construct[Bag::HermeticMirror]){//�ѻ��
		if(bag.construct_state[Bag::HermeticMirror]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"����֮��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[2]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";


	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 14 });
	cout<<"ʯӢ: ";
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[3]?"��":"��");
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
		

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 16 });
	cout<<"��:   ";
	if(bag.construct[Bag::ScryingLens]){//�ѻ��
		if(bag.construct_state[Bag::ScryingLens]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ռ��͸��";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[4]?"��":"��");
	if(bag.construct[Bag::SealOfBalance]){//�ѻ��
		if(bag.construct_state[Bag::SealOfBalance]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"ƽ���ӡ";

	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 9, 18 });
	cout<<"��: ";
	if(bag.construct[Bag::GoldenChassis]){//�ѻ��
		if(bag.construct_state[Bag::GoldenChassis]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"�ƽ�����";
	SetConsoleTextAttribute(hOut, 0x0007);
	cout<<(bag.link_state[5]?"��":"��");
	if(bag.construct[Bag::VoidGate]){//�ѻ��
		if(bag.construct_state[Bag::VoidGate]){//������
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else{//δ���
		SetConsoleTextAttribute(hOut, 0x0007);
	}
	cout<<"���֮��";
	
	//���ذ�ť
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";
	
	return 0;
}

int Controller::IntoLink(int chose_link){
	Clear();
	DrawInformationBar();
	DrawLink(chose_link);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������

	SetConsoleTextAttribute(hOut, 0x0070);//��������ı�����

	
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
	//ѭ��3��
	for(int i=0; i<3; i++){//һ��ѭ��
		a = rand()%6 + 1;
		b = rand()%6 + 1;
		SetConsoleCursorPosition(hOut, {20, 8});
		cout<<a;
		SetConsoleCursorPosition(hOut, {24, 8});
		cout<<b;
		
		//������
		while (1) {//����ѭ��
			ReadConsoleInput(hIn, &record, 1, temp);
			if (record.EventType == MOUSE_EVENT) {
                
				COORD MousePos = record.Event.MouseEvent.dwMousePosition;
				//�ж����λ��
				if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
					||//ע��Bottom��Top�Ĵ�С��ϵ
					(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
					) {//��������������ı�
					//�ı䰴ť�ķ���״̬
					//ԭ��λ�ñ䰵
					FillConsoleOutputAttribute(	hOut, 0x0070, 
												LastArea.Right - LastArea.Left + 1, 
												COORD{LastArea.Left, LastArea.Top}, temp);

					SMALL_RECT Rect;
					//7����ť
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
					//�µ�λ�ñ���
					FillConsoleOutputAttribute(hOut, 0x00F0, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
				}
				
				//�������
				if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
					if(LastArea.Right == -1 && LastArea.Bottom == -1)
						continue;
					
					//�����
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

	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����

	bool SuccessfulLink = true;
	SetConsoleCursorPosition(hOut, {17, 14});
	a = board[0] - board[3];
	if(a<0){
		cout<<"1�����Ӷ�·������ʧ��";
		SuccessfulLink = false;
	}
	else{
		cout<<"1�����ӳɹ�";
	}

	SetConsoleCursorPosition(hOut, {17, 15});
	a = board[1] - board[4];
	if(a<0){
		cout<<"2�����Ӷ�·������ʧ��";
		SuccessfulLink = false;
	}
	else{
		cout<<"2�����ӳɹ�";
	}
	
	SetConsoleCursorPosition(hOut, {17, 16});
	a = board[3] - board[5];
	if(a<0){
		cout<<"3�����Ӷ�·������ʧ��";
		SuccessfulLink = false;
	}
	else{
		cout<<"3�����ӳɹ�";
	}
	
	SetConsoleCursorPosition(hOut, {17, 17});
	if(SuccessfulLink){
		cout<<"���ӳɹ���";
		SetConsoleCursorPosition(hOut, {17, 18});
		cout<<"����ֵ����"<<board[0]+board[1]+board[2]-board[3]-board[4]-board[5];
		bag.activate_hard_level += (board[0]+board[1]+board[2]-board[3]-board[4]-board[5]);
		bag.link_state[chose_link] = true;
		a=1;//�����۳����
	}
	else{
		cout<<"����ʧ�ܣ�";
		SetConsoleCursorPosition(hOut, {17, 18});
		cout<<"����۳�1�����";
		a=2;
	}

	//�۳���Ӧ���
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
	//����1��
	DayEnd();

	SetConsoleCursorPosition(hOut, { 36, 17 });
	cout<<"����";


	//���ذ�ť
	LastArea={ 0,0,-1,-1 };//��ʼ��
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
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
	LPDWORD temp = new DWORD;//û��ʵ������


	
	//��ɫ�ӽ���
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
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED);//��������ı�����
	for(int i=0; i<=10; i++){
		SetConsoleCursorPosition(hOut, {12, 17});
		cout<<10-i<<' ';
		Sleep(1000);
	}
	SetConsoleCursorPosition(hOut, {12, 17});
		cout<<"   ";

	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	int color = 0x0007;
	
	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, color, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= bag_back_position.Left && MousePos.X <= bag_back_position.Right)
					&&
					(MousePos.Y <= bag_back_position.Bottom && MousePos.Y >= bag_back_position.Top)){
						//�����ڷ��ذ�ť��
						Rect = bag_back_position;
						LastArea = bag_back_position;
						color = 0x0007;
					}
				else if((MousePos.X >= bag_position.Left && MousePos.X <= bag_position.Right)
					&&
					(MousePos.Y <= bag_position.Bottom && MousePos.Y >= bag_position.Top)){
						//������ť
						Rect = bag_position;
						LastArea = bag_position;
						color = 0x0007;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//ȷ�ϼ�����ť
						Rect = search_button;
						LastArea = search_button;
						color = FOREGROUND_RED | FOREGROUND_INTENSITY;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | color, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//�˳�����
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
					// ����
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
						&& //ȷ�ϼ���
						LastArea.Right == search_button.Right){

					bag.current_state = FINAL_ACTIVATE_AREA;;
					bag.last_state = FINAL_ACTIVATE;
					IntoFinalActivate();

					bag.current_state = FINAL_ACTIVATE;
					bag.last_state = FINAL_ACTIVATE_AREA;

					if(bag.win_or_lose!=1){//�ѽ�����������
						return 0;//ֱ�ӷ���
					}

					//δ������������
					
					Clear();
					DrawInformationBar();
					DrawWarn();
					Sleep(500);
				}
				Sleep(500);
			}
		}
	}
	return 1;//1:�쳣����

}

int Controller::DrawWarn(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
/************************************************
	               ���棡
 	  	һ����ʼ�����������㲻��ֹͣ�����
	ֻ�гɹ����������������Ƿ�ʼ����������
************************************************/	
	//rgb(255,0,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x0000);//��������ı�����

	SetConsoleCursorPosition(hOut, { 5, 8 });
	cout<<"               ���棡";
	SetConsoleCursorPosition(hOut, { 5, 9 });
	cout<<"һ����ʼ�����������㲻��ֹͣ�����ֻ";
	SetConsoleCursorPosition(hOut, { 5, 10 });
	cout<<"�гɹ����������������Ƿ�ʼ����������";

	
	SetConsoleTextAttribute(hOut, 0x0007);//rgb(180,180,180)
	SetConsoleCursorPosition(hOut, { bag_back_position.Left, bag_back_position.Top });
	cout<<"����";

	//rgb(255,0,0)
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED | 0x0000);//��������ı�����
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"ȷ�ϼ���";
	
	
	return 0;
}

int Controller::IntoFinalActivate(){
	Clear();
	DrawInformationBar();
	DrawFinalActivate();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	
	while (1) {
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||
				(MousePos.Y > LastArea.Bottom || MousePos.Y < LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, 0x0007, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= sacrifice_button.Left && MousePos.X <= sacrifice_button.Right)
					&&
					(MousePos.Y <= sacrifice_button.Bottom && MousePos.Y >= sacrifice_button.Top)){
						//�׼���ť
						Rect = sacrifice_button;
						LastArea = sacrifice_button;
					}
				else if((MousePos.X >= final_activate_button.Left && MousePos.X <= final_activate_button.Right)
						&&
						(MousePos.Y <= final_activate_button.Bottom && MousePos.Y >= final_activate_button.Top)){
						//������ť
						Rect = final_activate_button;
						LastArea = final_activate_button;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
					
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | 0x0007, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);

			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				//����ѡ��,�ı�����
				if(	LastArea.Left == sacrifice_button.Left && LastArea.Right == sacrifice_button.Right){
					//�׼�
					
					if(bag.HP>0){
						//�����׼�
						bag.HP--;
						bag.activate_hard_level--;
						
						Clear();
						DrawInformationBar();
						DrawFinalActivate();
						SetConsoleCursorPosition(hOut, {10, 12});
						cout<<"�׼��ɹ�������ֵ����1��";
					}
					else{
						//ûѪ��
						SetConsoleCursorPosition(hOut, {10, 12});					
						cout<<"  ����ֵ�������׼�ʧ�� ";
					}
					
					Sleep(500);
					
				}
				else if(LastArea.Left == final_activate_button.Left && LastArea.Right == final_activate_button.Right){
					//!��������
					
					if(FinalActivate() == 2){//����ʧ��
						bag.win_or_lose = 2;
					}
					else{//�����ɹ�
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
	LPDWORD temp = new DWORD;//û��ʵ������

	SetConsoleCursorPosition(hOut, {16, 8});
	cout<<"�����Ѷȣ�"<<bag.activate_hard_level;

	SetConsoleCursorPosition(hOut, {14, 14});
	cout<<"�׼�";

	SetConsoleCursorPosition(hOut, {26, 14});
	cout<<"����";

	return 0;
}

int Controller::FinalActivate(){
	//TODO�������˧���Ķ���
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	LPDWORD temp = new DWORD;//û��ʵ������
	
	SetConsoleTextAttribute(hOut, 0x0007);
	SetConsoleCursorPosition(hOut, {26, 14});
	cout<<"����";
	
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
	cout<<"��ʼ����";
	
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
	cout<<"�Ǳ��̿���";
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
	cout<<"��ʼͶ����һ������";
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
	cout<<"��һ�����ӽ��Ϊ"<<a;

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
	cout<<"��ʼͶ���ڶ�������";
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
	cout<<"�ڶ������ӽ��Ϊ"<<b;
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
	
	cout<<"���ս��Ϊ"<<a+b<<"������"<<( (a+b>=bag.activate_hard_level) ? "�ɹ�" : "ʧ��");
	Sleep(3000);

	//�ж��Ƿ�ɹ�����
	if(a+b >= bag.activate_hard_level){//�ɹ�����
		return 0;
	}
	else{//����ʧ��
		return 2;
	}
	return 1;
}

int Controller::EndGame(){
	Clear();
	//{14,11}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����

	
	SetConsoleCursorPosition(hOut, { 10, 11 });
	
	if(bag.win_or_lose==2){//ʧ��
		cout<<"��Ϸʧ��";
		Sleep(444);
		cout<<"����û����������";
	}
	else{//�ɹ�
		cout<<"����ɹ������������������磡";
	}

	Sleep(1000);
	

	
	SetConsoleCursorPosition(hOut, { search_button.Left, search_button.Top });
	cout<<"����һ��";
	SMALL_RECT back = {19, 17, 41, 17};
	SetConsoleCursorPosition(hOut, { back.Left, back.Top });

	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//��������ı�����
	cout<<"��ѧϰͨ���ˣ��Ҳ�����";
	SetConsoleTextAttribute(hOut, 0x0007);//��������ı�����

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD record;//������¼������״̬
	LPDWORD temp = new DWORD;//û��ʵ������

	SMALL_RECT LastArea{ 0,0,-1,-1 };//֮ǰ�������������
	int color = 0x0007;

	while (1) {//һ��ѭ��
		ReadConsoleInput(hIn, &record, 1, temp);
		if (record.EventType == MOUSE_EVENT) {
			COORD MousePos = record.Event.MouseEvent.dwMousePosition;
			//�ж����λ��
			if ((MousePos.X < LastArea.Left || MousePos.X > LastArea.Right)
				||//ע��Bottom��Top�Ĵ�С��ϵ
				(MousePos.Y < LastArea.Bottom || MousePos.Y > LastArea.Top)
				) {//��������������ı�
				//�ı䰴ť�ķ���״̬
				//ԭ��λ�ñ䰵
				FillConsoleOutputAttribute(	hOut, color, 
											LastArea.Right - LastArea.Left + 1, 
											COORD{LastArea.Left, LastArea.Top}, temp);

				SMALL_RECT Rect;
				if(	(MousePos.X >= back.Left && MousePos.X <= back.Right)
					&&
					(MousePos.Y <= back.Bottom && MousePos.Y >= back.Top)){
						//������
						Rect = back;
						LastArea = back;
						color = FOREGROUND_RED;
					}
				else if((MousePos.X >= search_button.Left && MousePos.X <= search_button.Right)
					&&
					(MousePos.Y <= search_button.Bottom && MousePos.Y >= search_button.Top)){
					//����һ��
						Rect = search_button;
						LastArea = search_button;
						color = 0x0007;
					}
				else{
					LastArea = {0, 0, -1, -1};
					continue;
				}
				//�µ�λ�ñ���
				FillConsoleOutputAttribute(hOut, COMMON_LVB_REVERSE_VIDEO | color, Rect.Right - Rect.Left + 1, COORD{Rect.Left, Rect.Top}, temp);
			}
			
			//�������
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				if(LastArea.Right == -1 && LastArea.Bottom == -1)
					continue;
				
				//������
				if(	LastArea.Left == back.Left 
					&& 
					LastArea.Right == back.Right){
					return 2;
				}
				else if(LastArea.Left == search_button.Left 
						&& 
						LastArea.Right == search_button.Right){
						// ����һ��
					return 0;
				}
				Sleep(500);
			}
		}
	}

	return 1;
}

int Controller::Init(){
	//Action();//��ʼ����Ķ���

	Clear();

	/************************************************
	 * Bag ��ʼ��
 	************************************************/
	bag.tool_belt.dowing_rod = true;
	bag.tool_belt.paralysis_wand = true;
	//bag.tool_belt.focus_charm = true;
	for(int i=0; i<6; i++){
		bag.components_number[i] = 0;
		bag.treasure[i] = 0;
		bag.construct[i] = 0;
		bag.construct_state[i] = 0;
		//?�·�0��Ϊ1�����ɿ���������������
		bag.link_state[i] = 0;
	}
	
	bag.activate_hard_level = 0;
	bag.gods_hand = 0;
	bag.HP = 6;
	bag.current_state = SELECT_AREA;
	bag.win_or_lose = 1;

	/************************************************
	 * TimeSystem ��ʼ��
 	************************************************/
	time_system.day_now = 1;
	time_system.basic_time = 14;
	time_system.extra_time = 0;
	//time_system.event_cycle = 3;
	
	/************************************************
	 * Controller ��ʼ��
 	************************************************/
	v = 0;
	
	/************************************************
	 * SearchArea ��ʼ��
 	************************************************/
	search_area.InitAreaInfo();
	
	//DrawSelectArea();
	return 0;
}

int Controller::DayEnd(){
	time_system.day_now++;

	if(bag.treasure[Bag::BraceletOfLos]){//�ѻ����������
		//�ϵ�֮��+1
		bag.gods_hand++;
	}
	
	if(bag.treasure[Bag::ScaleOfTheInfinityWurm]){//�ѻ������֮��
		//HP+1
		bag.HP = min(bag.HP + 1, 6);
	}

	if(time_system.day_now > time_system.basic_time + time_system.extra_time){
		//ʱ���þ�
		bag.win_or_lose = 2;//��Ϸʧ��
	}
	return 0;
}



