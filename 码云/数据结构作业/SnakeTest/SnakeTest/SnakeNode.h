#pragma once
#include<iostream>
using namespace std;
class SnakeNode				//�ߵ�ÿһ�����
{
public:
	SnakeNode();
	~SnakeNode();
	int m_iX;
	int m_iY;
	SnakeNode *m_pNextNode;
	SnakeNode *m_pLastNode;
};
