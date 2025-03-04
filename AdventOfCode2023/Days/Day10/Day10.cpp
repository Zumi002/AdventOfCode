#include "../../Utility/SupportFunc.h"
#include "Day10.h"
#include <Set>
#include <queue>

enum
{
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

int opposite(int dir)
{
	return ClampS(dir + 2, 4);
}

class Node
{
public:
	vector<int> ends;
	int dist = 0;
	char C;
	Node(char c)
	{
		C = c;
		switch (c)
		{
			case '|':
				ends.push_back(UP);
				ends.push_back(DOWN);
				break;
			case '-':
				ends.push_back(LEFT);
				ends.push_back(RIGHT);
				break;
			case 'F':
				ends.push_back(RIGHT);
				ends.push_back(DOWN);
				break;
			case 'L':
				ends.push_back(UP);
				ends.push_back(RIGHT);
				break;
			case 'J':
				ends.push_back(UP);
				ends.push_back(LEFT);
				break;
			case '7':
				ends.push_back(DOWN);
				ends.push_back(LEFT);
				break;
			case '.':
				break;
			default:
				cout << "Not recognized {" << c << "}\n";
		}
	}
	bool visit(int dir)
	{
		if (find(ends.begin(), ends.end(), opposite(dir)) != ends.end())
		{
			return true;
		}
		return false;
	}
	int getNextDir(int trav, int dir)
	{
		dist = trav;
		for (int a : ends)
		{
			if (a != opposite(dir))return a;
		}
		return -1;
	}
};

class Player
{
public:
	int X, Y;
	int Dir;
	int maxX, maxY;
	int trav = 0;
	Player(int x,int y,int dir,int boundX,int boundY)
	{
		X = x;
		Y = y;
		Dir = dir;
		maxX = boundX;
		maxY = boundY;
	}
	bool Go()
	{
		trav++;
		switch (Dir)
		{
			case UP:
				if (Y > 0)Y -= 1;
				else return false;
				break;
			case RIGHT:
				if (X < maxX)X += 1;
				else return false;
				break;
			case DOWN:
				if (Y <maxY)Y += 1;
				else return false;
				break;
			case LEFT:
				if (X > 0)X -= 1;
				else return false;
				break;
		}
	}
};

void Day10()
{
	myFile in = myFile();
	in.Open("Days/Day10/in.txt");
	in.ReadFile();
	int sum = 0;
	vector<vector<Node*>> map;
	vector<vector<char>> p2input;
	int sX=0, sY=0;
	vector<char> empty;
	for (int j = 0; j < in.inputLines[0].size(); j++)
	{
		empty.push_back(' ');
		empty.push_back(' ');
	}
	empty.push_back(' ');
	p2input.push_back(empty);
	for (int i = 0; i < in.nol; i++)
	{
		vector<Node*> tmp;
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			tmp.push_back(new Node(in.inputLines[i][j]));
			if (in.inputLines[i][j] == 'S')
			{
				sX = j;
				sY = i;
			}
		}
		map.push_back(tmp);
	}
	vector<Player*> p;
	for (int i = UP; i <= LEFT; i++)
	{
		p.push_back(new Player(sX, sY, i, in.inputLines[0].size(), in.nol));
	}
	set<int> active = {0,1};
	int farR=0, farL=in.inputLines[0].size()-1, farU=in.nol-1, farD=0;
	int far = 0;
	while (active.size())
	{
		int del = 0;
		for (int a : active)
		{
			
			if(!p[a]->Go())del+=(1<<a);
			else
			{
				//cout << "Player " << a + 1 << ": X=" << p[a]->X << ", Y=" << p[a]->Y << ", going" << p[a]->Dir << "\n";
				farD = max(farD, p[a]->Y);
				farL = min(farL, p[a]->X);
				farR = max(farR, p[a]->X);
				farU = min(farU, p[a]->Y);
				if (map[p[a]->Y][p[a]->X]->visit(p[a]->Dir))
				{
					if (map[p[a]->Y][p[a]->X]->dist != 0)
					{
						far = map[p[a]->Y][p[a]->X]->dist;
						active.clear();
						break;
					}
					else
					{
						int dir = map[p[a]->Y][p[a]->X]->getNextDir(p[a]->trav, p[a]->Dir);
						p[a]->Dir = dir;
					}
				}
				else del += (1 << a);
			}
		}
		if (del)
		{
			for (int i = 0; i < 4; i++)
			{
				if (del & (1 << i))active.erase(i);
			}
		}
	}
	cout << far;
	cout << "\n";

	for (int i = 0; i <in.nol; i++)
	{
		vector<char> p2tmp;
		p2tmp.push_back(' ');
		for (int j = 0; j <in.inputLines[0].size(); j++)
		{
			if (in.inputLines[i][j] == 'S')p2tmp.push_back('L');
			else if (in.inputLines[i][j] == '.' || map[i][j]->dist)
				p2tmp.push_back(in.inputLines[i][j]);
			else p2tmp.push_back('.');
			p2tmp.push_back(' ');
		}
		p2input.push_back(empty);
		p2input.push_back(p2tmp);
	}
	p2input.push_back(empty);
	for (int i = 1; i < p2input.size()-1; i++)
	{
		for (int j = 1; j < p2input[0].size()-1; j++)
		{
			if (p2input[i][j] == ' ')
			{
				if (p2input[i][j - 1] == 'L' || p2input[i][j - 1] == '-' || p2input[i][j - 1] == 'F')
				{
					if (p2input[i][j + 1] == '7' || p2input[i][j + 1] == '-' || p2input[i][j + 1] == 'J')
					{
						p2input[i][j] = '-';
					}
				}
				if (p2input[i - 1][j] == '|' || p2input[i - 1][j] == '7' || p2input[i - 1][j] == 'F')
				{
					if (p2input[i + 1][j] == '|' || p2input[i + 1][j] == 'J' || p2input[i + 1][j] == 'L')
					{
						p2input[i][j] = '|';
					}
				}
			}
		}
	}

	queue<pair<int, int>> q;
	set<pair<int, int>> ss;
	q.push({ 0,0 });
	while (q.size())
	{
		pair<int, int> h = q.front();
		q.pop();
		p2input[h.first][h.second] = '#';
		if (h.first > 0)
		{
			if (p2input[h.first - 1][h.second] == '.' || p2input[h.first - 1][h.second] == ' ')
			{
				if (!ss.count({ h.first - 1 ,h.second }))
				{
					q.push({ h.first - 1 ,h.second });
					ss.insert({ h.first - 1 ,h.second });
				}
			}
		}
		if (h.first < p2input.size()-1)
		{
			if (p2input[h.first + 1][h.second] == '.' || p2input[h.first + 1][h.second] == ' ')
			{
				if (!ss.count({ h.first + 1 ,h.second }))
				{
					q.push({ h.first + 1 ,h.second });
					ss.insert({ h.first + 1 ,h.second });
				}
			}
		}
		if (h.second > 0)
		{
			if (p2input[h.first][h.second-1] == '.' || p2input[h.first][h.second-1] == ' ')
			{
				if (!ss.count({ h.first ,h.second-1 }))
				{
					q.push({ h.first  ,h.second-1 });
					ss.insert({ h.first  ,h.second-1 });
				}
			}
		}
		if (h.second < p2input[0].size() - 1)
		{
			if (p2input[h.first][h.second+1] == '.' || p2input[h.first][h.second+1] == ' ')
			{
				if (!ss.count({ h.first ,h.second + 1 }))
				{
					q.push({ h.first  ,h.second + 1 });
					ss.insert({ h.first  ,h.second + 1 });
				}
			}
		}
	}
	int p2ans = 0;
	for (int i = 0; i < p2input.size(); i++)
	{
		for (int j = 0; j < p2input[0].size(); j++)
		{
			
			if (p2input[i][j] == '.')p2ans++;
			cout << p2input[i][j];
		}
		cout << "\n";
	}
	cout << "\n" << p2ans;
	
}
