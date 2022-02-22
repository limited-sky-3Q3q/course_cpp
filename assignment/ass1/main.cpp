

#include <iostream>
#include "Maze.h"
using namespace std;

/****************************************************
*   Functions to solve mazes.                       *
*                                                   *
*   Datafile must still contain size as first data. *
*                                                   *
*   Four functions are only stubs.                  * 
****************************************************/

#include <iostream>
#include <fstream>
#include <memory.h>
#include<iomanip>
#include "Maze.h"
using namespace std;

enum Direction {DOWN, LEFT, UP, RIGHT};
struct Position
{
	int H, V;
};
//char maze[17*17];
char* maze;
int mazeWidth, mazeHeight;
//int posi[17*17];
int* posi;
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

bool LoadMaze(const char fname[]){//��ȡ�Թ�
	ifstream ifs(fname);
	
	if (ifs.good())
	{
		ifs >> mazeWidth >> mazeHeight;
		maze = new char[mazeWidth*mazeHeight];
		posi = new int[mazeWidth*mazeHeight];
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

//������ǽ��
//�������·��
void SolveMaze(){	
	int pos, other;
	Direction heading;
	int move[mazeHeight][mazeWidth],cnt=1;
	memset(move,0,sizeof(move));
	FindEntrance(pos);//��pos���ƶ������
	move[pos/mazeWidth][pos%mazeWidth]=cnt++;
	heading = DOWN;
	posi[i]=pos;//��¼λ��
	i++;
	while (!AtExit(pos)){//��û�������
		//ReportPosition(pos);cout<<"\n";
		
		/*
		if(i%100==0){
			char temp[17][17];
			for(int j=0; j<17; j++){
				for(int k=0; k<17; k++){
					temp[j][k]=' ';
				}
			}
			for(int j=0; j<i; j++){
				temp[posi[i]/mazeWidth][posi[i]%mazeWidth ]='A';
			}
			for(int j=0; j<17; j++){
				for(int k=0; k<17; k++){
					cout<<temp[j][k];
				}
				cout<<"\n";
			}
		}
		*/
		/*
		if(i>=289){//���������С
			cout<<"array too small\n";
			abort();
		}
		*/
		WheresRight(pos,heading,other);//�����ߵĻ��ᵽ��other
			if (!Wall(other)){//Ҫ�ߵķ���û��ǽ
				if(move[other/mazeWidth][other%mazeWidth]==0){
					move[other/mazeWidth][other%mazeWidth]=cnt++;
				}
				else if(move[other/mazeWidth][other%mazeWidth]<cnt&&move[other/mazeWidth][other%mazeWidth]!=0){
					cnt=move[other/mazeWidth][other%mazeWidth]+1;
					move[pos/mazeWidth][pos%mazeWidth]=0;
				}
			TurnRight(heading);//����ת
			MoveForward(pos,heading);//��ǰ��
			
			posi[i]=pos;//��¼λ��
			i++;
		}
		else{
			WheresAhead(pos,heading,other);//��ǰ�ߵĻ��ᵽ��other
			if (!Wall(other)){//ǰ��û��ǽ
				if(move[other/mazeWidth][other%mazeWidth]==0){
					move[other/mazeWidth][other%mazeWidth]=cnt++;
				}
				else if(move[other/mazeWidth][other%mazeWidth]<cnt&&move[other/mazeWidth][other%mazeWidth]!=0){
					cnt=move[other/mazeWidth][other%mazeWidth]+1;
					move[pos/mazeWidth][pos%mazeWidth]=0;
				}
				MoveForward(pos,heading);//��ǰ��
				posi[i]=pos;//��¼λ��
				i++;
			}
			else
				TurnLeft(heading);//����ת
		}
	}
	//move[pos/mazeWidth][pos%mazeWidth]=cnt;
	posi[i]=pos;//��¼���ڵ�λ��
	i++;
	if(i>=400){//?
		cout<<"array too small\n";
		abort();
	}
	int counter=0;
	for(int j=0;j<i;j++){
		counter++;
	}
	cout<<"�ܲ���:"<<counter<<endl;
 /******************************
    ������ߵ�·��
 ******************************/
    for(int j=0; j<mazeHeight; j++){
		for(int k=0; k<mazeWidth; k++){
			cout<<setw(2)<<maze[j*mazeWidth+k];
		}
		cout<<'\n';
	}
	for(int j=0; j<mazeHeight; j++){
		for(int k=0; k<mazeWidth; k++){
			cout<<setw(3)<<move[j][k];
		}
		cout<<'\n';
	}
	int temp_pos;
	char paint[mazeHeight][mazeWidth];
	FindEntrance(temp_pos);
	int y=temp_pos/mazeWidth,x=temp_pos%mazeWidth;

	for(int j=0; j<mazeHeight; j++){
		for(int k=0; k<mazeWidth; k++){
			paint[j][k]='.';
		}
	}
	paint[y][x]='O';
	while(!AtExit(y*mazeWidth+x)){
		if(move[y][x+1]==move[y][x]+1){
			paint[y][x+1]='O';
			x++;
			continue;
		}
		if(move[y+1][x]==move[y][x]+1){
			paint[y+1][x]='O';
			y++;
			continue;
		}
		if(move[y-1][x]==move[y][x]+1){
			paint[y-1][x]='O';
			y--;
			continue;
		}
		if(move[y][x-1]==move[y][x]+1){
			paint[y][x-1]='O';
			x--;
			continue;
		}	
	}
	for(int j=0; j<mazeHeight; j++){
		for(int k=0; k<mazeWidth; k++){
			if(maze[j*mazeWidth+k]=='#'){
				paint[j][k]='#';
			}
		}
	}
	for(int j=0; j<mazeHeight; j++){
		for(int k=0; k<mazeWidth; k++){
			cout<<setw(2)<<paint[j][k];
		}
		cout<<'\n';
	}

	cout << "���Թ��ѽ��" << endl;
	system("pause");
}

void FindEntrance(int& pos){
	pos= 0;	
	while (Wall(pos)) pos++;
}

bool AtExit(int pos){
	return (pos >= (mazeHeight-1)*mazeWidth);
}

void ReportPosition(int pos){
	cout << "Current position: (" << pos/mazeWidth << ',' << pos%mazeWidth << ')' << endl;
}
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
				heading=UP;
		}
	}
}














int main()
{	
	char fname[64];
	
	cout << "Maze File: ";
	cin >> fname;
	if (LoadMaze(fname))
		SolveMaze();
	
	system("pause");
	return 0;
}









