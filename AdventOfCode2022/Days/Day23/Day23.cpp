#include "../../Utility/SupportFunc.h"
#include "Day23.h"
#include <set>

#define SIZE 1000

class Elf
{
	public: 
	int x, y;

	int wantToMove = 0;
	int reserved = 0;
	int possibleMoves[4] = {0,0,0,0};

};

char map[SIZE][SIZE];

void printMap()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << map[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}

void Day23()
{
	myFile in = myFile();
	in.Open("Days/Day23/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;

	vector<Elf*> elfs;
	vector<vector<pair<int,int>>> dir;

	vector<pair<int, int>> ups;

	ups.push_back(make_pair(-1, -1));
	ups.push_back(make_pair(-1, 0));
	ups.push_back(make_pair(-1, 1));

	vector<pair<int, int>> downs;

	downs.push_back(make_pair(1, -1));
	downs.push_back(make_pair(1, 0));
	downs.push_back(make_pair(1, 1));

	vector<pair<int, int>> rights;

	rights.push_back(make_pair(1, 1));
	rights.push_back(make_pair(0, 1));
	rights.push_back(make_pair(-1, 1));

	vector<pair<int, int>> lefts;

	lefts.push_back(make_pair(1, -1));
	lefts.push_back(make_pair(0, -1));
	lefts.push_back(make_pair(-1, -1));

	dir.push_back(ups);
	dir.push_back(downs);
	dir.push_back(lefts);
	dir.push_back(rights);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			map[i][j] = '.';
		}
	}
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == '#')
			{
				Elf* a = new Elf();
				a->x = SIZE/2-50 + j;
				a->y = SIZE/2-50 + i;

				map[SIZE/2-50 + i][SIZE/2-50 + j] = '#';
				elfs.push_back(a);
			}
		}
	}

	set<pair<int, int>> reserved;
	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		for (Elf* a : elfs)
		{
			int y = a->y;
			int x = a->x;
			if (map[y + 1][x] == '#' || map[y + 1][x + 1] == '#' ||
				map[y][x + 1] == '#' || map[y - 1][x + 1] == '#' ||
				map[y - 1][x] == '#' || map[y - 1][x - 1] == '#' ||
				map[y][x - 1] == '#' || map[y + 1][x - 1] == '#')
			{
				a->wantToMove = 1;
			}
			else
			{
				a->wantToMove = 0;
			}
		}
		int moving = 0;
		for (Elf* a : elfs)
		{
			if (a->wantToMove)
			{
				moving += 1;
			}
		}
		if (moving == 0) break;
		for (Elf* a : elfs)
		{
			
			if (a->wantToMove)
			{
				int y = a->y;
				int x = a->x;
				for (int j = 0; j < 4; j++)
				{
					if (map[y + dir[j][0].first][x + dir[j][0].second] != '#' && map[y + dir[j][1].first][x + dir[j][1].second] != '#' && map[y + dir[j][2].first][x + dir[j][2].second] != '#'&&a->reserved!=1)
					{
						int b = 0;
						if (dir[j][0].first == dir[j][1].first && dir[j][0].first == 1)
						{
							b = 1;
						}
						else if (dir[j][0].second == dir[j][1].second && dir[j][0].second == 1)
						{
							b = 2;
						}
						else if (dir[j][0].second == dir[j][1].second && dir[j][0].second == -1)
						{
							b = 3;
						}
						//cout << b << "\n";
						a->possibleMoves[b] = 1;
						a->reserved = 1;
						if (map[y + dir[j][1].first][x + dir[j][1].second] != 'R')
						{
							map[y + dir[j][1].first][x + dir[j][1].second] = 'R';
						}
						else
						{
							map[y + dir[j][1].first][x + dir[j][1].second] = 'F';
						}
						reserved.insert(make_pair(y + dir[j][1].first, x + dir[j][1].second));
					}
				}
			}
			
		}
		//printMap();
		for (Elf* a : elfs)
		{
			if (a->wantToMove)
			{
				a->reserved = 0;
				int y = a->y;
				int x = a->x;
				if (a->possibleMoves[0] == 1)
				{
					a->possibleMoves[0] = 0;
					a->possibleMoves[1] = 0;
					a->possibleMoves[2] = 0;
					a->possibleMoves[3] = 0;
					if (map[y - 1][x] == 'R')
					{
						//cout << "xd";
						map[y][x] = '.';
						map[y - 1][x] = '#';
						a->y -= 1;
						
					}
				}
				else if (a->possibleMoves[1] == 1)
				{
					
					a->possibleMoves[0] = 0;
					a->possibleMoves[1] = 0;
					a->possibleMoves[2] = 0;
					a->possibleMoves[3] = 0;
					if (map[y + 1][x] == 'R')
					{
						//cout << "xd";
						map[y][x] = '.';
						map[y + 1][x] = '#';
						a->y += 1;
						
					}
				}
				else if (a->possibleMoves[2] == 1)
				{
					a->possibleMoves[0] = 0;
					a->possibleMoves[1] = 0;
					a->possibleMoves[2] = 0;
					a->possibleMoves[3] = 0;
					if (map[y][x + 1] == 'R')
					{
						//cout << "xd";
						map[y][x] = '.';
						map[y][x + 1] = '#';
						a->x += 1;
						
					}
				}
				else if (a->possibleMoves[3] == 1)
				{
					a->possibleMoves[0] = 0;
					a->possibleMoves[1] = 0;
					a->possibleMoves[2] = 0;
					a->possibleMoves[3] = 0;
					if (map[y][x - 1] == 'R')
					{
						//cout << "xd";
						map[y][x] = '.';
						map[y][x - 1] = '#';
						//cout << a->x << " ";
						a->x -= 1;
						//cout << a->x << " ";
						
					}
				}
			}
		}
		
		for (pair<int, int> a : reserved)
		{
			if (map[a.first][a.second] != '#')
			{
				map[a.first][a.second] = '.';
			}
		}
		reserved.clear();

		vector<pair<int, int>> tmp = dir[0];
		for (int j = 0; j < 3; j++)
		{
			dir[j] = dir[j + 1];
		}
		dir[3] = tmp;
	}
	int minX = SIZE, maxX = 0,
		minY = SIZE, maxY = 0;

	for (Elf* a : elfs)
	{
		if (a->x > maxX)
		{
			maxX = a->x;
		}
		if (a->x < minX)
		{
			minX = a->x;
		}
		if (a->y > maxY)
		{
			maxY = a->y;
		}
		if (a->y < minY)
		{
			minY = a->y;
		}
	}

	// VISUALS
	//for (int i = minY; i < maxY + 1; i++)
	//{
	//	for (int j = minX; j < maxX + 1; j++)
	//	{
	//		cout << map[i][j];
	//		if (map[i][j] == '.')sum++;
	//	}
	//	cout << "\n";
	//}

	cout << sum<< " " <<i;
}