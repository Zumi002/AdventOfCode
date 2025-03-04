#include "../../Utility/SupportFunc.h"
#include "Day10.h"
#include <Windows.h>
#include <queue>
#include <set>
#include <stack>

int reachable(int i, int j, myFile& in);

void Day10()
{
	myFile in = myFile();
	in.Open("Days/Day10/in.txt");
	in.ReadFile();

	int sum   = 0;

	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == '0')
			{
				sum += reachable(i, j, in);
			}
		}
	}

	cout << sum;
}

int reachable(int ii, int jj, myFile& in)
{
	stack<pair<int, int>> reach;
	reach.push({ ii, jj });
	set<pair<int, int>> ends;
	int score = 0;
	while (reach.size())
	{
		int i = reach.top().first;
		int j = reach.top().second;
		int h = in.inputLines[reach.top().first][reach.top().second]+1;
		reach.pop();
		if (i >= 1 && in.inputLines[i-1][j]==h)
		{
			reach.push({ i - 1,j });
		}
		if (j >= 1 && in.inputLines[i][j-1] == h)
		{
			reach.push({ i,j-1 });
		}
		if (i < in.nol-1 && in.inputLines[i + 1][j] == h)
		{
			reach.push({ i + 1,j });
		}
		if (j <in.inputLines[0].size() && in.inputLines[i][j+1] == h)
		{
			reach.push({ i,j+1 });
		}
		if (in.inputLines[i][j] == '9')
		{
			
				score++;
			
		}
	}
	return score;
}
