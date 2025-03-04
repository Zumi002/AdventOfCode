#include "../../Utility/SupportFunc.h"
#include "Day16.h"
#include <map>

struct DirH
{
	bool dir[4] = { false,false,false,false };
};

enum Dir
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};


class Beam
{
	public:
	vector<string> &map;
	vector<string> &energy;
	vector<vector<DirH>> &history;
	vector<Beam*> &beams;
	pair<int, int> where[4] = { {-1,0},{0,1},{1,0},{0,-1} };
	int x, y;
	int dir;
	Beam(vector<string> &m,vector<string>&e,vector<vector<DirH>> &h,vector<Beam*> &b,int X,int Y,int d):map(m),energy(e),history(h),beams(b)
	{
		x = X;
		y = Y;
		dir = d;
	};
	void ActiveFirst()
	{
		if (map[y][x] == '\\')
		{
			if (dir == UP)dir = LEFT;
			else if (dir == RIGHT)dir = DOWN;
			else if (dir == DOWN)dir = RIGHT;
			else if (dir == LEFT)dir = UP;
		}
		else if (map[y][x] == '/')
		{
			if (dir == UP)dir = RIGHT;
			else if (dir == RIGHT)dir = UP;
			else if (dir == DOWN)dir = LEFT;
			else if (dir == LEFT)dir = DOWN;
		}
		else if (map[y][x] == '-')
		{
			if (dir == UP || dir == DOWN)
			{
				beams.push_back(new Beam(map, energy, history, beams, x, y, RIGHT));
				dir = LEFT;
			}
		}
		else if (map[y][x] == '|')
		{
			if (dir == LEFT || dir == RIGHT)
			{
				beams.push_back(new Beam(map, energy, history, beams, x, y, UP));
				dir = DOWN;
			}
		}
	}
	bool Go()
	{
		history[y][x].dir[dir] = true;
		energy[y][x] = '#';
		y += where[dir].first;
		x += where[dir].second;
		if (x < 0 || x >= map[0].size())
		{
			//cout << "Dead by xbound\n";
			return false;
		}
		if (y < 0 || y >= map.size())
		{
			//cout << "Dead by ybound\n";
			return false;
		}
		if (history[y][x].dir[dir])
		{
			if (map[y][x] == '.')
			{
				//cout << "Dead by history\n";
				return false;
			}
		}
		if (map[y][x] == '\\')
		{
			if (dir == UP)dir = LEFT;
			else if (dir == RIGHT)dir = DOWN;
			else if (dir == DOWN)dir = RIGHT;
			else if (dir == LEFT)dir = UP;
		}
		else if (map[y][x] == '/')
		{
			if (dir == UP)dir = RIGHT;
			else if (dir == RIGHT)dir = UP;
			else if (dir == DOWN)dir = LEFT;
			else if (dir == LEFT)dir = DOWN;
		}
		else if (map[y][x] == '-')
		{
			if (dir == UP || dir == DOWN)
			{
				beams.push_back(new Beam(map, energy, history, beams, x, y, RIGHT));
				dir = LEFT;
			}
		}
		else if(map[y][x] == '|')
		{
			if (dir == LEFT || dir == RIGHT)
			{
				beams.push_back(new Beam(map, energy, history, beams, x, y, UP));
				dir = DOWN;
			}
		}
		return true;
	}

};

void Day16()
{
	myFile in = myFile();
	in.Open("Days/Day16/in.txt");
	in.ReadFile();

	vector<string> map;
	
	
	
	for (int i = 0; i < in.nol; i++)
	{
		map.push_back(in.inputLines[i]);
	}
	int maxEne = 0;
	for (int i = 0; i < map.size(); i++)
	{
		vector<string> energy;
		for(int j = 0;j<map.size();j++)energy.push_back(string(in.inputLines[j].size(), '.'));
		vector<Beam*> beams;
		vector<vector<DirH>>  history = vector<vector<DirH>>(map.size(), vector<DirH>(map[0].size()));
		beams.push_back(new Beam(map, energy, history, beams, 0, i, RIGHT));
		beams[0]->ActiveFirst();
		int k = beams.size();
		for (int i = 0; i < k; i++)
		{
			while (beams[i]->Go());
			k = beams.size();
		}
		int sum = 0;
		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				//if (map[i][j] == '.')cout << energy[i][j];
				//else cout << map[i][j];
				sum += (energy[i][j] == '#');
			}
		}
		maxEne = max(sum, maxEne);
	}
	for (int i = 0; i < map.size(); i++)
	{
		vector<string> energy;
		for (int j = 0; j < map.size(); j++)energy.push_back(string(in.inputLines[j].size(), '.'));
		vector<Beam*> beams;
		vector<vector<DirH>>  history = vector<vector<DirH>>(map.size(), vector<DirH>(map[0].size()));
		beams.push_back(new Beam(map, energy, history, beams, map[0].size()-1, i, LEFT));
		beams[0]->ActiveFirst();
		int k = beams.size();
		for (int i = 0; i < k; i++)
		{
			while (beams[i]->Go());
			k = beams.size();
		}
		int sum = 0;
		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				//if (map[i][j] == '.')cout << energy[i][j];
				//else cout << map[i][j];
				sum += (energy[i][j] == '#');
			}
			//cout << "\n";
		}
		maxEne = max(sum, maxEne);
	}
	for (int i = 0; i < map[0].size(); i++)
	{
		vector<string> energy;
		for (int j = 0; j < map.size(); j++)energy.push_back(string(in.inputLines[j].size(), '.'));
		vector<Beam*> beams;
		vector<vector<DirH>>  history = vector<vector<DirH>>(map.size(), vector<DirH>(map[0].size()));
		beams.push_back(new Beam(map, energy, history, beams, i, 0, DOWN));
		beams[0]->ActiveFirst();
		int k = beams.size();
		for (int i = 0; i < k; i++)
		{
			while (beams[i]->Go());
			k = beams.size();
		}
		int sum = 0;
		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				//if (map[i][j] == '.')cout << energy[i][j];
				//else cout << map[i][j];
				sum += (energy[i][j] == '#');
			}
			//cout << "\n";
		}
		maxEne = max(sum, maxEne);
	}
	for (int i = 0; i < map[0].size(); i++)
	{
		vector<string> energy;
		for (int j = 0; j < map.size(); j++)energy.push_back(string(in.inputLines[j].size(), '.'));
		vector<Beam*> beams;
		vector<vector<DirH>>  history = vector<vector<DirH>>(map.size(), vector<DirH>(map[0].size()));
		beams.push_back(new Beam(map, energy, history, beams, i, map.size()-1, UP));
		beams[0]->ActiveFirst();
		int k = beams.size();
		for (int i = 0; i < k; i++)
		{
			while (beams[i]->Go());
			k = beams.size();
		}
		int sum = 0;
		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				//if (map[i][j] == '.')cout << energy[i][j];
				//else cout << map[i][j];
				sum += (energy[i][j] == '#');
			}
			//cout << "\n";
		}
		maxEne = max(sum, maxEne);
	}
	cout << maxEne;
}