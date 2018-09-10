#pragma once
#include"SnakeNode.h"
const int Size_1 = 25;    //头文件中最好不要数据定义，否则可能会在编译时重复定义
											//
class Snake				//Snake为一条蛇 类中存储着蛇的头和尾
{
public:
	Snake();
	~Snake();
	void AddNode(int x, int y, char Map_1[][Size_1]);    //吃到食物时调用该函数
	void DeleteTail(char Map_1[][Size_1]);						//同上
	SnakeNode* getHead();
	SnakeNode* getTail();
	int getLength();
private:
	SnakeNode * m_pHead;
	SnakeNode *m_pTail;
	int m_iLength;
};

