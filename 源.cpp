#include <iostream>
#include <conio.h>
using namespace std;

bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
char MAP[20][60];
int MAPTool[20][60];

void display();
class Robot
{
private:
	int id;
	char symbol;
	std::pair<int, int> locationr;

public:
	Robot(int x, int y, int id, char symbol);
	void RobotBoom(int id);
	void update_location(int x, int y);
	std::pair<int, int> get_location();
};

Robot::Robot(int x, int y, int theid, char symbol)
{
	id = theid;
	locationr.first = x;
	locationr.second = y;
	symbol = symbol;
}
void Robot::update_location(int x, int y)
{
	locationr.first = x;
	locationr.second = y;
}


class Player
{
private:

	std::pair<int, int> location;

public:
	char symbol;
	int speed;
	Player(int x, int y);
	void update_location(int type);
	std::pair<int, int> get_location();
};

class Bomb
{
private:
	std::pair<int, int> location;
public:
	int level;
	Bomb(int x, int y, int le);
	void afterboom();
	void bomb_picture(int type);
	void update_location(int t, int y);
	std::pair<int, int> get_location();

};

Bomb::Bomb(int x, int y, int le)
{
	location.first = x;
	location.second = y;
	level = le;
}

std::pair<int, int> Bomb::get_location()
{
	return location;
}
void Bomb::bomb_picture(int type)
{
	MAP[location.first][location.second] = 'O';
	if (MAP[location.first - 1][location.second] != '#')
	{
		MAP[location.first - 1][location.second] = '~';
	}
	if (MAP[location.first + 1][location.second] != '#')
	{
		MAP[location.first + 1][location.second] = '~';
	}
	if (MAP[location.first][location.second + 1] != '#')
	{
		MAP[location.first][location.second + 1] = '~';
	}
	if (MAP[location.first][location.second - 1] != '#')
	{
		MAP[location.first][location.second - 1] = '~';
	}
}
void Bomb::update_location(int x, int y)
{
	location.first = x;
	location.second = y;
}
void Bomb::afterboom()
{
	MAP[location.first][location.second] = ' ';
	if (MAP[location.first - 1][location.second] == '~')
	{
		if (MAPTool[location.first - 1][location.second] == 1)
		{
			MAP[location.first - 1][location.second] = '1';
		}
		else if (MAPTool[location.first - 1][location.second] == 2)
		{
			MAP[location.first - 1][location.second] = '2';
		}
		else
		{
			MAP[location.first - 1][location.second] = ' ';
		}
	}
	if (MAP[location.first + 1][location.second] == '~')
	{
		if (MAPTool[location.first + 1][location.second] == 1)
		{
			MAP[location.first + 1][location.second] = '1';
		}
		else if (MAPTool[location.first + 1][location.second] == 2)
		{
			MAP[location.first + 1][location.second] = '2';
		}
		else
		{
			MAP[location.first + 1][location.second] = ' ';
		}
	}
	if (MAP[location.first][location.second - 1] == '~')
	{
		if (MAPTool[location.first][location.second - 1] == 1)
		{
			MAP[location.first][location.second - 1] = '1';
		}
		else if (MAPTool[location.first][location.second - 1] == 2)
		{
			MAP[location.first][location.second - 1] = '2';
		}
		else
		{
			MAP[location.first][location.second - 1] = ' ';
		}
	}
	if (MAP[location.first][location.second + 1] == '~')
	{
		if (MAPTool[location.first][location.second + 1] == 1)
		{
			MAP[location.first][location.second + 1] = '1';
		}
		else if (MAPTool[location.first][location.second + 1] == 2)
		{
			MAP[location.first][location.second + 1] = '2';
		}
		else
		{
			MAP[location.first][location.second + 1] = ' ';
		}
	}
}
Player::Player(int x, int y)
{
	location.first = x;
	location.second = y;
}

std::pair<int, int> Player::get_location()
{
	return location;
}
void Player::update_location(int type)
{
	if (type == 1)
	{
		location.first = location.first - 1;
	}
	else if (type == 2)
	{
		location.second = location.second - 1;
	}
	else if (type == 3)
	{
		location.first = location.first + 1;
	}
	else if (type == 4)
	{
		location.second = location.second + 1;
	}
}
Player player1(9, 5);
Player player2(9, 55);

Robot r1(1, 30, 1, 'R');
Robot r2(18, 30, 2, 'R');
Bomb bomb1(0, 0, 1);
Bomb bomb2(0, 0, 1);
Bomb rboom1(0, 0, 1);
Bomb rboom2(0, 0, 1);

void Robot::RobotBoom(int id)
{
	int dir = rand() % 4;
	// cout << dir << endl;
	if (dir == 0)
	{
		if (MAP[locationr.first - 1][locationr.second] == ' ')
		{
			MAP[locationr.first - 1][locationr.second] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first - 1, locationr.second);
		}
		else if (MAP[locationr.first - 1][locationr.second] == '*' && locationr.first < 18 && MAP[locationr.first + 1][locationr.second] == ' ' && MAP[locationr.first + 2][locationr.second] == ' ')
		{
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first + 2][locationr.second] = 'R';
			if (id == 1 && flag3 == 0)
			{
				rboom1.update_location(locationr.first - 1, locationr.second);
				flag3 = 1;
			}
			else if (id == 2 && flag4 == 0)
			{
				rboom2.update_location(locationr.first - 1, locationr.second);
				flag4 = 1;
			}
			update_location(locationr.first + 2, locationr.second);
		}
	}
	else if (dir == 1)
	{
		if (MAP[locationr.first + 1][locationr.second] == ' ')
		{
			MAP[locationr.first + 1][locationr.second] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first + 1, locationr.second);
		}
		else if (MAP[locationr.first + 1][locationr.second] == '*' && (locationr.first > 2 && MAP[locationr.first - 1][locationr.second] == ' ' && MAP[locationr.first - 2][locationr.second] == ' '))
		{
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first - 2][locationr.second] = 'R';
			if (id == 1 && flag3 == 0)
			{

				rboom1.update_location(locationr.first + 1, locationr.second);
				flag3 = 1;
			}
			else if (id == 2 && flag4 == 0)
			{

				rboom2.update_location(locationr.first + 1, locationr.second);
				flag4 = 1;
			}
			update_location(locationr.first - 2, locationr.second);
		}
	}
	else if (dir == 2)
	{
		if (MAP[locationr.first][locationr.second - 1] == ' ')
		{
			MAP[locationr.first][locationr.second - 1] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second - 1);
		}
		else if (MAP[locationr.first][locationr.second - 1] == '*' && locationr.second < 58 && MAP[locationr.first][locationr.second + 1] == ' ' && MAP[locationr.first][locationr.second + 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second + 2] = 'R';
			if (id == 1 && flag3 == 0)
			{
				rboom1.update_location(locationr.first, locationr.second - 1);
				flag3 = 1;
			}
			else if (id == 2 && flag4 == 0)
			{
				rboom2.update_location(locationr.first, locationr.second - 1);
				flag4 = 1;
			}
			update_location(locationr.first, locationr.second + 2);
		}
	}
	else if (dir == 3)
	{
		if (MAP[locationr.first][locationr.second + 1] == ' ')
		{
			MAP[locationr.first][locationr.second + 1] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second + 1);
		}
		else if (MAP[locationr.first][locationr.second + 1] == '*' && locationr.second > 2 && MAP[locationr.first][locationr.second - 1] == ' ' && MAP[locationr.first][locationr.second - 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second - 2] = 'R';
			if (id == 1 && flag3 == 0)
			{
				rboom1.update_location(locationr.first, locationr.second);
				flag3 = 1;
			}
			else if (id == 2 && flag4 == 0)
			{
				rboom2.update_location(locationr.first, locationr.second);
				flag4 = 1;
			}
			update_location(locationr.first, locationr.second - 2);
		}
	}
}
void Initmap()
{
	memset(MAP, ' ', sizeof(MAP));
	int locx = 0;
	int locy = 0;
	int tool = 0;
	for (int i = 0; i < 20; i += 2)
	{
		for (int j = 0; j < 60; j += 2)
		{
			MAP[i][j] = '#';
		}
	}
	for (int i = 0; i < 500; i++)
	{
		locx = rand() % 19;
		locy = rand() % 59;
		if (MAP[locx][locy] != '#')
		{
			MAP[locx][locy] = '*';
		}
		if (tool % 3 == 0)
		{
			MAPTool[locx][locy] = 1;
		}
		else if (tool % 4 == 0)
		{
			MAPTool[locx][locy] = 2;
		}
		tool++;
	}
	for (int i = 0; i < 20; i++)
	{
		MAP[i][0] = '#';
		MAP[i][59] = '#';
	}
	for (int i = 0; i < 60; i++)
	{
		MAP[0][i] = '#';
		MAP[19][i] = '#';
	}
	MAP[9][5] = 'A';
	MAP[9][55] = 'B';
	MAP[1][30] = 'R';
	MAP[18][30] = 'R';
	return;
}

void deal_with_input(char ch)
{
	std::pair<int, int> p = player1.get_location();
	std::pair<int, int> p2 = player2.get_location();
	if (ch == ' ' && flag1 == 0)
	{
		bomb1.update_location(p.first, p.second);
		flag1 = 1;
	}
	else if (ch == 13 && flag2 == 0)
	{
		bomb2.update_location(p2.first, p2.second);
		flag2 = 1;
	}
	else
	{
		int speed1 = player1.speed;
		while (speed1 > 0)
		{
			speed1--;
			if (ch == 'W')
			{

				if (p.first > 0 && MAP[p.first - 1][p.second] != '#' && MAP[p.first - 1][p.second] != '*')
				{
					if (MAP[p.first - 1][p.second] == '1')
					{
						player1.speed++;
						MAPTool[p.first - 1][p.second] = 0;
					}
					else if (MAP[p.first - 1][p.second] == '2')
					{
						bomb1.level++;
						MAPTool[p.first - 1][p.second] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first - 1][p.second] = 'A';
					player1.update_location(1);
				}
			}
			else if (ch == 'A')
			{
				if (p.second > 0 && MAP[p.first][p.second - 1] != '*' && MAP[p.first][p.second - 1] != '#')
				{
					if (MAP[p.first][p.second - 1] == '1')
					{
						player1.speed++;
						MAPTool[p.first][p.second - 1] = 0;
					}
					else if (MAP[p.first][p.second - 1] == '2')
					{
						bomb1.level++;
						MAPTool[p.first][p.second - 1] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first][p.second - 1] = 'A';
					player1.update_location(2);
				}
			}
			else if (ch == 'S')
			{
				if (p.first < 19 && MAP[p.first + 1][p.second] != '*' && MAP[p.first + 1][p.second] != '#')
				{
					if (MAP[p.first + 1][p.second] == '1')
					{
						player1.speed++;
						MAPTool[p.first + 1][p.second] = 0;
					}
					else if (MAP[p.first + 1][p.second] == '2')
					{
						bomb1.level++;
						MAPTool[p.first + 1][p.second] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first + 1][p.second] = 'A';
					player1.update_location(3);
				}
			}
			else if (ch == 'D')
			{
				if (p.second < 59 && MAP[p.first][p.second + 1] != '*' && MAP[p.first][p.second + 1] != '#')
				{
					if (MAP[p.first][p.second + 1] == '1')
					{
						player1.speed++;
						MAPTool[p.first][p.second + 1] = 0;
					}
					else if (MAP[p.first][p.second + 1] == '2')
					{
						bomb1.level++;
						MAPTool[p.first][p.second + 1] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first][p.second + 1] = 'A';
					player1.update_location(4);
				}
			}
		}
	}
	int speed2 = player2.speed;
	while (speed2 > 0)
	{
		speed2--;
		if (ch == 'I')
		{
			if (p2.first > 0 && MAP[p2.first - 1][p2.second] != '*' && MAP[p2.first - 1][p2.second] != '#')
			{
				if (MAP[p2.first - 1][p2.second] == '1')
				{
					player2.speed++;
					MAPTool[p2.first - 1][p2.second] = 0;
				}
				else if (MAP[p2.first - 1][p2.second] == '2')
				{
					bomb2.level++;
					MAPTool[p2.first - 1][p2.second] = 0;
				}
				MAP[p2.first][p2.second] = ' ';
				MAP[p2.first - 1][p2.second] = 'B';
				player2.update_location(1);
			}
		}
		else if (ch == 'J')
		{
			if (p2.second > 0 && MAP[p2.first][p2.second - 1] != '*' && MAP[p2.first][p2.second - 1] != '#')
			{
				if (MAP[p2.first][p2.second - 1] == '1')
				{
					player2.speed++;
					MAPTool[p2.first][p2.second - 1] = 0;
				}
				else if (MAP[p2.first][p2.second - 1] == '2')
				{
					bomb2.level++;
					MAPTool[p2.first][p2.second - 1] = 0;
				}
				MAP[p2.first][p2.second] = ' ';
				MAP[p2.first][p2.second - 1] = 'B';
				player2.update_location(2);
			}
		}
		else if (ch == 'K')
		{
			if (p2.first < 19 && MAP[p2.first + 1][p2.second] != '*' && MAP[p2.first + 1][p2.second] != '#')
			{
				if (MAP[p2.first + 1][p2.second] == '1')
				{
					player2.speed++;
					MAPTool[p2.first + 1][p2.second] = 0;
				}
				else if (MAP[p2.first + 1][p2.second] == '2')
				{
					bomb2.level++;
					MAPTool[p2.first + 1][p2.second] = 0;
				}
				MAP[p2.first][p2.second] = ' ';
				MAP[p2.first + 1][p2.second] = 'B';
				player2.update_location(3);
			}
		}
		else if (ch == 'L')
		{
			if (p2.second < 59 && MAP[p2.first][p2.second + 1] != '*' && MAP[p2.first][p2.second + 1] != '#')
			{
				if (MAP[p2.first][p2.second + 1] == '1')
				{
					player2.speed++;
					MAPTool[p2.first][p2.second + 1] = 0;
				}
				else if (MAP[p2.first][p2.second + 1] == '2')
				{
					bomb2.level++;
					MAPTool[p2.first][p2.second + 1] = 0;
				}
				MAP[p2.first][p2.second] = ' ';
				MAP[p2.first][p2.second + 1] = 'B';
				player2.update_location(4);
			}
		}
	}
}
	void PrintAll()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 60; j++)
			{
				printf("%c", MAP[i][j]);
			}
			printf("\n");
		}
	}
	void display()
	{
		system("cls");
		PrintAll();
	}
	void deal_with_time(int time)
	{
		if (time % 7 == 0)
		{
			r1.RobotBoom(1);
			r2.RobotBoom(2);
			display();
		}
		if (time % 3 == 0)
		{
			if (flag1 == 1)
				bomb1.bomb_picture(1), flag1 = 0, display();
			if (flag2 == 1)
				bomb2.bomb_picture(1), flag2 = 0, display();
			if (flag3 == 1)
				rboom1.bomb_picture(1), flag3 = 0, display();
			if (flag4 == 1)
				rboom2.bomb_picture(1), flag4 = 0, display();

		}
		if (flag1 == 0)
		{
			bomb1.afterboom();
		}
		if (flag2 == 0)
		{
			bomb2.afterboom();
		}
		if (flag3 == 0)
		{
			rboom1.afterboom();
		}
		if (flag4 == 0)
		{
			rboom2.afterboom();
		}
	}

	int main()
	{
		player1.symbol = 'A';
		player2.symbol = 'B';
		player1.speed = 1;
		player2.speed = 1;
		Initmap();
		PrintAll();
		int count = 1;
		int times = 0;
		bool onetime = 0;
		while (1)
		{
			char ch;
			if (count == 9000000)
			{
				if (_kbhit())
				{
					// cout <<"here";
					ch = _getch();
					if (ch == 27)
						break;
					deal_with_input(ch);
					display();
				}
				times++;
				deal_with_time(times);
				count = 0;
			}
			count++;
		}
		return 0;
	}
