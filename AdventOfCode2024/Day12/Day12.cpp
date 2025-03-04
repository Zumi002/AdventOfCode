#include "../Utility/SupportFunc.h"
#include "Day12.h"
#include <utility>
#include <set>
#include <queue>
#include <stack>

int fill(myFile &in, vector<vector<int>>& seen,int x ,int y)
{
	stack<pair<int, int>> q;
	q.push({ y,x });
	char lf = in.inputLines[y][x];
	int area = 0;
	int peri = 0;
	while (q.size())
	{
		auto p = q.top();
		int i = p.first;
		int j = p.second;
		q.pop();

		if (seen[i][j])
			continue;
		area++;
		int localperi = 0;
		int otherperi = 0;
		if (i > 0)
		{
			if (in.inputLines[i - 1][j] == lf)
			{
				otherperi |= seen[i-1][j];
				q.push({ i - 1,j });
			}
			else
			{
				localperi += 1;
				
			}
		}
		else
		{
			localperi += 1;
			
		}
		if (j > 0)
		{
			if (in.inputLines[i][j-1] == lf)
			{
				otherperi |= seen[i][j-1];
				q.push({ i,j-1 });
			}
			else
			{
				localperi += 2;
				
			}
		}
		else
		{
			localperi += 2;
			
		}
		
		if (j < in.inputLines[0].size()-1)
		{
			if (in.inputLines[i][j + 1] == lf)
			{
				otherperi |= seen[i][j+1];
				q.push({ i,j + 1 });
			}
			else
			{
				localperi += 4;
				
			}
		}
		else
		{
			localperi += 4;
			
		}
		if (i < in.nol - 1)
		{
			if (in.inputLines[i+1][j] == lf)
			{
				otherperi |= seen[i+1][j];
				q.push({ i+1,j });
			}
			else
			{
				localperi += 8;
				
			}
		}
		else
		{
			localperi += 8;

		}
		for (int i = 1; i <= 8; i *= 2)
		{
			if ((otherperi & i) == 0 && (localperi & i) != 0)
			{
				peri++;
			}
			
		}
		if (j > 0 && j < in.inputLines[0].size()-1)
		{
			if (in.inputLines[i][j] == in.inputLines[i ][j+1] && in.inputLines[i][j] == in.inputLines[i ][j-1])
			{
				if ((seen[i][j - 1] & 8) == 8 && (seen[i][j + 1] & 8) == 8 && (localperi & 8) == 8)
				{
					peri--;
				}
				if ((seen[i][j - 1] & 1) == 1 && (seen[i][j + 1] & 1) == 1 && (localperi & 1) == 1)
				{
					peri--;
				}
			}
		}
		if (i > 0 && i < in.nol-1)
		{
			if (in.inputLines[i][j] == in.inputLines[i + 1][j] && in.inputLines[i][j] == in.inputLines[i - 1][j])
			{
				if ((seen[i + 1][j] & 2) == 2 && (seen[i - 1][j] & 2) == 2 && (localperi & 2) == 2)
				{
					peri--;
				}
				if ((seen[i + 1][j] & 4) == 4 && (seen[i - 1][j] & 4) == 4 && (localperi & 4) == 4)
				{
					peri--;
				}
			}
		}
		seen[i][j] = localperi+16;
	}
	cout << lf << " " << peri << " " << area << " \n";
	return peri * area;
}


void Day12()
{
	myFile in = myFile();
	in.Open("Day12/in.txt");
	in.ReadFile();


	int sum = 0;
	vector<vector<int>> seen(in.nol, vector<int>(in.inputLines[0].size()));
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[0].size(); j++)
		{
			if (!seen[i][j])
			{
				sum += fill(in, seen, j, i);
			}
		}
	}

	cout << sum;
}			