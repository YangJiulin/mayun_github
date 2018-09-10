#pragma once
#include<iostream>
using namespace std;
class SnakeNode				//蛇的每一个结点
{
public:
	SnakeNode();
	~SnakeNode();
	int m_iX;
	int m_iY;
	SnakeNode *m_pNextNode;
	SnakeNode *m_pLastNode;
};
