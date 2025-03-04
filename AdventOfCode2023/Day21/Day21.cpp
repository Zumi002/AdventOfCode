#include "../Utility/SupportFunc.h"
#include "Day21.h"
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <set>


void trav(pair<int,int> start, vector<string>&map,vector<vector<int>> &res,int w)
{
	vector<vector<int>> dir = { {-1,0},{0,1},{1,0},{0,-1} };
	queue<pair<int, int>> q;
	set<pair<int, int>> ss;
	ss.insert(start);
	q.push(start);

	for (int i = 0; i < map.size()*2; i++)
	{
		int k = q.size();
		for (int j = 0; j < k; j++)
		{
			pair<int, int> h = q.front();
			q.pop();
			for (auto a : dir)
			{
				if (h.first + a[0] >= 0 && h.first + a[0] < map.size() && h.second + a[1] >= 0 && h.second + a[1] < map[0].size())
				{
					if (map[h.first + a[0]][h.second + a[1]] != '#')
					{
						if (!ss.count({ h.first + a[0],h.second + a[1] }))
						{
							q.push({ h.first + a[0],h.second + a[1] });
							ss.insert({ h.first + a[0],h.second + a[1] });
						}
					}
				}
			}
		}
		res[w][i] = q.size();
		ss.clear();
	}
}


void Day21()
{
	myFile in = myFile();
	in.Open("Day21/in.txt");
	in.ReadFile();

	vector<string> map;
	pair<int, int> start;
	for (int i = 0; i < in.nol; i++)
	{
		map.push_back(in.inputLines[i]);
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == 'S')
			{
				start = { i,j };
			}
		}
	}

	long long s = map.size();

	vector<vector<int>> from(9, vector<int>(s * 2, 0));
	trav(start, map, from, 0);
	trav({0,0}, map, from, 1);
	trav({0,s/2}, map, from, 5);
	trav({0,s-1}, map, from, 2);
	trav({s/2,0}, map, from, 6);
	trav({s/2,s-1}, map, from, 7);
	trav({s-1,0}, map, from, 3);
	trav({s-1,s/2}, map, from, 8);
	trav({s-1,s-1}, map, from, 4);

	vector<int> cycl = { from[8][2*s-2],from[8][2*s - 1] };

	//cout << cycl[0] << " " << cycl[1]<<"\n";

	long long steps = 26501365;
	long long res = 0;
	if (steps < s / 2)
	{
		cout << from[0][steps - 1]<<"\n";
	}
	else
	{
		long long n = (steps-s/2) / (s);
		long long k = (steps-s/2) % s;
		//cout << k << " " << n * s + k << "\n";
		int even = ((steps % 2) == 0);
		//cout << n*n * cycl[even]<<" \n";
		res += n * n * cycl[even];
		cout << (n-1) * (n-1) * cycl[even?0:1] << " \n";
		res += (n - 1) * (n - 1) * cycl[even?0:1];
		
		//cout << "--k--"<<k<<" \n";
		for (int i = 1; i <= 4; i++)
		{
			//cout << from[i+4][s - 2] << "\n";
			//cout << (n - 1) * from[i][s + s / 2 - 2] << "\n";
			res += from[i+4][s-2];
			res += (n-1) * from[i][s +s/2- 2];
		}
		for (int i = 1; i <= 4; i++)
		{
			//cout << (n ) * from[i][s/2-2] << "\n";
			res += (n) * from[i][s/2-2];
		}
		
	}

	cout <<from[0][64-1]<<" "<< res;
}