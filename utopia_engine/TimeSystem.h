/************************************************
 * TODO Auther: by SR
 * FilePath: \digital designc:\Users\SR\Documents\vscodefile\games\utopia_engine\TimeSystem.h
 * Date: 2020-05-04 11:02:53
 * LastEditTime: 2020-05-29 14:59:30
 * !今日运势: 吉，无bug
************************************************/
class TimeSystem {//时间系统
public:
	TimeSystem(){};
	int day_now{ 7 };//现在是第几天，初始值为1
	int basic_time{ 14 };//基础天数，默认14天
	int extra_time{ 2 };//额外添加的时间

	//int event_cycle{ 3 };//事件周期，默认3天
};