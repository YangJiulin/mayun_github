#include "Game.h"

Game::Game()
{
	m_pSnake = new Snake;
	m_iFood_x = 0;
	m_iFood_y = 0;
	m_iScore = 0;
	m_iLeave = 1;
}

Game::~Game()
{
	delete m_pSnake;
}

void Game::CreatFood()
{
	srand((unsigned int)time(NULL));
	do {
		m_iFood_x = rand() % (Size - 2) + 1;
		m_iFood_y = rand() % (Size - 2) + 1;
	} while (Map[m_iFood_x][m_iFood_y] == '*');
	Map[m_iFood_x][m_iFood_y] = '*';
}

void Game::CreatMap()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if ((i == 0) || (j == 0) || (i == Size - 1) || (j == Size - 1))
			{
				Map[i][j] = '#';
			}
			else
			{
				Map[i][j] = ' ';
			}
		}
	}
}

void Game::OutputMap()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cout << Map[i][j] << " ";
		}
		if (i == 3){
			cout << "╭————╮";
		} 
		if (i == 4){
			cout << "│" << "成绩: " << m_iScore << " │";
		}
		if (i == 5){
			cout << "╰————╯";
		}
		if (i == 7){
			cout << "╭————╮";
		}
		if (i == 8){
			cout << "│" << "等级: " << getLeave() << " │";
		}
		if (i == 9){
			cout << "╰————╯";
		}
		if (i == 10)
		{
			cout << "最高纪录:" << getHighestScore();
		}
		if (i == 16){
			cout << "w:向上移动   s:向下移动   空格:暂停";
		}
		if (i == 17) {
			cout << "a:向左移动  d:向右移动 ";
		}
		cout << endl;
	}
}

void Game::CreatObstruction()
{
	for (int i = 0; i < 3; i++) {
		int place_x = 1, place_y = 1;				//障碍物坐标
		do {
			place_x = rand() % (Size - 2) + 1;
			place_y = rand() % (Size - 2) + 1;
		} while (Map[place_x][place_y] == '*');
		Map[place_x][place_y] = '#';
		if (i == 0) {
			for (int j = 0; j < 8; j++)
			{
				if (Map[place_x++][(place_y++) % (Size - 2) + 1] == ' ')
				{
					Map[place_x][place_y] = '#';
				}
			}
		}
		else if (i == 1)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Map[place_x][(place_y++) % (Size - 2) + 1] == ' ')
				{
					Map[place_x][place_y] = '#';
				}
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				if (Map[place_x++][(place_y) % (Size - 2) + 1] == ' ')
				{
					Map[place_x][place_y] = '#';
				}
			}
		}
	}
}

void Game::Hide_or_show_Cursor(int x)
{
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info = { 1,x };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Game::gotoxy(int x, int y, COORD & coor)
{
coor.X = x;
coor.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

short Game::getWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;     
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.srWindow.Right;
}

void Game::moving(char keyboard, COORD &coor,bool &judge)
{
	SnakeNode *tmp = m_pSnake->getHead();
	int next_x = tmp->m_iX;
	int next_y = tmp->m_iY;
	switch (keyboard)
	{
	case'w':next_x--; break;
	case's':next_x++; break;
	case'a':next_y--; break;
	case'd':next_y++; break;
	}
	if (m_iLeave >= 2)   //级别大于3则可以穿墙
	{
		if (next_x == 0)
		{
			next_x = Size - 2;
		}
		if (next_y == 0)
		{
			next_y = Size - 2;
		}
		if (next_x == Size - 1)
		{
			next_x = 1;
		}
		if (next_y == Size - 1)
		{
			next_y = 1;
		}
	}
	if ((next_x == m_pSnake->getHead()->m_pNextNode->m_iX) && (next_y == m_pSnake->getHead()->m_pNextNode->m_iY))
	{
		return;
	}
	else if (next_x == tmp->m_iX&& next_y == tmp->m_iY)
	{
		return;
	}
	else if ((next_x == 0 || next_x == Size - 1 || next_y == 0 || next_y == Size - 1)
		|| (Map[next_x][next_y] != ' '&&next_x != m_iFood_x && next_y != m_iFood_y))
	{
		system("cls");
		if (m_iScore > getHighestScore())
		{
			gotoxy(10, 9, coor);
			cout << "恭喜你创造了新纪录";
			setHighestScore(m_iScore);
		}
		gotoxy(10, 10, coor);
		cout << "game over!" << endl;
		gotoxy(10, 11, coor);
		cout << "按esc退出,按其它继续，";
		char tmp_1 = _getwch();
		if (tmp_1 == 27) {
			EndGame(coor);
			exit(0);
		}
		else
		 {
		   judge = true;
		   return;
		 }
	}
	else if (next_x == m_iFood_x && next_y == m_iFood_y)
	{
		m_pSnake->AddNode(next_x, next_y, Map);
		m_iScore++;
		m_iLeave =1+ m_iScore / 10;
		CreatFood();
	}
	else
	{
		m_pSnake->AddNode(next_x, next_y, Map);
		m_pSnake->DeleteTail(Map);
	}
	return;
}

int  Game::GameMenu(COORD &coor)
{
	short width = getWidth()/2;
	gotoxy(width-5, 3, coor);
	cout << "欢迎你来到贪吃蛇游戏";
	gotoxy(width - 2, 5, coor);
	cout << "●游戏菜单●"<< endl;
	gotoxy(width - 2, 6, coor);
	cout << "开始新游戏" << endl;
	gotoxy(width - 2, 7, coor);
	cout << "继续游戏" << endl;
	gotoxy(width - 2, 8, coor);
	cout << "退出游戏" << endl;
	gotoxy(width - 3,6 , coor);
	cout << ">";
	return 0;
}

void Game::Choose(char tmp, COORD &coor)				
{
	short width = getWidth() / 2;
	int y = coor.Y;
	switch (tmp)
	{
	case'w':
		gotoxy(width - 3, y, coor);
		cout << " ";
		y--;
		if (y >= 6 && y<= 8) {      //当光标处于菜单所在行数之内时才移动光标
			gotoxy(width - 3, y, coor);
			cout << ">";
		}
		else
		{
			y++;
			gotoxy(width - 3, y, coor);
			cout << ">";
		}
		break;
	case's':
		gotoxy(width - 3, y, coor);
		cout << " ";
		y++;
		if (y >= 6 && y <= 8) {      //当光标处于菜单所在行数之内时才移动光标
			gotoxy(width-3, y, coor);
			cout << ">";
		}
		else
		{
			y--;
			gotoxy(width - 3, y, coor);
			cout << ">";
		}
		break;
	default:
		y = 0;
		break;
	}
}

void Game::EndGame(COORD &coor)
{
	    short width = getWidth() / 2;
		system("cls");
		gotoxy(width-2, 8, coor);
		cout << "已退出游戏" << endl;
		exit(0);
}

void Game::StartGame(COORD & coor,bool &judge)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	GameMenu(coor);
	char tmp;
	do
	{
		tmp = _getwch();
		Choose(tmp,coor);
	} while (tmp != '\r');
	if (coor.Y == 6) {
		system("cls");
		/*Hide_or_show_Cursor(0);*/
		coor.X = coor.Y = 0;
		m_pSnake->AddNode(4, 4, Map);      //初始化蛇
		m_pSnake->AddNode(4, 5, Map);
		m_pSnake->AddNode(4, 6, Map);
		CreatFood();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		OutputMap();
		while (!judge)
		{
			bool add_judge = true;  //判断是否添加障碍物（大于3级时只需添加一次）
			int tmp_speed;
			char keyboard = _getwch();
			if (keyboard == ' ')
			{
				system("cls");
				cout << " 游戏已暂停";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
				GameMenu(coor);
				/*Hide_or_show_Cursor(1);*/
				do
				{
					tmp = _getwch();
					Choose(tmp, coor);
				} while (tmp != '\r');

				if (coor.Y == 8)
				{
					if (m_iScore > getHighestScore())
					{
						setHighestScore(m_iScore);
					}
					EndGame(coor);
				}
				if (coor.Y == 6)
				{
					if (m_iScore > getHighestScore())
					{
						setHighestScore(m_iScore);
					}
					judge = true;
					break;
				}
				if (coor.Y == 7)
				{
					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
					OutputMap();
					/*Hide_or_show_Cursor(0);*/
					keyboard = _getwch();
				}
			}
			while (!_kbhit())
			{
				Hide_or_show_Cursor(0);
				gotoxy(0, 0, coor);
				moving(keyboard, coor,judge);
				if (judge)
				{
					break;
				}
				if (add_judge&&m_iLeave >= 3)
				{
					CreatObstruction();
					add_judge = false;
				}
				OutputMap();
				if ((900 - getLeave() * 100) >= 200)
				{
					tmp_speed = 900 - getLeave() * 100;
				}
				Sleep(tmp_speed);
			}
		}
	}
	else if (coor.Y == 8)
	{
		cout << endl;
		exit(0);
	}
	else
	{
		cout << endl << endl;
	}
}

int Game::getSnakeLength()
{
	return m_pSnake->getLength();
}

int Game::getLeave()
{
	return m_iLeave;
}

int Game::getHighestScore()
{
	ifstream in("HighestScore.txt");
	int tmp;
	in >> tmp;
	in.close();
	return tmp;
}

void Game::setHighestScore(int score)
{
	ofstream out("HighestScore.txt");
	out << score;
	out.close();
}



Snake * Game::getSnake()
{
	return m_pSnake;
}
