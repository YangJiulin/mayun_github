#include "Snake.h"
Snake::Snake()
{
	m_pHead = m_pTail = NULL;
	m_iLength = 0;
}

Snake::~Snake()
{
}

void Snake::AddNode(int x, int y, char Map_1[][Size_1])
{
	Map_1[x][y] = '$';
	m_iLength++;
	SnakeNode *Food = new SnakeNode;
	Food->m_iX = x, Food->m_iY = y;
	Food->m_pNextNode = m_pHead;
	Food->m_pLastNode = NULL;
	if (m_pHead)
	{
		m_pHead->m_pLastNode = Food;
	}
	m_pHead = Food;
	if (!m_pTail)
	{
		m_pTail = m_pHead;
	}
	if (m_pHead->m_pNextNode) {
		Map_1[m_pHead->m_pNextNode->m_iX][m_pHead->m_pNextNode->m_iY] = '*';
	}
}

void Snake::DeleteTail(char Map_1[][Size_1])
{
	m_iLength--;
	Map_1[m_pTail->m_iX][m_pTail->m_iY] = ' ';
	SnakeNode *tmp = m_pTail;
	m_pTail = m_pTail->m_pLastNode;
	m_pTail->m_pNextNode = NULL;
	delete tmp;
}

SnakeNode * Snake::getHead()
{
	return m_pHead;
}

SnakeNode * Snake::getTail()
{
	return m_pTail;
}

int Snake::getLength()
{
	return m_iLength;
}
