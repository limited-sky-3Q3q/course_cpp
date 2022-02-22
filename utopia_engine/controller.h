/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\controller.h
 * Date: 2020-05-03 11:01:56
 * LastEditTime: 2020-05-11 19:12:52
 * !��������: ������bug
************************************************/
/************************************************
 //TODO ��֪����
 1. ʹ��system�����ᵼ���޷��������
 2. ����̨��Ҫ�޸Ĳ���ѡ��������û������ʹ��ڴ�С
************************************************/
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<windows.h>
#include"TimeSystem.h"
//#include"ArtifactWorkshop.h"
#include"Bag.h"
#include"SearchArea.h"
//���ڵ�״̬
#define INTRODUCE_BACKGROUND   0x0001 //���½��ܽ���
#define ACTION                 0x0002 //��ʼ����
#define SELECT_AREA            0x0004 //ѡ�����
#define OPEN_BAG               0x0008 //�򿪱���
#define ARTIFACT_WORKSHOP      0x0010 //��������
#define ACTIVATE_AREA          0x0020 //��������
#define ACTIVATE               0x0040 //��������
#define LINK_AREA              0x0080 //��������
#define LINK                   0x0100 //��������
#define FINAL_ACTIVATE_AREA    0x0200 //������������
#define FINAL_ACTIVATE         0x0400 //������������
#define SEARCH_AREA_INTERFACE  0x0800 //̽�������ѡ�����6ѡ1
#define SEARCH_AREA            0x1000 //��������
#define SEARCH                 0x4000 //������
#define BATTLE                 0x8000 //ս����




class Controller{//������

    //*���ǿ���һ������ͨ��

    private://������Ϸ��һֱ���ڵĶ���
        Bag bag;//�������Ͼ��е����Ժ���Ʒ
        TimeSystem time_system;//ʱ��ϵͳ

        COORD windows_size={46, 20};//���ڴ�С
        SMALL_RECT windows_rect={0, 0, 46-1, 20-1};

        //��¼��ť�����ϽǺ����½�λ��

        SMALL_RECT bag_position{4, 2, 7, 2};//������ť
        SMALL_RECT bag_back_position{36, 17, 39, 17};//��������ķ��ذ�ť��
        
        //ѡ����水ť

        SMALL_RECT select_search_area{14, 9, 17, 9};
        SMALL_RECT select_workshop_area{26, 9, 29, 9};
        SMALL_RECT final_activate_area{18, 11, 25, 11};
        //��Ϣ������
        SMALL_RECT current_state_position{4, 3, 20, 3};
        
        //������������
        SMALL_RECT search_button{4, 17, 11, 17};
        
        //������������
        SMALL_RECT activate_area_button{20, 9, 27, 9};//����װ�ð�ť
        SMALL_RECT link_area_button{20, 10, 27, 10};//��������ť
        
        //
        SMALL_RECT sacrifice_button{14, 14, 17, 14};//�׼���ť
        SMALL_RECT final_activate_button{26, 14, 29, 14};//����������ť
        
        //int IntroduceBackground();//���ܹ��±���
        //int Action();//��ʼ����Ķ���������������
        
        //selectHard//ѡ���Ѷ�

        int DrawInformationBar();//����Ϣ����������ʱ�䣬�ϵ�֮��

        int DrawSelectArea();//չʾѡ����棺������ð�գ�������ʱ��
        int SelectArea();//ѡ�����
        int SelectBack();//ѡ�񷵻�ѡ�����

        int IntoWorkshop();//���빤��
        int DrawWorkshop();//չʾ����

        int IntoActivateArea();//����ѡ������װ������
        int DrawActivateArea();//չʾѡ������װ������
        int IntoActivate(int);//��ѡ�е�װ�ý�������
        int DrawActivate(int);//չʾ��������

        int IntoWarn();//�������������ľ������
        int DrawWarn();//չʾ�������������ľ������
        int IntoFinalActivate();//��������������
        int DrawFinalActivate();//չʾ������������
        int FinalActivate();//!������������

        int IntoLinkArea();//����ѡ����������
        int DrawLinkArea();//չʾѡ����������
        int IntoLink(int);//����ѡ�������
        int DrawLink(int);//չʾ���ӽ���

        int IntoSearchArea();//������������
        int DrawSearchArea();//չʾ��������
        int IntoSelectedSearchArea(int);//����ѡ�е���������
        int DrawSelectedSearchArea();//չʾѡ�е���������
        int BeginSearch();//��ʼ����
        int DrawSearch();//չʾ������

        int Battle(int);//ս��
        int GetBraceletOfLos();//�����������


        int v=0;//��¼�������
        

        int IntoBag();//���뱳������
        int DrawBag();//չʾ��������
        int IntoAncientRecord();//ʹ��Զ�ż���
        int DrawAncientRecord();//չʾ��Զ�ż��½���
        //DrawBag���뱳������
        int Clear();//�����Ļ

        SearchArea search_area;//̽������
        //ArtifactWorkshop artifact_workshop;//��������

        //int GiveUp();//������һ����Ϸ
        int DayEnd();//�������
        int Init();//��Ϸ��ʼʱ��ʼ������
        //int CalculateScore();//����÷�
        int EndGame();//������Ϸ����ʱ����
        //int DrawFinalInterface();//չʾ��Ϸ������Ľ���
        //int SelectPlayAgain();//ѡ������һ��
    public:
        Controller(){};
        int BeginGame();//��ʼ��Ϸ
        
};

#endif