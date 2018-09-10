#pragma once
#include<windows.h>
#include"Snake.h"
#include<conio.h>
#include<time.h>
#include<fstream>
const int Size = 25;
class Game
{
public:
	Game();
	~Game();
	COORD coor;
	void CreatFood();					//随机生成食物
	void CreatMap();						//初始化边框
	void OutputMap();					//打印地图
	void CreatObstruction();			//随机生成障碍物
	void Hide_or_show_Cursor(int x);				//0表示隐藏，1表示显示光标
	void gotoxy(int x, int y, COORD &coor);				//定位光标函数
	short getWidth();					//获取窗口大小
	void moving(char keyboard, COORD &coor,bool &judge);		//根据从键盘输入的方向来移动蛇
	int GameMenu( COORD &coor);		//打印游戏菜单
	void Choose(char tmp, COORD &coor);  //选择功能
	void EndGame( COORD &coor);  //结束游戏
	void StartGame(COORD &coor,bool &judge);   //开始游戏函数
	int getSnakeLength();
	int getLeave();
	int getHighestScore();
	void setHighestScore(int score);
	Snake *getSnake();
private:
	Snake *m_pSnake;
	char Map[Size][Size];
	int m_iFood_x;
	int m_iFood_y;
	int m_iScore;
	int m_iLeave;
};

