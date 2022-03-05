#include <iostream>
#include <conio.h>
using namespace std;

bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
char MAP[21][60];
int MAPTool[21][60];

void display();
class Robot
{
private:
	
	char symbol;
	std::pair<int, int> locationr;

public:
	int dir;
    int id;
	Robot(int x, int y, char symbol);
	void RobotBoom(int id);
	void update_location(int x, int y);
	std::pair<int, int> get_location();
};

Robot::Robot(int x, int y, char symbol)
{
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
	int speedsecond;
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
	int state;
	Bomb(int x, int y);
	void afterboom();
	void bomb_picture(int type);
	void update_location(int t, int y);
	std::pair<int, int> get_location();

};

Bomb::Bomb(int x, int y)
{
	location.first = x;
	location.second = y;
}

std::pair<int, int> Bomb::get_location()
{
	return location;
}
void Bomb::bomb_picture(int lev)
{
	MAP[location.first][location.second] = 'O';
	for (int i = 1; i <= level; i++)
	{
		if (MAP[location.first - i][location.second] != '#')
		{
			MAP[location.first - i][location.second] = '~';
		}
		if (MAP[location.first + i][location.second] != '#')
		{
			MAP[location.first + i][location.second] = '~';
		}
		if (MAP[location.first][location.second + i] != '#')
		{
			MAP[location.first][location.second + i] = '~';
		}
		if (MAP[location.first][location.second - i] != '#')
		{
			MAP[location.first][location.second - i] = '~';
		}
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
	for (int i = 1; i <= level; i++)
	{
		if (MAP[location.first - i][location.second] == '~')
		{
			if (MAPTool[location.first - i][location.second] == 1)
			{
				MAP[location.first - i][location.second] = '1';
			}
			else if (MAPTool[location.first - i][location.second] == 2)
			{
				MAP[location.first - i][location.second] = '2';
			}
			else
			{
				MAP[location.first - i][location.second] = ' ';
			}
		}
		if (MAP[location.first + i][location.second] == '~')
		{
			if (MAPTool[location.first + i][location.second] == 1)
			{
				MAP[location.first + 1][location.second] = '1';
			}
			else if (MAPTool[location.first + i][location.second] == 2)
			{
				MAP[location.first + i][location.second] = '2';
			}
			else
			{
				MAP[location.first + i][location.second] = ' ';
			}
		}
		if (MAP[location.first][location.second - i] == '~')
		{
			if (MAPTool[location.first][location.second - i] == 1)
			{
				MAP[location.first][location.second - i] = '1';
			}
			else if (MAPTool[location.first][location.second - i] == 2)
			{
				MAP[location.first][location.second - i] = '2';
			}
			else
			{
				MAP[location.first][location.second - i] = ' ';
			}
		}
		if (MAP[location.first][location.second + i] == '~')
		{
			if (MAPTool[location.first][location.second + i] == 1)
			{
				MAP[location.first][location.second + i] = '1';
			}
			else if (MAPTool[location.first][location.second + 1] == 2)
			{
				MAP[location.first][location.second + i] = '2';
			}
			else
			{
				MAP[location.first][location.second + i] = ' ';
			}
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
Robot r1(1, 30, 'R');
Robot r2(19, 30,'R');
Bomb bomb1(0, 0);
Bomb bomb2(0, 0);
Bomb rboom1(0, 0);
Bomb rboom2(0, 0);

void Robot::RobotBoom(int id)
{
	int direction = rand() % 5;
	if (dir)
		direction = dir;
	// cout << "!!" << dir << " " << direction;
	if (direction == 1)
	{
		if (MAP[locationr.first - 1][locationr.second] == ' ')
		{;
			MAP[locationr.first - 1][locationr.second] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first - 1, locationr.second);
			dir = 0;
			display();
		}
		else if ((rboom2.state == 4 || rboom1.state == 4) && MAP[locationr.first - 1][locationr.second] == '*' && locationr.first < 18 && MAP[locationr.first + 1][locationr.second] == ' ' && MAP[locationr.first + 2][locationr.second] == ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			dir = 1;
			if (id == 1 && rboom1.state == 4)
			{
				rboom1.update_location(locationr.first, locationr.second);
				rboom1.state = 3;

			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
			}
			MAP[locationr.first + 1][locationr.second] = 'R';
			update_location(locationr.first + 1, locationr.second);
			display();
		}
	}
	else if (direction == 2)
	{
		if (MAP[locationr.first + 1][locationr.second] == ' ')
		{
			MAP[locationr.first + 1][locationr.second] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first + 1, locationr.second);
			dir = 0;
			display();
		}
		else if ((rboom2.state == 4 || rboom1.state == 4) && MAP[locationr.first + 1][locationr.second] == '*' && (locationr.first > 2 && MAP[locationr.first - 1][locationr.second] == ' ' && MAP[locationr.first - 2][locationr.second] == ' '))
		{
			MAP[locationr.first][locationr.second] = 'o';
			dir = 2;
			if (id == 1 && rboom1.state == 4)
			{
				rboom1.update_location(locationr.first, locationr.second);
				rboom1.state = 3;
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
			}
			MAP[locationr.first - 1][locationr.second] = 'R';
			update_location(locationr.first - 1, locationr.second);
			display();
		}
	}
	else if (direction == 3)
	{
		if (MAP[locationr.first][locationr.second - 1] == ' ')
		{
			MAP[locationr.first][locationr.second - 1] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second - 1);
			dir = 0;
			display();
		}
		else if ((rboom2.state == 4 || rboom1.state == 4) && MAP[locationr.first][locationr.second - 1] == '*' && locationr.second < 58 && MAP[locationr.first][locationr.second + 1] == ' ' && MAP[locationr.first][locationr.second + 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			dir = 3;
			if (id == 1 && rboom1.state == 4)
			{
				rboom1.update_location(locationr.first, locationr.second);
				rboom1.state = 3;

			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
			}
			MAP[locationr.first][locationr.second + 1] = 'R';
			update_location(locationr.first, locationr.second + 1);
			display();
		}
	}
	else if (direction == 4)
	{
		if (MAP[locationr.first][locationr.second + 1] == ' ')
		{
			MAP[locationr.first][locationr.second + 1] = 'R';
			MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second + 1);
			dir = 0;
			display();
		}
		else if ((rboom2.state == 4 || rboom1.state == 4 ) &&  MAP[locationr.first][locationr.second + 1] == '*' && locationr.second > 2 && MAP[locationr.first][locationr.second - 1] == ' ' && MAP[locationr.first][locationr.second - 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			dir = 4;
			if (id == 1 && rboom1.state == 4)
			{
				rboom1.update_location(locationr.first, locationr.second);
				rboom1.state = 3;
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
			}
			MAP[locationr.first][locationr.second - 1] = 'R';
			update_location(locationr.first, locationr.second - 1);
			display();
		}
	}
}
void Initmap()
{
	memset(MAP, ' ', sizeof(MAP));
	int locx = 0;
	int locy = 0;
	int tool = 0;
	for (int i = 0; i < 21; i += 2)
	{
		for (int j = 0; j < 60; j += 2)
		{
			MAP[i][j] = '#';
		}
	}
	for (int i = 0; i < 500; i++)
	{
		locx = rand() % 20;
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
	for (int i = 0; i < 21; i++)
	{
		MAP[i][0] = '#';
		MAP[i][59] = '#';
	}
	for (int i = 0; i < 60; i++)
	{
		MAP[0][i] = '#';
		MAP[20][i] = '#';
	}
	MAP[9][5] = 'A';
	MAP[9][55] = 'B';
	MAP[1][30] = 'R';
	MAP[19][30] = 'R';
	return;
}

void deal_with_input(char ch)// ´¦Àí¼üÅÌÊäÈë
{
	std::pair<int, int> p = player1.get_location();
	std::pair<int, int> p2 = player2.get_location();
	if (ch == ' ' && bomb1.state == 4)
	{
		bomb1.update_location(p.first, p.second);
		bomb1.state = 3;
		MAP[p.first][p.second] = 'o';
	}
	else if (ch == 13 && bomb2.state == 4)
	{
		bomb2.update_location(p2.first, p2.second);
		bomb2.state = 3;
		MAP[p2.first][p2.second] = 'o';
	}
	else
	{
		int speed1 = player1.speed;
		for (int i = 1; i <= speed1; i++)
		{
			std::pair<int, int> p = player1.get_location();
			std::pair<int, int> p2 = player2.get_location();
			if (ch == 'W')
			{
				cout << p.first << " " << p.second << endl;

				if (p.first > 0 && MAP[p.first - i][p.second] != '#' && MAP[p.first - i][p.second] != '*')
				{
					if (MAP[p.first - i][p.second] == '1')
					{
						player1.speed++, player1.speedsecond = 6;
						MAPTool[p.first - i][p.second] = 0;
					}
					else if (MAP[p.first - i][p.second] == '2')
					{
						bomb1.level++;
						MAPTool[p.first - i][p.second] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first - i][p.second] = 'A';
					player1.update_location(1);
				}
			}
			else if (ch == 'A')
			{
				if (p.second > 0 && MAP[p.first][p.second - i] != '*' && MAP[p.first][p.second - i] != '#')
				{
					if (MAP[p.first][p.second - i] == '1')
					{
						player1.speed++, player1.speedsecond = 6;
						MAPTool[p.first][p.second - 1] = 0;
					}
					else if (MAP[p.first][p.second - i] == '2')
					{
						bomb1.level++;
						MAPTool[p.first][p.second - i] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first][p.second - i] = 'A';
					player1.update_location(2);
				}
			}
			else if (ch == 'S')
			{
				if (p.first < 19 && MAP[p.first + i][p.second] != '*' && MAP[p.first + i][p.second] != '#')
				{
					if (MAP[p.first + i][p.second] == '1')
					{
						player1.speed++, player1.speedsecond = 6;
						MAPTool[p.first + i][p.second] = 0;
					}
					else if (MAP[p.first + i][p.second] == '2')
					{
						bomb1.level++;
						MAPTool[p.first + i][p.second] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first + i][p.second] = 'A';
					player1.update_location(3);
				}
			}
			else if (ch == 'D')
			{
				if (p.second < 59 && MAP[p.first][p.second + i] != '*' && MAP[p.first][p.second + i] != '#')
				{
					if (MAP[p.first][p.second + i] == '1')
					{
						player1.speed++, player1.speedsecond = 6;
						MAPTool[p.first][p.second + i] = 0;
					}
					else if (MAP[p.first][p.second + i] == '2')
					{
						bomb1.level++;
						MAPTool[p.first][p.second + i] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first][p.second + i] = 'A';
					player1.update_location(4);
				}
			}
			cout << p.first << p.second << endl;
			display();
		}
	}
	int speed2 = player2.speed;
	while (speed2 > 0)
	{
		std::pair<int, int> p = player1.get_location();
		std::pair<int, int> p2 = player2.get_location();
		speed2--;
		if (ch == 'I')
		{
			if (p2.first > 0 && MAP[p2.first - 1][p2.second] != '*' && MAP[p2.first - 1][p2.second] != '#')
			{
				if (MAP[p2.first - 1][p2.second] == '1')
				{
					player2.speed++, player2.speedsecond = 6;
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
					player2.speed++, player2.speedsecond = 6;
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
					player2.speed++, player2.speedsecond = 6;
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
					player2.speed++, player2.speedsecond = 6;
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
		display();
	}
}
	void PrintAll()
	{
		for (int i = 0; i < 21; i++)
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
		if (time % 9 == 0)
		{
			r1.RobotBoom(1);
			r2.RobotBoom(2);
			display();
		}
		if (player1.speedsecond >= 1)
		{
			player1.speedsecond--;
			if (player1.speedsecond == 0)
				player1.speed--;
		}
		if (player2.speedsecond >= 1)
		{
			player2.speedsecond--;
			if (player2.speedsecond == 0)
				player2.speed--;
		}
		if (bomb1.state <= 3)
		{
			bomb1.state--;
			if (bomb1.state == 0)
				bomb1.bomb_picture(bomb1.level), bomb1.state = 5, display();
		}
		if (bomb2.state <= 3)
		{
			bomb2.state--;
			if (bomb2.state == 0)
				bomb2.bomb_picture(bomb2.level), bomb2.state = 5, display();
		}
		if (rboom1.state <= 3)
		{
			rboom1.state--;
			if (rboom1.state == 0)
				rboom1.bomb_picture(rboom1.level), rboom1.state = 5, display();
		}
		if (rboom2.state <= 3)
		{
			rboom2.state--;
			if (rboom2.state == 0)
				rboom2.bomb_picture(rboom2.level), rboom2.state = 5, display();
		}

		if (bomb1.state == 5)
		{
			bomb1.state--;
			bomb1.afterboom(), display();
		}
		if (bomb2.state == 5)
		{
			bomb2.state--;
			bomb2.afterboom(), display();
		}
		if (rboom1.state == 5)
		{
			rboom1.state--;
			rboom1.afterboom(), display();
		}
		if (rboom2.state == 5)
		{
			rboom2.state--;
			rboom2.afterboom(), display();
		}
	}
	void InitRole()
	{
        player1.symbol = 'A',player1.speed = 1, player1.speedsecond = 0;
		player2.symbol = 'B',player2.speed = 1, player2.speedsecond = 0;
		r1.dir = 0, r1.id = 1, r2.id = 2, r2.dir = 0;
		bomb1.state = 4, bomb1.level = 1;
		bomb2.state = 4, bomb2.level = 1;
		rboom1.state = 4, rboom1.level = 1;
		rboom2.state = 4, rboom2.level = 1;
	} 
	int main()
	{
		Initmap();
		InitRole();
		PrintAll();
		int count = 1;
		int times = 0;
		while (1)
		{
			char ch;
			if (count % 4500000 == 0)
			{
                if (_kbhit())
				{
					ch = _getch();
					if (ch == 27)
						break;
					deal_with_input(ch);
					// display();
				}
                if (_kbhit())
				{
					_getch();
				}
			}
			if (count == 90000000)
			{
				times++;
				deal_with_time(times);
				count = 0;
			}
			count++;
		}
		return 0;
	}
