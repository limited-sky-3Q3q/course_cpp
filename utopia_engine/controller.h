/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\controller.h
 * Date: 2020-05-03 11:01:56
 * LastEditTime: 2020-05-11 19:12:52
 * !今日运势: 吉，无bug
************************************************/
/************************************************
 //TODO 已知问题
 1. 使用system函数会导致无法监听鼠标
 2. 控制台需要修改部分选项才能设置缓冲区和窗口大小
************************************************/
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<windows.h>
#include"TimeSystem.h"
//#include"ArtifactWorkshop.h"
#include"Bag.h"
#include"SearchArea.h"
//现在的状态
#define INTRODUCE_BACKGROUND   0x0001 //故事介绍界面
#define ACTION                 0x0002 //开始界面
#define SELECT_AREA            0x0004 //选择界面
#define OPEN_BAG               0x0008 //打开背包
#define ARTIFACT_WORKSHOP      0x0010 //工坊界面
#define ACTIVATE_AREA          0x0020 //启动区域
#define ACTIVATE               0x0040 //正在启动
#define LINK_AREA              0x0080 //链接区域
#define LINK                   0x0100 //正在链接
#define FINAL_ACTIVATE_AREA    0x0200 //最终启动区域
#define FINAL_ACTIVATE         0x0400 //进行最终启动
#define SEARCH_AREA_INTERFACE  0x0800 //探索区域的选择界面6选1
#define SEARCH_AREA            0x1000 //搜索区域
#define SEARCH                 0x4000 //搜索中
#define BATTLE                 0x8000 //战斗中




class Controller{//控制器

    //*考虑开启一个作者通道

    private://整局游戏里一直存在的东西
        Bag bag;//主角身上具有的属性和物品
        TimeSystem time_system;//时间系统

        COORD windows_size={46, 20};//窗口大小
        SMALL_RECT windows_rect={0, 0, 46-1, 20-1};

        //记录按钮的左上角和右下角位置

        SMALL_RECT bag_position{4, 2, 7, 2};//背包按钮
        SMALL_RECT bag_back_position{36, 17, 39, 17};//背包界面的返回按钮，
        
        //选择界面按钮

        SMALL_RECT select_search_area{14, 9, 17, 9};
        SMALL_RECT select_workshop_area{26, 9, 29, 9};
        SMALL_RECT final_activate_area{18, 11, 25, 11};
        //信息栏区域
        SMALL_RECT current_state_position{4, 3, 20, 3};
        
        //搜索界面区域
        SMALL_RECT search_button{4, 17, 11, 17};
        
        //工坊界面区域
        SMALL_RECT activate_area_button{20, 9, 27, 9};//启动装置按钮
        SMALL_RECT link_area_button{20, 10, 27, 10};//链接区域按钮
        
        //
        SMALL_RECT sacrifice_button{14, 14, 17, 14};//献祭按钮
        SMALL_RECT final_activate_button{26, 14, 29, 14};//最终启动按钮
        
        //int IntroduceBackground();//介绍故事背景
        //int Action();//开始界面的动画，可以跳过？
        
        //selectHard//选择难度

        int DrawInformationBar();//画信息栏，背包，时间，上帝之手

        int DrawSelectArea();//展示选择界面：工坊，冒险，背包，时间
        int SelectArea();//选择界面
        int SelectBack();//选择返回选择界面

        int IntoWorkshop();//进入工坊
        int DrawWorkshop();//展示工坊

        int IntoActivateArea();//进入选择启动装置区域
        int DrawActivateArea();//展示选择启动装置区域
        int IntoActivate(int);//对选中的装置进行启动
        int DrawActivate(int);//展示启动界面

        int IntoWarn();//进入最终启动的警告界面
        int DrawWarn();//展示进入最终启动的警告界面
        int IntoFinalActivate();//进行最终启动！
        int DrawFinalActivate();//展示最终启动界面
        int FinalActivate();//!进行最终启动

        int IntoLinkArea();//进入选择链接区域
        int DrawLinkArea();//展示选择链接区域
        int IntoLink(int);//进入选择的链接
        int DrawLink(int);//展示链接界面

        int IntoSearchArea();//进入搜索界面
        int DrawSearchArea();//展示搜索界面
        int IntoSelectedSearchArea(int);//进入选中的搜索界面
        int DrawSelectedSearchArea();//展示选中的搜索界面
        int BeginSearch();//开始搜索
        int DrawSearch();//展示搜索框

        int Battle(int);//战斗
        int GetBraceletOfLos();//获得雷神手镯


        int v=0;//记录链接情况
        

        int IntoBag();//进入背包界面
        int DrawBag();//展示背包界面
        int IntoAncientRecord();//使用远古记事
        int DrawAncientRecord();//展示用远古记事界面
        //DrawBag进入背包界面
        int Clear();//清空屏幕

        SearchArea search_area;//探索界面
        //ArtifactWorkshop artifact_workshop;//工坊界面

        //int GiveUp();//放弃这一句游戏
        int DayEnd();//今天结束
        int Init();//游戏开始时初始化数据
        //int CalculateScore();//计算得分
        int EndGame();//本局游戏结束时调用
        //int DrawFinalInterface();//展示游戏结束后的界面
        //int SelectPlayAgain();//选择再来一局
    public:
        Controller(){};
        int BeginGame();//开始游戏
        
};

#endif