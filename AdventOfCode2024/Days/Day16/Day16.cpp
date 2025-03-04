#include "../../Utility/SupportFunc.h"
#include "Day16.h"
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>

struct deer
{
	int x, y;
	int dir;
	int score = 0;

	deer(int X, int Y, int Score, int dirr)
	{
		x = X;
		y = Y;
		score = Score;
		dir = dirr;
	}

	deer()
	{
		x = 0;
		y = 0;
		dir = 0;
		score = INT_MAX;
	}

	bool checkMove(vector<string>& map, int moveDir)
	{
		int dx = 0, dy = 0;
		if (moveDir == 0)
		{
			dx++;
		}
		if (moveDir == 1)
		{
			dy++;
		}
		if (moveDir == 2)
		{
			dx--;
		}
		if (moveDir == 3)
		{
			dy--;
		}

		if ((moveDir + 2) % 4 == dir)
			return false;

		if (map[y + dy][x + dx] != '#')
			return true;
		return false;
	}

	deer move(vector<string>& map, int moveDir)
	{
		int dx = 0, dy = 0;
		if (moveDir == 0)
		{
			dx++;
		}
		if (moveDir == 1)
		{
			dy++;
		}
		if (moveDir == 2)
		{
			dx--;
		}
		if (moveDir == 3)
		{
			dy--;
		}

		int lscore = score + 1;

		if (dir != moveDir)
		{
			lscore += 1000;
		}

		return deer(x + dx, y + dy, lscore, moveDir);
	}

	deer backTrack()
	{
		int dx = 0, dy = 0;
		if (dir == 0)
		{
			dx--;
		}
		if (dir == 1)
		{
			dy--;
		}
		if (dir == 2)
		{
			dx++;
		}
		if (dir == 3)
		{
			dy++;
		}

		return deer(x + dx, y + dy, score, dir);
	}
};

int hashpos(int x, int y)
{
	return 1000 * x + y;
}

void Day16()
{
	myFile in = myFile();
	in.Open("Days/Day16/in.txt");
	in.ReadFile();

	unordered_map<int, vector<deer>> best;

	vector<string> map;

	int sum = 0;
	pair<int, int> start, end;
	for (int i = 0; i < in.nol; i++)
	{
		map.push_back(in.inputLines[i]);
		for (int j = 0; j < in.inputLines[0].size(); j++)
		{
			if (in.inputLines[i][j] == 'S')
			{
				start = { i,j };
			}
			if (in.inputLines[i][j] == 'E')
			{
				end = { i,j };
			}
		}
	}

	deer first = deer(start.second, start.first, 0, 0);

	stack<deer> q;

	q.push(first);

	while (q.size())
	{
		deer d = q.top();
		q.pop();
		if (best.find(hashpos(d.x, d.y)) != best.end())
		{
			if (best[hashpos(d.x, d.y)][d.dir].score < d.score)
			{
				continue;
			}
			best[hashpos(d.x, d.y)][d.dir] = d;

		}
		else
		{
			best[hashpos(d.x, d.y)] = vector<deer>(4);
			best[hashpos(d.x, d.y)][d.dir] = d;
		}
		for (int i = 0; i < 4; i++)
		{
			if (d.checkMove(map, i))
			{
				q.push(d.move(map, i));
			}
		}

	}

	//backTrack
	int minnn = INT_MAX;
	for (auto kk : best[hashpos(end.second, end.first)])
	{
		minnn = min(minnn, kk.score);
	}
	for (auto k : best[hashpos(end.second, end.first)])
	{
		if (k.score != minnn)
			continue;
		q.push(k);
		while (q.size())
		{
			k = q.top();
			q.pop();
			map[k.y][k.x] = 'O';

			deer w = k.backTrack();
			if (best.find(hashpos(w.x, w.y)) == best.end())
				continue;
			int minn = best[hashpos(w.x, w.y)][0].score;

			for (auto kk : best[hashpos(w.x, w.y)])
			{
				if ((kk.score==k.score-1&&kk.dir==k.dir)||(kk.score==k.score-1001&&kk.dir!=k.dir))
					q.push(kk);
			}

			map[k.y][k.x] = 'O';
		}
	}

	int seats = 0;

	for (int i = 0; i < map.size(); i++)
	{
		cout << map[i] << "\n";
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 'O')
				seats++;
		}
	}
	cout << "\n";


	cout << minnn << " " << seats;
}