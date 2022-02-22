/****************************************************
*   Functions to solve mazes.                       *
*                                                   *
*   Datafile must still contain size as first data. *
*                                                   *
*   Four functions are only stubs.                  * 
****************************************************/

#include <iostream>
#include <fstream>
#include "Maze.h"
using namespace std;

enum Direction {DOWN, LEFT, UP, RIGHT};
struct Position
{
	int H, V;
};
char maze[17*17];
int mazeWidth, mazeHeight;
int posi[17*17];
int i=0;
//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

void FindEntrance(int&);
bool AtExit(int);
void ReportPosition(int);
void WheresRight(int,Direction,int&);
bool Wall(int);
void TurnRight(Direction&);
void MoveForward(int&,Direction);
void WheresAhead(int,Direction,int&);
void TurnLeft(Direction&);

bool LoadMaze(const char fname[]){//读取迷宫
	ifstream ifs(fname);
	
	if (ifs.good())
	{
		ifs >> mazeWidth >> mazeHeight;
		for (int i=0;i<mazeHeight;i++)
			for (int j=0;j<mazeWidth;j++)
				ifs >> maze[i*mazeWidth+j];
		ifs.close();
		return true;
	}
	else
	{
		cerr << "File not found." << endl;
		return false;
	}
}

//靠着左墙走
//输出行走路径
void SolveMaze(){	
	int pos, other;
	Direction heading;
	
	FindEntrance(pos);//把pos引移动到入口
	heading = DOWN;
	while (!AtExit(pos)){//还没到达出口
		posi[i]=pos;//记录位置
		i++;
		if(i>=289){//超过数组大小
			cout<<"array too small\n";
			abort();
		}
		WheresRight(pos,heading,other);//靠右走的话会到达other
		if (!Wall(other)){//要走的方向没有墙
			TurnRight(heading);//向右转
			MoveForward(pos,heading);//向前走
		}
		else{
			WheresAhead(pos,heading,other);//向前走的话会到达other
			if (!Wall(other))//前面没有墙
				MoveForward(pos,heading);//向前走
			else
				TurnLeft(heading);//向左走
		}
	}
	posi[i]=pos;//记录出口的位置
	i++;
	if(i>=400){//?
		cout<<"array too small\n";
		abort();
	}
	int counter=0;
	for(int j=0;j<i;j++)
	{
		if(posi[j]<0)
			continue;
		cout << "现在的位置: (" << posi[j]/mazeWidth << ',' << posi[j]%mazeWidth << ')' << endl;
		counter++;
	}
	cout<<"总步数:"<<counter<<endl;
	cout << "该迷宫已解决" << endl;
}

void FindEntrance(int& pos){
	pos= 0;	
	while (Wall(pos)) pos++;
}

bool AtExit(int pos){
	return (pos >= (mazeHeight-1)*mazeWidth);
}

//	This function displays the position in the maze
//	At this time it specifies row and column of the array

/*void ReportPosition(int pos)
{
	cout << "Current position: (" << pos/mazeWidth << ',' << pos%mazeWidth << ')' << endl;
}*/
void WheresRight(int pos, Direction heading, int& right){
	right=pos;
	switch (heading) {
		case DOWN:{
				right--;
				break;
		}
		case LEFT:{
				right-=mazeWidth;
				break;
		}
		case UP:{
				right++;
				break;
		}
		case RIGHT:{
				right+=mazeWidth;
		}
	}

}

bool Wall(int pos){
	return (maze[pos] == '#');
}

void TurnRight(Direction& heading){
	switch (heading){
		case DOWN:{
				heading=LEFT;
				break;
		}
		case LEFT:{
				heading=UP;
				break;
		}
		case UP:{
				heading=RIGHT;
				break;
		}
		case RIGHT:{
				heading=DOWN;
		}
	}
}

void MoveForward(int& pos, Direction heading){
	switch (heading) {
		case DOWN:{
				pos+=mazeWidth;
				break;
		}
		case LEFT:{
				pos--;
				break;
		}
		case UP:{
				pos-=mazeWidth;
				break;
		}
		case RIGHT:{
				pos++;
		}
	}
}

void WheresAhead(int pos, Direction heading, int& ahead){
	switch (heading) {
		case DOWN:{
				ahead=pos+mazeWidth;
				break;
		}
		case LEFT:{
				ahead=pos-1;
				break;
		}
		case UP:{
				ahead=pos-mazeWidth;
				break;
		}
		case RIGHT:{
				ahead=pos+1;
		}
	}
}

void TurnLeft(Direction& heading){
	switch (heading){
		case DOWN:{
				heading=RIGHT;
				break;
		}
		case LEFT:{
				heading=DOWN;
				break;
		}
		case UP:{
				heading=LEFT;
				break;
		}
		case RIGHT:{
				heading=DOWN;
		}
	}
}
