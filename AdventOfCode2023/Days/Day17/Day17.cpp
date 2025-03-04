#include "../../Utility/SupportFunc.h"
#include "Day17.h"
#include <queue>

#define MAXSTEP 10

enum Dir
{
	UP=1,
	RIGHT,
	DOWN,
	LEFT
};

struct Way
{
	int dir;
	int consDir;
	int cost;
	int realCost = 0;
	int end = 0;
	int x, y;
	int updatedCost = 0;
	Way(int D,int cD,int c,int X,int Y)
	{
		dir = D;
		consDir = cD;
		cost = c;
		x = X;
		y = Y;
	}
	vector<Way*> out;
};

vector<vector<int>> canGo = { {}, {2,1,4},{3,2,1},{3,2,4},{3,4,1} };
vector<int> xoff = { -1,0,1,0,-1 };
vector<int> yoff = { -1,-1,0,1,0 };

class comp
{
public:
	bool operator()(Way* lhs, Way* rhs)
	{
		return lhs->realCost > rhs->realCost;
	}
};


void Day17()
{
	myFile in = myFile();
	in.Open("Days/Day17/in.txt");
	in.ReadFile();

	vector<vector<vector<vector<Way*>>>> nodes;
	vector<vector<vector<vector<bool>>>> seen;
	for (int i = 0; i < in.nol; i++)
	{
		vector<vector<vector<Way*>>> tmp1;
		vector<vector<vector<bool>>> tmpb1;
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			vector<vector<Way*>> tmp2;
			vector<vector<bool>> tmpb2;
			int v = in.inputLines[i][j] - '0';
			for (int k = 1; k <= LEFT; k++)
			{
				vector<Way*> tmp3;
				vector<bool> tmpb3;
				for (int c = 1; c <= MAXSTEP; c++)
				{
					tmp3.push_back(new Way(k, c, v,j,i));
					tmpb3.push_back(false);
				}
				tmp2.push_back(tmp3);
				tmpb2.push_back(tmpb3);
			}
			tmp1.push_back(tmp2);
			tmpb1.push_back(tmpb2);
		}
		nodes.push_back(tmp1);
		seen.push_back(tmpb1);
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i].size(); j++)
		{
			for (int k = 1; k <= LEFT; k++)
			{
				for (int l = 1; l <= MAXSTEP; l++)
				{
					for (int w : canGo[k])
					{
						if (w == k)
						{
							if (l != MAXSTEP)
							{
								if(i+yoff[w]>=0&&i+yoff[w]<nodes.size()&&j+xoff[w]>=0&&j+xoff[w]<nodes[0].size())nodes[i][j][k - 1][l - 1]->out.push_back(nodes[i + yoff[w]][j + xoff[w]][k - 1][l]);
							}
						}
						else if (l>=4&&i + yoff[w] >= 0 && i + yoff[w] < nodes.size() && j + xoff[w] >= 0 && j + xoff[w] < nodes[0].size()) nodes[i][j][k - 1][l - 1]->out.push_back(nodes[i + yoff[w]][j + xoff[w]][w-1][0]);
					}
					if (i == nodes.size() - 1 && j == nodes[0].size() - 1)
					{
						//cout << "ends \n";
						nodes[i][j][k - 1][l - 1]->end = 1;
					}
				}

			}
		}
	}
	
	int sum = in.inputLines[0][0] - '0';
	nodes[0][1][RIGHT - 1][0]->realCost = nodes[0][1][RIGHT - 1][0]->cost;
	nodes[1][0][DOWN - 1][0]->realCost = nodes[1][0][DOWN - 1][0]->cost;
	seen[0][0][0][0] = true;
	priority_queue<Way*, vector<Way*>, comp> q;
	q.push(nodes[0][1][RIGHT - 1][0]);
	q.push(nodes[1][0][DOWN - 1][0]);
	int endMinCost = INT_MAX,costNow = sum;

	while (costNow<endMinCost&&q.size())
	{
		Way* a = q.top();
		costNow = a->realCost;
		seen[a->y][a->x][a->dir-1][a->consDir-1] = true;
		q.pop();
		if (a->end&&a->consDir>=4)
		{
			cout << costNow;
			break;
		}
		for (Way* b : a->out)
		{
			if (!seen[b->y][b->x][b->dir-1][b->consDir-1])
			{
				if (!b->updatedCost)
				{
					b->realCost = costNow + b->cost;
					b->updatedCost = 1;
					q.push(b);
				}
			}
		}
	}
	//cout << costNow;

}