#include"Game.h"
//void gotoxy(int x, int y, COORD &coor)     //定位光标函数
//{
//	coor.X = x;
//	coor.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
//}
//void Hide_or_show_Cursor(int x)       //0表示隐藏，1表示显示
//{
//	CONSOLE_CURSOR_INFO cursor_info;
//	cursor_info = { 1,x };
//	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
//}

int main()
{
	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);*/
	SetConsoleTitle("贪吃蛇");
	Game *g = new Game;
	g->Hide_or_show_Cursor(0);
	bool continue_or_end = false;      //用于判断game over后是否继续
	g->CreatMap();
	/*g->CreatObstruction();*/
	g->StartGame(g->coor, continue_or_end);		//当game over后并按enter键时continue_or_end才为ture
																					//然后执行下一步，若按esc则会直接退出
	while (continue_or_end)
	{
		delete g;										//结束上一个游戏
		system("cls");
		g = new Game;												//开始新游戏
		continue_or_end = false;
		g->CreatMap();
		/*g->Hide_or_show_Cursor(1);*/	
		g->CreatObstruction();       //选择功能时光标出现，蛇在移动时光标隐藏，避免闪一闪的
		g->StartGame(g->coor, continue_or_end);		
	}
	delete g;
	return 0;
}