#include "../../Utility/SupportFunc.h"
#include "Day23.h"
#include <set>
#include <stack>
#include <unordered_map>
#include <queue>

enum
{
	U =0,
	R,
	D,
	L
};



class crossRoad
{
public:
	vector<bool> entry;
	int entered;
	vector<bool> checked;
	int y, x;
	int movesTo;
	int longest = -1;
	vector<int> dist;
	vector<crossRoad*> con;
	crossRoad(int y,int x,int mt)
	{
		this->y = y;
		this->x = x;
		entry = vector<bool>(4, false);
		checked = vector<bool>(4, false);
		con = vector<crossRoad*>(4, NULL);
		dist = vector<int>(4, 0);
		movesTo = mt;
	}

	bool Chcecked()
	{
		for (int i = 0; i < 4; i++)
		{
			if (entry[i] != checked[i])return false;
		}
		return true;
	}

	void check(int steps)
	{
		longest = max(longest, steps);
		for (int i = 0; i < 4; i++)
		{
			if (entry[i] != checked[i])
			{
				checked[i] = entry[i];
				break;
			}
		}
	}

	int goNext()
	{
		for (int i = 0; i < 4; i++)
		{
			if (entry[i] != checked[i])return i;
		}
		return -1;
	}

};

vector<int> possibleDir(vector<string>& s, int y, int x,int from)
{
	vector<vector<int>> dir = { {-1,0},{0,1},{1,0},{0,-1} };
	vector<int> res;
	for (int i =0;i<4;i++)
	{
		if (from +2==i||from-2==i)continue;
		vector<int> d = dir[i];
		int yy = y + d[0];
		int xx = x + d[1];
		if (yy >= 0 && yy < s.size() && xx >= 0 && xx < s[0].size())
		{
			//P1 == '.'
			if (s[yy][xx] != '#')
			{
				res.push_back(i);
			}
			else if (s[yy][xx] == '^' && i == U)
			{
				res.push_back(i);
			}
			else if (s[yy][xx] == '>' && i == R)
			{
				res.push_back(i);
			}
			else if (s[yy][xx] == 'v' && i == D)
			{
				res.push_back(i);
			}
			else if (s[yy][xx] == '<' && i == L)
			{
				res.push_back(i);
			}
		}
	}
	return res;
}

int op(int a)
{
	return a - 2 >= 0 ? a - 2 : a + 2;
}

int C(int l, int r)
{
	return (l + r) * (l + r + 1) / 2 + r;
}

void Day23()
{
	myFile in = myFile();
	in.Open("Days/Day23/in.txt");
	in.ReadFile();

	vector<vector<int>> dir = { {-1,0},{0,1},{1,0},{0,-1} };
	vector<string> map;

	for (int i = 0; i < in.nol; i++)
	{
		map.push_back(in.inputLines[i]);
	}
	int y=0, x=1;

	stack<crossRoad*> aha;
	queue<crossRoad*> q;
	set<int> v;
	unordered_map<int, crossRoad*> CrossBPos;
	crossRoad* start = new crossRoad(0, 1,0);

	start->entered = D;
	for (int a : possibleDir(map,0,1,D))start->entry[a] = true;
	CrossBPos[C(0, 1)] = start;
	aha.push(start);
	q.push(start);
	v.insert(C(0,1));
	int steps = 0;
	bool onCross = true;
	int dd = D;
	while (q.size())
	{
		for (int i = 0; i < 4; i++)
		{
			if (q.front()->entry[i]&&q.front()->dist[i]==0)
			{
				x = q.front()->x + dir[i][1];
				y = q.front()->x + dir[i][0];
				dd = i;
				auto poss = possibleDir(map, y, x, dd);
				int steps = 1;
				while (poss.size()==1)
				{
					x += dir[poss[0]][1];
					y += dir[poss[0]][1];
					steps++;
				}
				if (poss.size() == 0)
				{

					break;
				}
				if (!v.count(C(y, x)))
				{
					crossRoad* r = new crossRoad(y, x, steps);
					for (int a : poss)r->entry[a] = true;
					r->entry[op(dd)] = true;
					r->con[op(dd)] = q.front();
					r->dist[op(dd)] = steps;
					q.front()->dist[i] = steps;
					q.front()->con[i] = r;

				}
			}
		}
	}
	/*
	while (aha.size())
	{
		if (x == map[0].size() - 2 && y == map.size() - 1&&!onCross)
		{
			aha.top()->check(steps);
			onCross = true;
			while (aha.top()->Chcecked())
			{
				steps = aha.top()->longest + aha.top()->movesTo;
				CrossBPos[C(aha.top()->y, aha.top()->x)] = NULL;
				crossRoad* r = aha.top();
				aha.pop();
				delete r;
				if (!aha.size())break;
				aha.top()->check(steps);
			}
			continue;
		}
		vector<int> d;
		if (onCross)
		{
			steps = 0;
			dd = aha.top()->goNext();
			d = dir[dd];
			x = aha.top()->x;
			y = aha.top()->y;
			onCross = false;
		}
		else
		{
			auto poss = possibleDir(map, y, x,dd);
			if (poss.size() > 1)
			{
				if (CrossBPos.count(C(y, x)) && CrossBPos[C(y, x)] != NULL)
				{
					aha.top()->check(-1);
					while (aha.top()->Chcecked())
					{
						steps = aha.top()->longest + aha.top()->movesTo;
						if (aha.top()->longest == -1) steps = -1;
						CrossBPos[C(aha.top()->y, aha.top()->x)] = NULL;
						crossRoad* r = aha.top();
						aha.pop();
						delete r;
						if (!aha.size())break;
						aha.top()->check(steps);
					}
					onCross = true;
					continue;
				}
				onCross = true;
				aha.push(new crossRoad(y, x, steps));
				CrossBPos[C(y, x)] = aha.top();
				for (int a : poss)aha.top()->entry[a] = 1;
				continue;
			}
			d = dir[poss[0]];
			dd = poss[0];

		}
		steps++;
		x += d[1];
		y += d[0];
		
	}*/
	
	std::cout << steps;

	
}