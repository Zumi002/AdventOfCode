#include "../../Utility/SupportFunc.h"
#include "Day22.h"
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Brick
{
public:
	int id;
	int changeIn;
	vector<vector<int>>ends;
	vector<vector<vector<int>>> &brickMap;
	unordered_map<int, Brick*> &bricks;
	vector<Brick*> above;
	vector<Brick*> under;

	Brick(int i,int ch,vector<vector<int>> e,vector<vector<vector<int>>> &bmap,unordered_map<int,Brick*> &b):brickMap(bmap),bricks(b)
	{
		id = i;
		changeIn = ch;
		ends = e;
	}

	void fall()
	{
		
		for (int x = ends[0][0]; x <= ends[1][0]; x++)
		{
			for (int y = ends[0][1]; y <= ends[1][1]; y++)
			{
				for (int z = ends[0][2]; z <= ends[1][2]; z++)
				{
					brickMap[x][y][z] = -1;
				}
			}
		}
		unordered_set<int>hits;
		bool hit = 0;
		int upZ = ends[0][2];
		while (!hit && upZ != 1)
		{
			for (int x = ends[0][0]; x <= ends[1][0]; x++)
			{
				for (int y = ends[0][1]; y <= ends[1][1]; y++)
				{
					if (brickMap[x][y][upZ-1] != -1)
					{
						hit = true;
						hits.insert(brickMap[x][y][upZ - 1]);
					}
				}
			}
			if (!hit)upZ -= 1;
		}
		int diff = ends[1][2] - ends[0][2];
		ends[0][2] = upZ;
		ends[1][2] = upZ + diff;
		for (int x = ends[0][0]; x <= ends[1][0]; x++)
		{
			for (int y = ends[0][1]; y <= ends[1][1]; y++)
			{
				for (int z = ends[0][2]; z <= ends[1][2]; z++)
				{
					brickMap[x][y][z] = id;
				}
			}
		}
		for (int b : hits)
		{
			under.push_back(bricks[b]);
			bricks[b]->onTop(this);
		}
	}

	void onTop(Brick* b)
	{
		above.push_back(b);
	}

	bool canDestory()
	{
		for (auto b : above)
		{
			if (b->under.size() == 1)return false;
		}
		return true;
	}

	int destroyFalls()
	{
		unordered_set<int> s = {id};
		queue<int> q;
		q.push(id);
		while (q.size())
		{
			Brick* b = bricks[q.front()];
			q.pop();
			for (auto bb : b->above)
			{
				if (bb->willCauseFall(s))
				{
					q.push(bb->id);
					s.insert(bb->id);
				}
			}
		}
		return s.size()-1;
	}

	bool willCauseFall(unordered_set<int> &o)
	{
		for (auto b : under)
		{
			if (!o.count(b->id)) return false;
		}
		return true;
	}

};

void Day22()
{
	myFile in = myFile();
	in.Open("Days/Day22/in.txt");
	in.ReadFile();

	vector<vector<vector<int>>> allEnds;

	for (int i = 0; i < in.nol; i++)
	{
		vector<string> ends = split(in.inputLines[i], '~');
		vector<vector<int>> intEnds(2,vector<int>(3,0));
		for (int j = 0; j < 2; j++)
		{
			vector<string>coords = split(ends[j], ',');
			for (int k = 0; k < 3; k++)
			{
				intEnds[j][k] = atoi(coords[k].c_str());
			}
		}
		allEnds.push_back(intEnds);
	}

	sort(allEnds.begin(), allEnds.end(), [](const auto& lhs, const auto& rhs) {
		return lhs[0][2] < rhs[0][2];
		});

	unordered_map<int, Brick*> bricks;
	vector<vector<vector<int>>> brickMap(500, vector<vector<int>>(500, vector<int>(500, -1)));

	int id = 0;
	for (auto b : allEnds)
	{
		Brick* br = new Brick(id, 0, b, brickMap, bricks);
		bricks[id] = br;
		br->fall();
		id++;
	}
	/*
	int sum = 0;
	for (int i = 0; i < id; i++)
	{
		sum += bricks[i]->canDestory();
	}*/

	int sum = 0;
	for (int i = 0; i < id; i++)
	{
		sum += bricks[i]->destroyFalls();
	}

	cout << sum;

}