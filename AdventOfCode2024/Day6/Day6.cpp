#include "../Utility/SupportFunc.h"
#include "Day6.h"
#include <queue>


struct guard
{
	int x;
	int y;

	int dir = 0;

	guard(int X, int Y)
	{
		x = X;
		y = Y;
	}

	void step()
	{
		if (dir == 0)
		{
			y--;
		}
		else if (dir == 1)
		{
			x++;
		}
		else 	if (dir == 2)
		{
			y++;
		}
		else if (dir == 3)
		{
			x--;
		}
	}
};



void Day6()
{
	myFile in = myFile();
	in.Open("Day6/in.txt");
	in.ReadFile();

	int sum = 0;
	guard g = guard (0,0);
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == '^')
			{
				g = guard(j, i);
			}
		}
	}
	guard start = g;
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] != '.')
				continue;
			in.inputLines[i][j] = '#';
			int l = 0;
			while (g.x >= 0 && g.x < in.inputLines[0].size() && g.y >= 0 && g.y < in.nol)
			{
				while (1 == 1)
				{
					guard k = g;
					k.step();
					if (k.x >= 0 && k.x < in.inputLines[0].size() && k.y >= 0 && k.y < in.nol)
					{
						if (in.inputLines[k.y][k.x] == '#')
						{
							g.dir++;
							g.dir %= 4;
						}
						else
						{
							g.step();
							break;
						}
					}
					else
					{
						g.step();
						break;
					}
				}
				l++;
				if (l > 9000)
				{
					sum++;
					break;
				}

			}
			g = start;
			in.inputLines[i][j] = '.';
		}
	}
	/*
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == 'X')
				sum++;
		}
	}*/

	cout << sum;

}