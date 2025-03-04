#include "../../Utility/SupportFunc.h"
#include "Day14.h"
#include <set>


class Rock
{
public:
	int x, y;
	vector<string> &map;
	vector<vector<Rock*>>& rockSpace;
	Rock(int X, int Y, vector<string>& m, vector<vector<Rock*>>& rs) :map(m) , rockSpace(rs)
	{
		x = X;
		y = Y;
	}
	bool Go(int dirx, int diry)
	{
		if (x + dirx >= 0 && x + dirx < map[0].size())
		{
			if (y + diry >= 0 && y + diry < map.size())
			{
				//cout << map[y + diry][x + dirx] << " in front \n";
				if (map[y + diry][x + dirx] == '.')
				{
					map[y][x] = '.';
					rockSpace[y][x] = NULL;
					x += dirx;
					y += diry;
					map[y][x] = 'O';
					rockSpace[y][x] = this;
					return true;
				}
				
			}
			//cout << "Ybound\n";
		}
		//cout << "Xbound \n";
		return false;
	}
	void GoNorth()
	{
		while(Go(0,-1))
		{
			//cout << "1";
		}
	}
	void GoSouth()
	{
		while (Go(0, 1))
		{
			//cout << "1";
		}
	}
	void GoEast()
	{
		while (Go(1, 0))
		{
			//cout << "1";
		}
	}
	void GoWest()
	{
		while (Go(-1, 0))
		{
			//cout << "1";
		}
	}
};

void North(vector<string> &map, vector<vector<Rock*>>&rockSpace)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (rockSpace[i][j])
			{
				rockSpace[i][j]->GoNorth();
			}
		}
	}
}
void South(vector<string>& map, vector<vector<Rock*>>& rockSpace)
{
	for (int i = map.size()-1; i >=0; i--)
	{
		for (int j = map[0].size()-1; j >= 0; j--)
		{
			if (rockSpace[i][j])
			{
				rockSpace[i][j]->GoSouth();
			}
		}
	}
}
void West(vector<string>& map, vector<vector<Rock*>>& rockSpace)
{
	for (int i =0; i <map[0].size() ; i++)
	{
		for (int j = map.size()-1; j >=0; j--)
		{
			if (rockSpace[j][i])
			{
				rockSpace[j][i]->GoWest();
			}
		}
	}
}
void East(vector<string>& map, vector<vector<Rock*>>& rockSpace)
{
	for (int i = map[0].size()-1; i >=0 ; i--)
	{
		for (int j = 0; j < map.size(); j++)
		{
			if (rockSpace[j][i])
			{
				rockSpace[j][i]->GoEast();
			}
		}
	}
}

void Cycle(vector<string>& map, vector<vector<Rock*>>& rockSpace)
{
	North(map, rockSpace);
	West(map, rockSpace);
	South(map, rockSpace);
	East(map, rockSpace);
}

int compareWithSnaps(vector<string>& map, vector<vector<string>>& snaps)
{
	for (int j =0;j<snaps.size();j++)
	{
		bool next = false;
		for (int i = 0; i < map.size(); i++)
		{
			if (snaps[j][i] != map[i])
			{
				next = true;
				break;
			}
		}
		if (next)continue;
		return j;
	}
	return -1;
}

void Day14()
{
	myFile in = myFile();
	in.Open("Days/Day14/in.txt");
	in.ReadFile();


	int sum = 0;
	vector<string> map;
	vector<vector<Rock*>>rockSpace(in.nol,vector<Rock*>(in.inputLines[0].size(),NULL));
	vector<vector<string>> snapshots;
	for (int i = 0; i < in.nol; i++)
	{
		map.push_back(in.inputLines[i]);
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == 'O')
			{
				//cout << "0" << " " << i << " " << j << "\n";
				rockSpace[i][j] = new Rock(j, i, map, rockSpace);
			}
		}
	}

	
	int sC = 0, C = 0;
	for (int i = 0; i < 100000; i++)
	{
		Cycle(map,rockSpace);
		int k = compareWithSnaps(map, snapshots);
		if (k != -1)
		{
			sC = k;
			C = i - k;
			cout << "Cycle start: "<<k+1<<" length: " << i -k<< "\n";

			break;
		}
		snapshots.push_back(map);
	}
	int searched = ((1000000000 - sC - 1) % C);
	int rC = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (snapshots[sC + searched][i][j] == 'O')rC++;
		}
		sum += rC;
	}
	cout << sum;

}