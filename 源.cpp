#include <iostream>
#include <conio.h>
using namespace std;
const int WIDE = 21;
const int LEN = 60;
#define OVER 5
#define ONE_SECOND 100000000
char MAP[WIDE][LEN];
int MAPTool[WIDE][LEN];
enum DIRACTION
{
	UP = 1, DOWN, RIGHT, LEFT
};
void display();
void PrintAll();
void Welcome();
class Robot
{
private:
	
	char symbol;
	std::pair<int, int> locationr;

public:
	int predir;
	int dir;
    int id;
	Robot(int x, int y, char symbol);
	void RobotBoom(int id);
	void update_location(int x, int y);
	void Walk(int dir);
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
std::pair<int, int> Robot::get_location()
{
	return locationr;
}

class Player
{
private:

	std::pair<int, int> location;

public:
	char symbol;
	int score;
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
	int levelsecond;
	int state;
	Bomb(int x, int y);
	void afterboom();
	void bomb_picture(int lev, int id);
	void update_location(int t, int y);
	std::pair<int, int> get_location();
};
Player player1(WIDE / 2 - 1, 5);
Player player2(WIDE / 2 - 1, LEN - 5);
Robot r1(1, LEN / 2, 'R');
Robot r2(WIDE - 2, LEN / 2, 'R');
Bomb bomb1(0, 0);
Bomb bomb2(0, 0);
Bomb rboom1(0, 0);
Bomb rboom2(0, 0);
Bomb::Bomb(int x, int y)
{
	location.first = x;
	location.second = y;
}

std::pair<int, int> Bomb::get_location()
{
	return location;
}
void Bomb::bomb_picture(int lev, int id)
{
	MAP[location.first][location.second] = 'o';
	bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
	for (int i = 1; i <= level; i++)
	{
		if (MAP[location.first - i][location.second] != '#' && flag1 != 1)
		{
			if (MAP[location.first - i][location.second] == '*')
			{
				if (id == 1)
					player1.score++;
				else
					player2.score++;
			}
			MAP[location.first - i][location.second] = '~';
		}
		else if (MAP[location.first - i][location.second] == '#')
		    flag1 = 1;
		if (MAP[location.first + i][location.second] != '#' && flag2 != 1)
		{
			if (MAP[location.first + i][location.second] == '*')
			{
				if (id == 1)
					player1.score++;
				else
					player2.score++;
			}
			MAP[location.first + i][location.second] = '~';
		}
		else if (MAP[location.first + i][location.second] == '#')
			flag2 = 1;
		if (MAP[location.first][location.second + i] != '#' && flag3 != 1)
		{
			if (MAP[location.first][location.second + i] == '*')
			{
				if (id == 1)
					player1.score++;
				else
					player2.score++;
			}
			MAP[location.first][location.second + i] = '~';
		}
		else if (MAP[location.first][location.second + i] == '#')
			flag3 = 1;
		if (MAP[location.first][location.second - i] != '#' && flag4 != 1)
		{
			if (MAP[location.first][location.second - i] == '*')
			{
				if (id == 1)
					player1.score++;
				else
					player2.score++;
			}
			MAP[location.first][location.second - i] = '~';
		}
		else if (MAP[location.first][location.second - i] == '#')
			flag4 = 1;
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
				MAP[location.first - i][location.second] = '1';
			else if (MAPTool[location.first - i][location.second] == 2)
				MAP[location.first - i][location.second] = '2';
			else
				MAP[location.first - i][location.second] = ' ';
		}
		if (MAP[location.first + i][location.second] == '~')
		{
			if (MAPTool[location.first + i][location.second] == 1)
				MAP[location.first + i][location.second] = '1';
			else if (MAPTool[location.first + i][location.second] == 2)
				MAP[location.first + i][location.second] = '2';
			else
				MAP[location.first + i][location.second] = ' ';
		}
		if (MAP[location.first][location.second - i] == '~')
		{
			if (MAPTool[location.first][location.second - i] == 1)
				MAP[location.first][location.second - i] = '1';
			else if (MAPTool[location.first][location.second - i] == 2)
				MAP[location.first][location.second - i] = '2';
			else
				MAP[location.first][location.second - i] = ' ';
		}
		if (MAP[location.first][location.second + i] == '~')
		{
			if (MAPTool[location.first][location.second + i] == 1)
				MAP[location.first][location.second + i] = '1';
			else if (MAPTool[location.first][location.second + 1] == 2)
				MAP[location.first][location.second + i] = '2';
			else
				MAP[location.first][location.second + i] = ' ';
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
		location.first = location.first - 1;
	else if (type == 2)
	    location.second = location.second - 1;
	else if (type == 3)
		location.first = location.first + 1;
	else if (type == 4)
		location.second = location.second + 1;
}


void Robot::RobotBoom(int id)
{
	int direction = rand() % 5;
	if (dir)
		direction = dir;
	while (direction == predir)
		direction = rand() % 5;
	if (direction == UP)
	{
		predir = DOWN;
		if (MAP[locationr.first - 1][locationr.second] == ' ' || MAP[locationr.first - 1][locationr.second] == '1' || MAP[locationr.first - 1][locationr.second] == '2')
		{
			MAP[locationr.first - 1][locationr.second] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else 
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
				r1.Walk(2);
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
				r2.Walk(2);
			}
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first + 1][locationr.second] = 'R';
			update_location(locationr.first + 1, locationr.second);
			display();
			
		}
	}
	else if (direction == DOWN)
	{
		predir = UP;
		if (MAP[locationr.first + 1][locationr.second] == ' '|| MAP[locationr.first + 1][locationr.second] == '1' || MAP[locationr.first + 1][locationr.second] == '2' )
		{
			MAP[locationr.first + 1][locationr.second] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
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
				r1.Walk(1);
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
				r2.Walk(1);
			}
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first - 1][locationr.second] = 'R';
			update_location(locationr.first - 1, locationr.second);
			display();
		}
	}
	else if (direction == LEFT)
	{
		predir = RIGHT;
		if (MAP[locationr.first][locationr.second - 1] == ' ' || MAP[locationr.first][locationr.second - 1] == '1' || MAP[locationr.first][locationr.second - 1] == '2')
		{
			MAP[locationr.first][locationr.second - 1] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
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
				r1.Walk(4);
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
				r2.Walk(4);
			}
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second + 1] = 'R';
			update_location(locationr.first, locationr.second + 1);
			display();
		}
	}
	else if (direction == RIGHT)
	{
	    predir = LEFT;
		if (MAP[locationr.first][locationr.second + 1] == ' ' || MAP[locationr.first][locationr.second + 1] == '1' || MAP[locationr.first][locationr.second + 1] == '2')
		{
			MAP[locationr.first][locationr.second + 1] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
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
				r1.Walk(3);
			}
			else if (id == 2 && rboom2.state == 4)
			{
				rboom2.update_location(locationr.first, locationr.second);
				rboom2.state = 3;
				r2.Walk(3);
			}
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second - 1] = 'R';
			update_location(locationr.first, locationr.second - 1);
			display();
		}
	}
}
void Robot::Walk(int dir)
{
	std::pair<int, int> p = get_location();
	if (dir == 1)
	{
		MAP[p.first - 1][p.second] = 'R';
		update_location(p.first - 1, p.second);
	}
	else if (dir == 2)
	{
		MAP[p.first + 1][p.second] = 'R';
		update_location(p.first + 1, p.second);
	}
	else if (dir == 3)
	{
		MAP[p.first][p.second - 1] = 'R';
		update_location(p.first, p.second - 1);
	}
	else if (dir == 4)
	{
		MAP[p.first][p.second + 1] = 'R';
		update_location(p.first, p.second + 1);
	}
	display();
}
void Initmap()
{
	memset(MAP, ' ', sizeof(MAP));
	int locx = 0;
	int locy = 0;
	int tool = 0;
	for (int i = 0; i < 21; i += 2)
		for (int j = 0; j < 60; j += 2)
			MAP[i][j] = '#';
	for (int i = 0; i < 500; i++)
	{
		locx = rand() % 20;
		locy = rand() % 59;
		if (MAP[locx][locy] != '#')
			MAP[locx][locy] = '*';
		if (tool % 3 == 0)
			MAPTool[locx][locy] = 1;
		else if (tool % 4 == 0)
			MAPTool[locx][locy] = 2;
		tool++;
	}
	for (int i = 0; i < 21; i++)
	    MAP[i][0] = '#', MAP[i][59] = '#';
	for (int i = 0; i < 60; i++)
		MAP[0][i] = '#', MAP[20][i] = '#';
	MAP[9][5] = 'A';
	MAP[9][55] = 'B';
	MAP[1][30] = 'R', MAP[19][30] = 'R';
}

void deal_with_input(char ch)// ������������
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
			if (ch == 'W')
			{
				if (p.first > 0 && MAP[p.first - 1][p.second] != '#' && MAP[p.first - 1][p.second] != '*')
				{
					if (MAP[p.first - 1][p.second] == '1')
					{
						player1.score++,  player1.speed++, player1.speedsecond += 6;
						MAPTool[p.first - 1][p.second] = 0;
					}
					else if (MAP[p.first - 1][p.second] == '2')
					{
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
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
						player1.score++, player1.speed++, player1.speedsecond += 6;
						MAPTool[p.first][p.second - 1] = 0;
					}
					else if (MAP[p.first][p.second - 1] == '2')
					{
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
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
						player1.score++, player1.speed++, player1.speedsecond += 6;
						MAPTool[p.first + 1][p.second] = 0;
					}
					else if (MAP[p.first + 1][p.second] == '2')
					{
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
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
						player1.score++, player1.speed++, player1.speedsecond += 6;
						MAPTool[p.first][p.second + 1] = 0;
					}
					else if (MAP[p.first][p.second + 1] == '2')
					{
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
						MAPTool[p.first][p.second + 1] = 0;
					}
					MAP[p.first][p.second] = ' ';
					MAP[p.first][p.second + 1] = 'A';
					player1.update_location(4);
				}
			}
			// cout << p.first << p.second << endl;
			display();
		}
	}
	int speed2 = player2.speed;
	while (speed2 > 0)
	{
		std::pair<int, int> p2 = player2.get_location();
		speed2--;
		if (ch == 'I')
		{
			if (p2.first > 0 && MAP[p2.first - 1][p2.second] != '*' && MAP[p2.first - 1][p2.second] != '#')
			{
				if (MAP[p2.first - 1][p2.second] == '1')
				{
					player2.score++, player2.speed++, player2.speedsecond += 6;
					MAPTool[p2.first - 1][p2.second] = 0;
				}
				else if (MAP[p2.first - 1][p2.second] == '2')
				{
					player2.score++, bomb2.level++, bomb2.levelsecond += 6;
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
					player2.score++, player2.speed++, player2.speedsecond += 6;
					MAPTool[p2.first][p2.second - 1] = 0;
				}
				else if (MAP[p2.first][p2.second - 1] == '2')
				{
					player2.score++, bomb2.level++, bomb2.levelsecond += 6;
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
					player2.score++, player2.speed++, player2.speedsecond += 6;
					MAPTool[p2.first + 1][p2.second] = 0;
				}
				else if (MAP[p2.first + 1][p2.second] == '2')
				{
					player2.score++, bomb2.level++, bomb2.levelsecond += 6;
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
					player2.score++, player2.speed++, player2.speedsecond += 6;
					MAPTool[p2.first][p2.second + 1] = 0;
				}
				else if (MAP[p2.first][p2.second + 1] == '2')
				{
					player2.score++, bomb2.level++, bomb2.levelsecond += 6;
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
				cout << MAP[i][j];
			}
			cout << endl;
		}
		cout << "Player1 score : " << player1.score << endl;
		cout << "Player2 score : " << player2.score << endl;
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
				player1.speed = 1;
		}
		if (player2.speedsecond >= 1)
		{
			player2.speedsecond--;
			if (player2.speedsecond == 0)
				player2.speed = 1;
		}
		if (bomb1.levelsecond >= 1)
		{
			bomb1.levelsecond--;
			if (bomb1.levelsecond == 0)
				bomb1.level = 1;
		}
		if (bomb2.levelsecond >= 1)
		{
			bomb2.levelsecond--;
			if (bomb2.levelsecond == 0)
				bomb2.level = 1;
		}
		if (bomb1.state <= 3)
		{
			bomb1.state--;
			if (bomb1.state == 0)
				bomb1.bomb_picture(bomb1.level, 1), bomb1.state = 5, display();
		}
		if (bomb2.state <= 3)
		{
			bomb2.state--;
			if (bomb2.state == 0)
				bomb2.bomb_picture(bomb2.level, 2), bomb2.state = 5, display();
		}
		if (rboom1.state <= 3)
		{
			rboom1.state--;
			if (rboom1.state == 0)
				rboom1.bomb_picture(rboom1.level, 1), rboom1.state = 5, display();
		}
		if (rboom2.state <= 3)
		{
			rboom2.state--;
			if (rboom2.state == 0)
				rboom2.bomb_picture(rboom2.level, 2), rboom2.state = 5, display();
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
        player1.symbol = 'A', player1.score = 0, player1.speed = 1, player1.speedsecond = 0;
		player2.symbol = 'B', player2.score = 0, player2.speed = 1, player2.speedsecond = 0;
		r1.predir = 0, r1.dir = 0, r1.id = 1, r2.predir = 0, r2.id = 2, r2.dir = 0;
		bomb1.state = 4, bomb1.level = 1, bomb1.levelsecond = 0;
		bomb2.state = 4, bomb2.level = 1, bomb2.levelsecond = 0;
		rboom1.state = 4, rboom1.level = 1;
		rboom2.state = 4, rboom2.level = 1;
	}
	void Welcome()
	{
		cout << "***********************************************************" << endl;
		cout << "         Welcome to zxy's Crazy Arcade                     " << endl;
		cout << "\n\nDo you want to be a super Bombman ?" << endl;
		cout << "\nHere !   Make your Dream Come True !" << endl;
		cout << "This game is for two players:" << endl;
		cout << "'A' is player1\n";
		cout << "'B' is player2\n";
		cout << "Player1 use 'W S A D��   to control the direciton\n";
		cout << "            'Space Key'  to put the bomb 'o'" << endl;
		cout << "Player2 use 'I K J L'    to control the direction\n";
		cout << "            'Return Key' to put the bomb 'o'" << endl;
		cout << "There are also two Robots 'R'\n";
		cout << "as for the wall:\n";
		cout << "'#' is the hard wall, which can't be bombed\n";
		cout << "'*' is the soft wall, which can be bombed\n";
		cout << "as for the treat, they are hiding in the soft wall:\n";
		cout << "'1' is for speeding up\n";
		cout << "'2' is for increasing your bomb power\n";
		cout << "\nnow!\n";
		cout << "make good use of your bomb !\n";
		cout << "bomb the wall��pick up the treatand get scores.\n";
		cout << "oh ! Remember don't set yourself up!\n";
		cout << "Here we go!\n";
		system("pause");
		system("cls");
	}

	int main()
	{
		Welcome();
		Initmap();
		InitRole();
		PrintAll();
		int count = 1, times = 0;
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
			if (count == ONE_SECOND)
			{
				times++;
				deal_with_time(times);
				count = 0;
			}
			count++;
		}
		return 0;
	}