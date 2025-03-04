#include "../Utility/SupportFunc.h"
#include "Day8.h"
#include <utility>
#include <set>
#include <unordered_map>

class freq
{
public:
	int x,y;
	freq(int X, int Y)
	{
		x = X;
		y = Y;
	}
};

void Day8()
{
	myFile in = myFile();
	in.Open("Day8/in.txt");
	in.ReadFile();
	int sum = 0;

	unordered_map<char, vector<freq>> ff;

	int n = in.nol;
	int m = in.inputLines[0].size();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (in.inputLines[i][j] != '.')
			{
				if (!ff.count(in.inputLines[i][j]))
				{
					ff[in.inputLines[i][j]] = vector<freq>();
				}
				ff[in.inputLines[i][j]].push_back(freq(j, i));
			}
		}
	}

	for (auto p : ff)
	{
		for (int i = 0; i < p.second.size(); i++)
		{
			for (int j = 0; j < p.second.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				freq a = p.second[i], b =  p.second[j];
				int dx = a.x - b.x;
				int dy = a.y - b.y;
				int x = a.x;
				int y = a.y;
				while (x >= 0 && x < m && y >= 0 && y < n)
				{
					in.inputLines[y][x] = '#';
					x += dx;
					y += dy;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << in.inputLines[i][j];
			if (in.inputLines[i][j] == '#')
			{
				
				sum++;
			}
		}
		cout << "\n";
	}

	cout << sum;
}