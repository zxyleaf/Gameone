#include <iostream>
#include <conio.h>
using namespace std;
const int WIDE = 14;
const int LEN = 20;
#define OVER 5
#define ONE_SECOND 25000
int MAPTool[14][20];
clock_t cur, lasttime;

char MAP[14][20] = {
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','*','*','*','#','*','#','*',' ','R','*','*','*',' ','#',' ','#','#','B','#'},
	{'#','*','*',' ','#','*','#','*',' ',' ','*','*','#',' ','*',' ','*','*',' ','#'},
	{'#',' ','#',' ','*','*','#','#','*',' ','*',' ','#','#','*','*','*','#',' ','#'},
	{'#',' ','#','#','#',' ','*','*','#','*',' ','*','*','*',' ','#','#','#','*','#'},
	{'#','A','*','*','*','*',' ','*','#','*','#','*','*','*',' ','#',' ','#','*','#'},
	{'#','*',' ',' ','*','#',' ','*','#',' ','#',' ','*','*',' ','#','*',' ',' ','#'},
	{'#','#',' ','#','#','#','*',' ','#','#','#',' ','*','*','#','#','#','*','#','#'},
	{'#','#',' ','*','*',' ','*','*','*','*','*',' ',' ','#','#','*',' ','*','*','#'},
	{'#','*','*','#','*',' ','#','#','#','#','*',' ','#','#','*','*',' ','*','*','#'},
	{'#','*','*','#','*',' ','#','*','#','#','*','*','*','*','*',' ',' ',' ','#','#'},
	{'#','*',' ',' ','*','*','*',' ',' ',' ',' ','*','*',' ','*','*','*','#','*','#'},
	{'#','*','*','*','#','*','#','*',' ','R',' ','*','*',' ','#',' ','*','#','*','#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

class Bomb;
class Player;
class Robot;
enum DIRACTION
{
	UP = 1, DOWN, RIGHT, LEFT
};
void display();
void PrintAll();
void Welcome();
void GetScore(int id);
class Robot
{
private:
	char symbol;
	std::pair<int, int> locationr;
	int id;
public:
	int predir = 0;
	int dir = 0;
	bool live = 1;
	Bomb* ownthebomb;
	Robot(int x, int y,int idx, char symbol);
	int GetId();
	void RobotBoom();
	void update_location(int x, int y);
	void Walk(int dir);
	std::pair<int, int> get_location();
};

Robot::Robot(int x, int y, int idx, char sym)
{
	locationr.first = x;
	locationr.second = y;
	id = idx;
	symbol = sym;
}
int Robot::GetId()
{
	return id;
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
	char symbol;
    bool live;
public:
	
	int score = 0;
	int speed = 1;
	int speedsecond = 0;
	int Bombnum = 3;
	int Diff = 500;
	clock_t Lastime = 0;
	char GetSymbol();
	void SetLive(bool liv);
	bool GetLive();
	Player(int x, int y, char sy);
	void update_location(int type);
	std::pair<int, int> get_location();
};
void Player::SetLive(bool liv)
{
	live = liv;
}
bool Player::GetLive()
{
	return live;
}
class Bomb
{
private:
	int id;
	std::pair<int, int> location;
public:
	int level = 1;
	int levelsecond = 0;
	int state = -1;
	Bomb* nextBomb;
	Player* owner;
	Robot* own;
	void afterboom(int id);
	void bomb_picture(int lev, int id);
	void update_location(int t, int y);
	void SetId(int ID);
	int GetId();
	std::pair<int, int> get_location();
	friend class Player;
};

void Bomb::SetId(int ID)
{
	id = ID;
}
int Bomb::GetId()
{
	return id;
}
Bomb* head1;
Bomb* head2;
Player player1(5, 1,'A'), player2(1, 18, 'B');
Robot r1(1, 9, 1, 'R'), r2(12, 9, 2, 'R');
Bomb bomb1, bomb2, rboom1, rboom2;

std::pair<int, int> Bomb::get_location()
{
	return location;
}
void SthHide(int i, int j, int idx)
{
	if (MAP[i][j] == 'A')
		player1.SetLive(0);
	else if (MAP[i][j] == 'B')
		player2.SetLive(0);
	else if (i == r1.get_location().first && j == r1.get_location().second)
		r1.live = 0, GetScore(idx);
	else if (i == r2.get_location().first && j == r2.get_location().second)
		r2.live = 0, GetScore(idx);
	if (MAP[i][j] == 'o')
		MAPTool[i][j] = 3;
	MAP[i][j] = '~';
}
void Bomb::bomb_picture(int lev, int id)
{ 
	bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0; // ≤ªª·¥©Õ∏”≤«Ω’®¥©
	for (int i = 1; i <= lev; i++)
	{
		if (MAP[location.first - i][location.second] != '#' && flag1 != 1)
		{
			if (id != 3 && id != 4)
			{
				if (MAP[location.first - i][location.second] == '*')
				{
					this->owner->score++;
					flag1 = 1;
				}
			}
			SthHide(location.first - i,location.second, id);
		}
		else if (MAP[location.first - i][location.second] == '#')
		    flag1 = 1;
		if (MAP[location.first + i][location.second] != '#' && flag2 != 1)
		{
			if (id != 3 && id != 4)
			{
				if (MAP[location.first + i][location.second] == '*')
				{
					this->owner->score++;
					flag2 = 1;
				}
			}
			SthHide(location.first + i, location.second, id);
		}
		else if (MAP[location.first + i][location.second] == '#')
			flag2 = 1;
		if (MAP[location.first][location.second + i] != '#' && flag3 != 1)
		{
			if (id != 3 && id != 4)
			{
				if (MAP[location.first][location.second + i] == '*')
				{
					this->owner->score++;
					flag3 = 1;
				}
			}
			SthHide(location.first, location.second + i, id);
		}
		else if (MAP[location.first][location.second + i] == '#')
			flag3 = 1;
		if (MAP[location.first][location.second - i] != '#' && flag4 != 1)
		{
			if (id != 3 && id != 4)
			{
				if (MAP[location.first][location.second - i] == '*')
					this->owner->score++, flag4 = 1;
			}
			SthHide(location.first, location.second - i, id);
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
void GetScore(int id)
{
	if (id == 1)
		player1.score += 5;
	else if (id == 2)
		player2.score += 5;
}
void SthLeft(int i, int j)
{
	if (MAPTool[i][j] == 1)
		MAP[i][j] = '1';
	else if (MAPTool[i][j] == 2)
		MAP[i][j] = '2';
	else if (MAPTool[i][j] == 3)
		MAP[i][j] = 'o';
	else
		MAP[i][j] = ' ';
}
void Bomb::afterboom(int id)
{
	MAPTool[location.first][location.second] = 0;
	if (id == 1)
		player1.Bombnum++;
	else if (id == 2)
		player2.Bombnum++;
	if (location.first == player1.get_location().first && location.second == player1.get_location().second)
		player1.SetLive(0);
	else if (location.first == player2.get_location().first && location.second == player2.get_location().second)
		player2.SetLive(0);
	else if (location.first == r1.get_location().first && location.second == r1.get_location().second)
		r1.live = 0;
	else if (location.first == r2.get_location().first && location.second == r2.get_location().second)
		r2.live = 0;
	else if (MAPTool[location.first][location.second] == 1)
		MAP[location.first][location.second] = '1';
	else if (MAPTool[location.first][location.second] == 2)
		MAP[location.first ][location.second] = '2';
	else
		MAP[location.first][location.second] = ' ';
	for (int i = 1; i <= level; i++)
	{
		if (MAP[location.first - i][location.second] == '~')
			SthLeft(location.first - i, location.second);
		if (MAP[location.first + i][location.second] == '~')
			SthLeft(location.first + i, location.second);
		if (MAP[location.first][location.second - i] == '~')
			SthLeft(location.first, location.second - i);
		if (MAP[location.first][location.second + i] == '~')
			SthLeft(location.first, location.second + i);
	}
}
Player::Player(int x, int y, char sy)
{
	symbol = sy;
	location.first = x;
	location.second = y;
}
char Player::GetSymbol()
{
	return symbol;
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

void Robot::RobotBoom()
{
	int direction = rand() % 4 + 1;
	if (dir)
		direction = dir;
	while (direction == predir)
		direction = rand() % 4 + 1;
	if (direction == UP)
	{
		if (MAP[locationr.first - 1][locationr.second] == ' ' || MAP[locationr.first - 1][locationr.second] == '1' || MAP[locationr.first - 1][locationr.second] == '2')
		{
			predir = DOWN;
			MAP[locationr.first - 1][locationr.second] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
				MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first - 1, locationr.second);
			dir = DOWN;
			display();
		}
		else if (this->ownthebomb->state == 4 && MAP[locationr.first - 1][locationr.second] == '*' && locationr.first < 12 && MAP[locationr.first + 1][locationr.second] != ' ' && MAP[locationr.first + 2][locationr.second] != ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			MAPTool[locationr.first][locationr.second] = 3;
			dir = 2;
			this->ownthebomb->update_location(locationr.first, locationr.second);
			this->ownthebomb->state = 3;
			this->Walk(2);
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first + 1][locationr.second] = 'R';
			update_location(locationr.first + 1, locationr.second);
			display();
		}
		else
			predir = 1;
	}
	else if (direction == DOWN)
	{
		if (MAP[locationr.first + 1][locationr.second] == ' ' || MAP[locationr.first + 1][locationr.second] == '1' || MAP[locationr.first + 1][locationr.second] == '2')
		{
			predir = UP;
			MAP[locationr.first + 1][locationr.second] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
				MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first + 1, locationr.second);
			dir = UP;
			display();
		}
		else if (this->ownthebomb->state == 4 && MAP[locationr.first + 1][locationr.second] == '*' && (locationr.first > 2 && MAP[locationr.first - 1][locationr.second] == ' ' && MAP[locationr.first - 2][locationr.second] == ' '))
		{
			MAP[locationr.first][locationr.second] = 'o';
			MAPTool[locationr.first][locationr.second] = 3;
			dir = UP;
			this->ownthebomb->update_location(locationr.first, locationr.second);
			this->ownthebomb->state = 3;
			this->Walk(1);
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first - 1][locationr.second] = 'R';
			update_location(locationr.first - 1, locationr.second);
			display();
		}
		else
			predir = DOWN;
	}
	else if (direction == LEFT)
	{
		if (MAP[locationr.first][locationr.second - 1] == ' ' || MAP[locationr.first][locationr.second - 1] == '1' || MAP[locationr.first][locationr.second - 1] == '2')
		{
			predir = RIGHT;
			MAP[locationr.first][locationr.second - 1] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
				MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second - 1);
			dir = LEFT;
			display();
		}
		else if (this->ownthebomb->state == 4 && MAP[locationr.first][locationr.second - 1] == '*' && locationr.second < 18 && MAP[locationr.first][locationr.second + 1] == ' ' && MAP[locationr.first][locationr.second + 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			MAPTool[locationr.first][locationr.second] = 3;
			dir = LEFT;
			this->ownthebomb->update_location(locationr.first, locationr.second);
			this->ownthebomb->state = 3;
			this->Walk(4);
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second + 1] = 'R';
			update_location(locationr.first, locationr.second + 1);
			display();
		}
		else
			predir = LEFT;
	}
	else if (direction == RIGHT)
	{
		if (MAP[locationr.first][locationr.second + 1] == ' ' || MAP[locationr.first][locationr.second + 1] == '1' || MAP[locationr.first][locationr.second + 1] == '2')
		{
			predir = LEFT;
			MAP[locationr.first][locationr.second + 1] = 'R';
			if (MAPTool[locationr.first][locationr.second] == 1)
				MAP[locationr.first][locationr.second] = '1';
			else if (MAPTool[locationr.first][locationr.second] == 2)
				MAP[locationr.first][locationr.second] = '2';
			else
				MAP[locationr.first][locationr.second] = ' ';
			update_location(locationr.first, locationr.second + 1);
			dir = RIGHT;
			display();
		}
		else if (this->ownthebomb->state == 4 && MAP[locationr.first][locationr.second + 1] == '*' && locationr.second > 2 && MAP[locationr.first][locationr.second - 1] == ' ' && MAP[locationr.first][locationr.second - 2] == ' ')
		{
			MAP[locationr.first][locationr.second] = 'o';
			MAPTool[locationr.first][locationr.second] = 3;
			dir = 3;
			this->ownthebomb->update_location(locationr.first, locationr.second);
			this->ownthebomb->state = 3;
			this->Walk(3);
			MAP[locationr.first][locationr.second] = ' ';
			MAP[locationr.first][locationr.second - 1] = 'R';
			update_location(locationr.first, locationr.second - 1);
			display();
		}
	    else
		   predir = 3;
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
void TellIfBomb(int i, int j)
{
	if (MAP[i][j] == 'o')
		MAP[i][j] = 'o';
	else
		MAP[i][j] = ' ';
}
void deal_with_input(char ch)// ¥¶¿Ìº¸≈Ã ‰»Î
{
	std::pair<int, int> p = player1.get_location();
	std::pair<int, int> p2 = player2.get_location();
	if (ch == ' ' && player1.Bombnum > 0)
	{
		player1.Bombnum--;
		Bomb* newone = new Bomb;
		newone->SetId(1);
		newone->state = 3;
		newone->owner = &player1;
		Bomb* temp = head1;
		while (temp != NULL && temp->nextBomb != NULL)
			temp = temp->nextBomb;
		if (head1 != NULL)
		{
			newone->level = temp->level;
			newone->levelsecond = temp->levelsecond;
			newone->nextBomb = NULL;
			temp->nextBomb = newone;
		}
		else
		{
			newone->level = bomb1.level;
			newone->levelsecond = bomb1.levelsecond;
			newone->nextBomb = NULL;
			head1 = newone;
		}
		newone->update_location(p.first, p.second);
		MAPTool[p.first][p.second] = 6;
		newone->state = 3;
		MAP[p.first][p.second] = 'o';
	}
	else if (ch == 13 && player2.Bombnum > 0)
	{
		player2.Bombnum--;
		Bomb* newone = new Bomb;
		newone->SetId(2);
		newone->state = 3;
		newone->owner = &player2;
		Bomb* temp = head2;
		while (temp != NULL && temp->nextBomb != NULL)
			temp = temp->nextBomb;
		if (head2 != NULL)
		{
			newone->level = temp->level;
			newone->levelsecond = temp->levelsecond;
			newone->nextBomb = NULL;
			temp->nextBomb = newone;
		}
		else
		{
			newone->level = bomb2.level;
			newone->levelsecond = bomb2.levelsecond;
			newone->nextBomb = NULL;
			head2 = newone;
		}
		newone->update_location(p2.first, p2.second);
		newone->state = 3;
		MAP[p2.first][p2.second] = 'o';
		MAPTool[p2.first][p2.second] = 6;
	}
	else
	{
		if(ch == 'W' || ch == 'A' || ch == 'S' || ch == 'D')
		{
			if ((cur - player1.Lastime) < player1.Diff)
			    return;
			player1.Lastime = cur;
			std::pair<int, int> p = player1.get_location();
			if (ch == 'W')
			{
				if (p.first > 0 && MAP[p.first - 1][p.second] != '#' && MAP[p.first - 1][p.second] != '*'&& MAPTool[p.first - 1][p.second] != 6)
				{
					if (MAP[p.first - 1][p.second] == '1')
					{
						player1.score++, player1.speed++, player1.speedsecond += 6;
						player1.Diff /= 4;
						MAPTool[p.first - 1][p.second] = 0;
					}
					else if (MAP[p.first - 1][p.second] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
						MAPTool[p.first - 1][p.second] = 0;
					}
					TellIfBomb(p.first, p.second);
					MAP[p.first - 1][p.second] = 'A';
					player1.update_location(1);
				}
			}
			else if (ch == 'A')
			{
				if (p.second > 0 && MAPTool[p.first][p.second - 1] != 6 && MAP[p.first][p.second - 1] != '#' && MAP[p.first][p.second - 1] != '*')
				{
					if (MAP[p.first][p.second - 1] == '1')
					{
						player1.score++, player1.speed++, player1.speedsecond += 6;
						player1.Diff /= 4;
						MAPTool[p.first][p.second - 1] = 0;
					}
					else if (MAP[p.first][p.second - 1] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
						MAPTool[p.first][p.second - 1] = 0;
					}
					TellIfBomb(p.first, p.second);
					MAP[p.first][p.second - 1] = 'A';
					player1.update_location(2);
				}
			}
			else if (ch == 'S')
			{
				if (p.first < 13 && MAPTool[p.first + 1][p.second] != 6 && MAP[p.first + 1][p.second] != '#' && MAP[p.first + 1][p.second] != '*')
				{
					if (MAP[p.first + 1][p.second] == '1')
					{
						player1.score++, player1.speed++, player1.speedsecond += 6;
						player1.Diff /= 4;
						MAPTool[p.first + 1][p.second] = 0;
					}
					else if (MAP[p.first + 1][p.second] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
						MAPTool[p.first + 1][p.second] = 0;
					}
					TellIfBomb(p.first, p.second);
					MAP[p.first + 1][p.second] = 'A';
					player1.update_location(3);
				}
			}
			else if (ch == 'D')
			{
				if (p.second < 19 && MAPTool[p.first][p.second + 1] != 6 && MAP[p.first][p.second + 1] != '#' && MAP[p.first][p.second + 1] != '*')
				{
					if (MAP[p.first][p.second + 1] == '1')
					{
						player1.score++, player1.speed++, player1.speedsecond += 6;
						player1.Diff /= 4;
						MAPTool[p.first][p.second + 1] = 0;
					}
					else if (MAP[p.first][p.second + 1] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player1.score++, bomb1.level++, bomb1.levelsecond += 6;
						MAPTool[p.first][p.second + 1] = 0;
					}
					TellIfBomb(p.first, p.second);
					MAP[p.first][p.second + 1] = 'A';
					player1.update_location(4);
				}
			}
		}
		else
		{
			if ((cur - player2.Lastime) < player2.Diff)
			    return;
			player2.Lastime = cur;
			std::pair<int, int> p2 = player2.get_location();
			if (ch == 'I')
			{
				if (p2.first > 0 && MAPTool[p2.first - 1][p2.second] != 6 && MAP[p2.first - 1][p2.second] != '#' && MAP[p2.first - 1][p2.second] != '*')
				{
					if (MAP[p2.first - 1][p2.second] == '1')
					{
						player2.score++, player2.speed++, player2.speedsecond += 6;
						player2.Diff /= 4; 
						MAPTool[p2.first - 1][p2.second] = 0;
					}
					else if (MAP[p2.first - 1][p2.second] == '2')
					{
						Bomb* cnt = head2;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player2.score++, bomb2.level++, bomb2.levelsecond += 6;
						MAPTool[p2.first - 1][p2.second] = 0;
					}
					TellIfBomb(p2.first, p2.second);
					MAP[p2.first - 1][p2.second] = 'B';
					player2.update_location(1);
				}
			}
			else if (ch == 'J')
			{
				if (p2.second > 0 && MAPTool[p2.first][p2.second - 1] != 6 && MAP[p2.first][p2.second - 1] != '#' && MAP[p2.first][p2.second - 1] != '*')
				{
					if (MAP[p2.first][p2.second - 1] == '1')
					{
						player2.score++, player2.speed++, player2.speedsecond += 6;
						player2.Diff /= 4;
						MAPTool[p2.first][p2.second - 1] = 0;
					}
					else if (MAP[p2.first][p2.second - 1] == '2')
					{
						Bomb* cnt = head2;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player2.score++, bomb2.level++, bomb2.levelsecond += 6;
						MAPTool[p2.first][p2.second - 1] = 0;
					}
					TellIfBomb(p2.first, p2.second);
					MAP[p2.first][p2.second - 1] = 'B';
					player2.update_location(2);
				}
			}
			else if (ch == 'K')
			{
				if (p2.first < 13 && MAPTool[p2.first + 1][p2.second] != 6 && MAP[p2.first + 1][p2.second] != '#' && MAP[p2.first + 1][p2.second] != '*')
				{
					if (MAP[p2.first + 1][p2.second] == '1')
					{
						player2.score++, player2.speed++, player2.speedsecond += 6;
						player2.Diff /= 4;
						MAPTool[p2.first + 1][p2.second] = 0;
					}
					else if (MAP[p2.first + 1][p2.second] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player2.score++, bomb2.level++, bomb2.levelsecond += 6;
						MAPTool[p2.first + 1][p2.second] = 0;
					}
					TellIfBomb(p2.first, p2.second);
					MAP[p2.first + 1][p2.second] = 'B';
					player2.update_location(3);
				}
			}
			else if (ch == 'L')
			{
				if (p2.second < 19 && MAPTool[p2.first][p2.second + 1] != 6 && MAP[p2.first][p2.second + 1] != '#' && MAP[p2.first][p2.second + 1] != '*')
				{
					if (MAP[p2.first][p2.second + 1] == '1')
					{
						player2.score++, player2.speed++, player2.speedsecond += 6;
						player2.Diff /= 4;
						MAPTool[p2.first][p2.second + 1] = 0;
					}
					else if (MAP[p2.first][p2.second + 1] == '2')
					{
						Bomb* cnt = head1;
						while (cnt != NULL)
						{
							cnt->level++;
							cnt->levelsecond += 6;
							cnt = cnt->nextBomb;
						}
						player2.score++, bomb2.level++, bomb2.levelsecond += 6;
						MAPTool[p2.first][p2.second + 1] = 0;
					}
					TellIfBomb(p2.first, p2.second);
					MAP[p2.first][p2.second + 1] = 'B';
					player2.update_location(4);
				}
			}
		}
	}
}

void PrintAll()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << MAP[i][j];
		}
		cout << endl;
	}
	cout << "Player1 score : " << player1.score << endl;
	cout << "        Bomb level: " << bomb1.level << endl;
	cout << "        Bomb number:" << player1.Bombnum << endl;
	cout << "        Speed:      " << player1.speed << endl;
	cout << "Player2 score : " << player2.score << endl;
	cout << "        Bomb level:" << bomb2.level << endl;
	cout << "        Bomb number:" << player2.Bombnum << endl;
	cout << "        Speed:      " << player2.speed << endl;
}
void display()
{
	system("cls");
	PrintAll();
}
	
	void deal_with_time(int time)
	{
		if (time % 8 == 0)
		{
			if (r1.live == 1)
				r1.RobotBoom();
			if (r2.live == 1)
				r2.RobotBoom();
		}
		Bomb* cnt = head1;
		Bomb* pre = cnt;
		Bomb* cnt2 = head2;
		Bomb* pre2 = cnt2;
		while (cnt != NULL)
		{
			pre = cnt;
			cnt->state--;
			if (cnt->state == 5)
			{
				cnt->afterboom(cnt->GetId()), display();
				if (cnt == head1)
				{
					head1 = cnt->nextBomb;
				}
				else
					pre->nextBomb = cnt->nextBomb;
			}
			if (cnt->levelsecond >= 1)
			{
				cnt->levelsecond--;
				if (cnt->levelsecond == 0)
					cnt->level = 1,bomb1.level = 1;
			}
			if (cnt->state == 0)
				cnt->bomb_picture(cnt->level, 1), cnt->state = 6, display();
			cnt = cnt->nextBomb;
		}
		while (cnt2 != NULL)
		{
			pre2 = cnt2;
			cnt2->state--;
			if (cnt2->state == 5)
			{
				cnt2->afterboom(cnt2->GetId()), display();
				if (cnt2 == head2)
				{
					head2 = cnt2->nextBomb;
				}
				else
					pre2->nextBomb = cnt2->nextBomb;
			}
			if (cnt2->levelsecond >= 1)
			{
				cnt2->levelsecond--;
				if (cnt2->levelsecond == 0)
					cnt2->level = 1, bomb2.level= 1;
			}
			if (cnt2->state == 0)
				cnt2->bomb_picture(cnt2->level, 2), cnt2->state = 6, display();
			cnt2 = cnt2->nextBomb;
		}
		if (player1.speedsecond >= 1)
		{
			player1.speedsecond--;
			if (player1.speedsecond == 0)
				player1.Diff = 150, player1.speed = 1;
		}
		if (player2.speedsecond >= 1)
		{
			player2.speedsecond--;
			if (player2.speedsecond == 0)
				player2.Diff = 150, player2.speed = 1;
		}
		if (rboom1.state == 5)
		{
			rboom1.state--;
			rboom1.afterboom(rboom1.GetId()), display();
		}
		if (rboom2.state == 5)
		{
			rboom2.state--;
			rboom2.afterboom(rboom2.GetId()), display();
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
		if (rboom1.state <= 3)
		{
			rboom1.state--;
			if (rboom1.state == 0)
				rboom1.bomb_picture(rboom1.level, 3), rboom1.state = 5, display();
		}
		if (rboom2.state <= 3)
		{
			rboom2.state--;
			if (rboom2.state == 0)
				rboom2.bomb_picture(rboom2.level, 4), rboom2.state = 5, display();
		}
		
	}
	void InitRole()
	{
		player1.score = 0, player1.speed = 1, player1.speedsecond = 0, player1.Diff = 150, player1.Lastime = clock();
		player2.score = 0, player2.speed = 1, player2.speedsecond = 0, player2.Diff = 150, player2.Lastime = clock();
		player1.Bombnum = 3, player1.SetLive(1), player2.Bombnum = 3, player2.SetLive(1);
		r1.predir = 0, r1.dir = 0, r2.predir = 0, r2.dir = 0;
		bomb1.state = 4, bomb1.level = 1, bomb1.levelsecond = 0, bomb1.SetId(3);
		bomb2.state = 4, bomb2.level = 1, bomb2.levelsecond = 0, bomb2.SetId(4);
		rboom1.state = 4, rboom1.level = 1,rboom1.own = &r1, rboom1.SetId(5);
		rboom2.state = 4, rboom2.level = 1,rboom2.own = &r2, rboom2.SetId(6);
		r1.ownthebomb = &rboom1;
		r2.ownthebomb = &rboom2;
	}
	void InitMap()
	{
		int locx, locy,tool;
		for (int i = 0; i < 500; i++)
		{
			tool = rand() % 2 + 1;
			locx = rand() % 13;
			locy = rand() % 19;
			if (MAP[locx][locy] == '*')
			{
				if (tool == 1)
					MAPTool[locx][locy] = 1;
				else if (tool == 2)
					MAPTool[locx][locy] = 2;
			}
		}
	}
	void Welcome()
	{
		cout << "***********************************************************" << endl;
		cout << "         Welcome to zxy's Crazy Arcade                     " << endl;
		cout << "\n\n   Do you want to be a super Bombman ?" << endl;
		cout << "\n     Here !   Make your Dream Come True !" << endl;
		cout << "***********************************************************" << endl;
		system("pause");
		system("cls");

		cout << "In this world\n";
		cout << "'#' is the hard wall, which can't be bombed\n";
		cout << "'*' is the soft wall, which can be bombed\n";
		cout << "This game is for two players:" << endl;
		cout << "'A' is player1\n";
		cout << "'B' is player2\n";
		cout << " \n";
		cout << "Player1 use 'W S A D°Ø   to control the direciton\n";
		cout << "            'Space Key'  to put the bomb 'o'" << endl;
		cout << "Player2 use 'I K J L'    to control the direction\n";
		cout << "            'Return Key' to put the bomb 'o'" << endl;
		cout << "There are also two Robots 'R'\n";
		cout << "they can put the bomb too\n";
		system("pause");
		cout << "As for the treat, they are hiding in the soft wall:\n";
		cout << "'1' is for speeding up\n";
		cout << "'2' is for increasing your bomb power\n";
		cout << "\n NOW !\n";
		cout << "make good use of your bomb !\n";
		cout << "Control A and B\n";
		cout << "bomb the wall£¨pick up the treat and get scores.\n";
		cout << "Your mission is to bomb the opponent and win the game\n";
		cout << "oh ! Remember don't set yourself up!\n";
		cout << "Here we go!\n";
		system("pause");
		system("cls");
	}

	int main()
	{
		Welcome();
		InitMap();
		InitRole();
		display();
		int count = 1, times = 0;
		clock_t start , now = 0;
		start = clock();
		while (1)
		{
			now = clock();
			if ((now - start) / CLK_TCK == 600)
			{
				system("cls");
				cout << "You have already played for 10 min" << endl;
				cout << "HOW COULD YOU NOT KILL EACH OTHER" << endl;
				cout << "Game is over" << endl;
				if (player1.score > player2.score)
					cout << "Player 1 Win" << endl;
				else if(player1.score < player2.score)
					cout << "Player 2 Win" << endl;
				else
					cout << "oh ! DOGFALL" << endl;
				system("pause");
				break;
			}
			if (player1.GetLive() == 0)
			{
				system("cls");
				cout << "Player 1 died !!" << endl;
				cout << "Player 2 win !!" << endl;

				break;
			}
			else if (player2.GetLive() == 0)
			{
				system("cls");
				cout << "Player 2 died !!" << endl;
				cout << "Player 1 win !!" << endl;
				system("pause");
			}
			char ch;
                if (_kbhit())
				{
					ch = _getch();
					if (ch == 27)
						break;
					cur = clock();
					deal_with_input(ch);
					display();
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
