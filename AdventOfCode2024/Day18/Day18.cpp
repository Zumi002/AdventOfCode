#include "../Utility/SupportFunc.h"
#include "Day18.h"
#include <tuple>
#include <set>
#include <queue>

#define SIZE 71

void Day18()
{
	myFile in = myFile();
	in.Open("Day18/in.txt");
	in.ReadFile();

	vector<vector<int>> map(SIZE, vector<int>(SIZE, 0)), mapCopy(SIZE, vector<int>(SIZE, 0));

	for (int i = 0; i < 1024; i++)
	{
		auto strs = split(in.inputLines[i], ',');
		map[stoi(strs[1])][stoi(strs[0])] = 1;
	}

	for (int i = 1024; i < in.nol; i++)
	{
		auto strs = split(in.inputLines[i], ',');
		map = mapCopy;
		map[stoi(strs[1])][stoi(strs[0])] = 1;
		mapCopy = map;
		queue<pair<int, int>> q;
		q.push({ 0,0 });

		int moves = -1;
		bool exit = false;
		while (q.size() && !exit)
		{

			moves++;
			int s = q.size();
			for (int i = 0; i < s; i++)
			{
				auto p = q.front();
				q.pop();

				if (p.second >= SIZE || p.first >= SIZE || p.second < 0 || p.first < 0 || map[p.second][p.first] > 0)
					continue;
				if (p.second == SIZE - 1 && p.first == SIZE - 1)
				{
					exit = true;
					break;
				}
				map[p.second][p.first] = 2;
				q.push({ p.first,p.second + 1 });
				q.push({ p.first,p.second - 1 });
				q.push({ p.first + 1,p.second });
				q.push({ p.first - 1,p.second });
			}
		}
		if (!exit)
		{
			cout << stoi(strs[0]) << "," << stoi(strs[1]);
			break;
		}
	}

	

	int sum = 0;
}