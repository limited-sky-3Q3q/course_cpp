/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\Bag.h
 * Date: 2020-05-04 11:04:34
 * LastEditTime: 2020-05-29 15:04:47
 * !��������: ������bug
************************************************/

#ifndef BAG_H
#define BAG_H
class ToolBelt {//��������
/************************************************
	��ʼֵȫ���ѳ���
************************************************/
public:
	bool dowing_rod{ true };//̽��Ȩ��
	bool paralysis_wand{ true };//���Ȩ��
	//bool focus_charm{ true };//�۽�����
};


class Bag {//����
public:
	Bag(){};
	ToolBelt tool_belt;//���ߴ�
	//����ʯӢ���𽺣�����������Ǧ
	enum { Silver, Quartz, Gum, Silica, Wax, Lead };//�����
	int components_number[6]{2,3,0,3,3,3};//�������
	
	//�����ؼ� �������� ҹ��ӫ˿ ����֮�� Զ�ż��� ������Ƭ 
	enum { IcePlate, BraceletOfLos, ShimmeringMoonlace,
		   ScaleOfTheInfinityWurm, TheAncientRecord, TheMoltenSharo};//������
	int treasure[6]{1,1,0,0,1,0};//���������
	
	//ƽ���ӡ ����֮�� ���֮�� �ƽ����� ռ��͸�� ˮ����� 
	//SealOfBalance, HermeticMirror, VoidGate, GoldenChassis, ScryingLens, CrystalBattery
	enum { SealOfBalance, HermeticMirror, VoidGate, 
			GoldenChassis, ScryingLens, CrystalBattery };//װ����
	bool construct[6]{1,1,1,1,1,1};//װ�û�����
	bool construct_state[6]{1,1,1,0,1,0};//װ�ó���״̬

	/************************************************
	 ˮ����� �ƽ�����
	 ����֮�� ƽ���ӡ
	 ����֮�� ���֮��
	 ƽ���ӡ �ƽ�����
	 ռ��͸�� ƽ���ӡ
	 �ƽ����� ���֮��
 ************************************************/
	bool link_state[6]{0,1,1,1,1,0};//�������

	int activate_hard_level{8};//�����Ѷ�

	int gods_hand{ 7 };//�ϵ�֮�ֵĵ���
	int HP{ 6 };//����ֵ����ʼֵ6��
	
	int current_state{ 0 };//���ڵ�״̬����������������Ƿ�����
	int last_state{0};//�ϸ�״̬

	int win_or_lose{1};//0Ϊʤ����2Ϊʧ�ܣ�1Ϊδ����
};
#endif