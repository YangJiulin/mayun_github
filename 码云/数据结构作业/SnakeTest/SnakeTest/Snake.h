#pragma once
#include"SnakeNode.h"
const int Size_1 = 25;    //ͷ�ļ�����ò�Ҫ���ݶ��壬������ܻ��ڱ���ʱ�ظ�����
											//
class Snake				//SnakeΪһ���� ���д洢���ߵ�ͷ��β
{
public:
	Snake();
	~Snake();
	void AddNode(int x, int y, char Map_1[][Size_1]);    //�Ե�ʳ��ʱ���øú���
	void DeleteTail(char Map_1[][Size_1]);						//ͬ��
	SnakeNode* getHead();
	SnakeNode* getTail();
	int getLength();
private:
	SnakeNode * m_pHead;
	SnakeNode *m_pTail;
	int m_iLength;
};

