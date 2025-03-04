#include "../Utility/SupportFunc.h"
#include "Day20.h"
#include <queue>
#include <unordered_map>

struct race
{
	bool cheated = false;
	int cheatStart, cheatEnd;
	int x, y;
	race(int X, int Y)
	{
		x = X;
		y = Y;
	}
};

vector<vector<int>> BFS(vector<string> map, pair<int, int> start, pair<int, int> end)
{
	queue<pair<int, int>> q;
	q.push(start);

	int secs = 0;

	int ymax = map.size();
	int xmax = map[0].size();

	vector<vector<int>> res(ymax, vector<int>(xmax, -1));

	while (q.size())
	{
		int sizee = q.size();
		int same = 0;
		for (int i = 0; i < sizee; i++)
		{
			auto p = q.front();
			q.pop();
			if (res[p.first][p.second] != -1 || map[p.first][p.second] != '.')
				continue;
			same++;
			res[p.first][p.second] = secs;
			if (p == end)
			{
				break;
			}

			if (p.first > 0)
			{
				q.push({ p.first - 1,p.second });
			}
			if (p.first < ymax - 1)
			{
				q.push({ p.first + 1,p.second });
			}
			if (p.second > 0)
			{
				q.push({ p.first ,p.second - 1 });
			}
			if (p.second < xmax - 1)
			{
				q.push({ p.first,p.second + 1 });
			}
		}
		if (res[end.first][end.second]!=-1)
			break;
		secs++;
	}

	return res;
}

vector<pair<pair<pair<int, int>, pair<int, int>>, int>> findCheats(vector<vector<int>> dist,vector<string> map)
{
	

	int ymax = map.size();
	int xmax = map[0].size();

	vector<pair<pair<pair<int, int>, pair<int, int>>, int>> res;

	

	for (int i = 0; i < ymax; i++)
	{
		for (int j = 0; j < xmax; j++)
		{
			if (dist[i][j] == -1)
				continue;
			vector<vector<bool>> was(ymax, vector<bool>(xmax, false));

			queue<pair<int, int>> q;
			q.push({ i,j });

			int timer = 20;

			while (q.size()&&timer>=0)
			{
				int sizee = q.size();
				for (int k = 0; k < sizee; k++)
				{
					auto p = q.front();
					q.pop();
					if (was[p.first][p.second])
						continue;
					was[p.first][p.second] = true;
					if (map[p.first][p.second] == '.'&&(p != pair<int,int>{i,j}))
					{

						if (p.first > 0)
						{
							q.push({ p.first - 1,p.second });
						}
						if (p.first < ymax - 1)
						{
							q.push({ p.first + 1,p.second });
						}
						if (p.second > 0)
						{
							q.push({ p.first ,p.second - 1 });
						}
						if (p.second < xmax - 1)
						{
							q.push({ p.first ,p.second + 1 });
						}
						if (dist[i][j] + 20 - timer < dist[p.first][p.second])
						{
							res.push_back({ {{i,j},{p.first,p.second}}, dist[p.first][p.second] - dist[i][j] - 20 + timer });
						}
					}
					else
					{
						if (p.first > 0)
						{
							q.push({ p.first - 1,p.second });
						}
						if (p.first < ymax-1)
						{
							q.push({ p.first + 1,p.second });
						}
						if (p.second > 0)
						{
							q.push({ p.first ,p.second -1});
						}
						if (p.second < xmax-1)
						{
							q.push({ p.first ,p.second+1 });
						}
					}
				}
				timer--;
			}
		}
	}

	return res;
}

void Day20()
{
	myFile in = myFile();
	in.Open("Day20/in.txt");
	in.ReadFile();

	int sum = 0;
	
	pair<int, int> start, end;

	vector<string> map;

	for (int i = 0; i < in.nol; i++)
	{
		string lane = "";
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == 'S')
			{
				lane += '.';
				start = { i,j };
			}
			else if (in.inputLines[i][j] == 'E')
			{
				lane += '.';
				end = { i,j };
			}
			else
			{
				lane += in.inputLines[i][j];
			}
		}
		map.push_back(lane);
	}

	auto res = BFS(map, start, end);
	unordered_map<int, int> count;
	for (auto ppp : findCheats(res, map))
	{
		auto pp = ppp.first;
		pair<int, int> st = pp.first;
		pair<int, int> en = pp.second;
		int save = ppp.second;

		if (save >= 100)
			sum++;

		count[save]++;

		//cout << st.second << ", " << st.first << " : " << en.second << ", " << en.first << " - dist saved " << save << "\n";
	}

	for (auto p : count)
	{
		//if(p.first>=50)
		//cout << "There is " << p.second << " cheats that saves " << p.first << " seconds\n";
	}

	cout<<"\n" << sum;
}