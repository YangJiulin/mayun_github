#include"Game.h"
//void gotoxy(int x, int y, COORD &coor)     //��λ��꺯��
//{
//	coor.X = x;
//	coor.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
//}
//void Hide_or_show_Cursor(int x)       //0��ʾ���أ�1��ʾ��ʾ
//{
//	CONSOLE_CURSOR_INFO cursor_info;
//	cursor_info = { 1,x };
//	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
//}

int main()
{
	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);*/
	SetConsoleTitle("̰����");
	Game *g = new Game;
	g->Hide_or_show_Cursor(0);
	bool continue_or_end = false;      //�����ж�game over���Ƿ����
	g->CreatMap();
	/*g->CreatObstruction();*/
	g->StartGame(g->coor, continue_or_end);		//��game over�󲢰�enter��ʱcontinue_or_end��Ϊture
																					//Ȼ��ִ����һ��������esc���ֱ���˳�
	while (continue_or_end)
	{
		delete g;										//������һ����Ϸ
		system("cls");
		g = new Game;												//��ʼ����Ϸ
		continue_or_end = false;
		g->CreatMap();
		/*g->Hide_or_show_Cursor(1);*/	
		g->CreatObstruction();       //ѡ����ʱ�����֣������ƶ�ʱ������أ�������һ����
		g->StartGame(g->coor, continue_or_end);		
	}
	delete g;
	return 0;
}