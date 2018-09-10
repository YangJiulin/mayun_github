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
	void CreatFood();					//�������ʳ��
	void CreatMap();						//��ʼ���߿�
	void OutputMap();					//��ӡ��ͼ
	void CreatObstruction();			//��������ϰ���
	void Hide_or_show_Cursor(int x);				//0��ʾ���أ�1��ʾ��ʾ���
	void gotoxy(int x, int y, COORD &coor);				//��λ��꺯��
	short getWidth();					//��ȡ���ڴ�С
	void moving(char keyboard, COORD &coor,bool &judge);		//���ݴӼ�������ķ������ƶ���
	int GameMenu( COORD &coor);		//��ӡ��Ϸ�˵�
	void Choose(char tmp, COORD &coor);  //ѡ����
	void EndGame( COORD &coor);  //������Ϸ
	void StartGame(COORD &coor,bool &judge);   //��ʼ��Ϸ����
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

