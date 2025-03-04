#include "../../Utility/SupportFunc.h"
#include "Day12.h"
#include <utility>
#include <set>


int charDiff(char a, char b)
{
	int val = a - b;
	if (b == 'S') val = a - 'a';
	if (a == 'S') val = 'a' - b;
	if (a == 'E') val = 'z'- b;
	return val;
}


int Pathfind(set<pair<int, int>> Start, pair<int, int>End, vector<string> map)
{
	//minx,maxx,miny,maxy
	int bounds[4] = { 0,map[0].size(),0,map.size()};

	vector<vector<int>> myMap;

	for (int i = 0; i < bounds[3]; i++)
	{
		vector<int> row;
		for (int j = 0; j < bounds[1]; j++)
		{
			row.push_back(0);
		}
		myMap.push_back(row);
	}

	set<pair<int, int>> goToPoints;
	set<pair<int, int>> nextToVisitPoints;
	goToPoints = Start;

	int turn = 0;
	while (turn<=1000)
	{
		turn++;
		
		for (pair<int, int> a: goToPoints)
		{
			int i = a.first, j = a.second;

			
				myMap[i][j] = 2;
				if (j < bounds[1] - 1)
				{
					if (myMap[i][j + 1] == 0)
					{
						if (charDiff(map[i][j + 1], map[i][j]) - 1 <= 0) nextToVisitPoints.insert(make_pair(i, j + 1));
					}
				}
				if (j > 0)
				{
					if (myMap[i][j - 1] == 0)
					{
						if (charDiff(map[i][j - 1], map[i][j]) - 1 <= 0) nextToVisitPoints.insert(make_pair(i, j - 1));
					}
				}
				if (i < bounds[3] - 1)
				{
					if (myMap[i + 1][j] == 0)
					{
						if (charDiff(map[i + 1][j], map[i][j]) - 1 <= 0) nextToVisitPoints.insert(make_pair(i + 1, j));
					}
				}
				if (i > 0)
				{
					if (myMap[i - 1][j] == 0)
					{
						if (charDiff(map[i - 1][j], map[i][j]) - 1 <= 0) nextToVisitPoints.insert(make_pair(i - 1, j));
					}
				}
			
		}
		for (pair<int, int> a : nextToVisitPoints)
		{
			if (a == End) return turn;
		}
		goToPoints.clear();
		goToPoints = nextToVisitPoints;
		nextToVisitPoints.clear();
	}
	
	return 4000;
}




void Day12()
{
	myFile in = myFile();
	in.Open("Days/Day12/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;
	int maxY = in.nol, maxX = in.inputLines[0].size();

	set<pair<int, int>> Start;
	pair<int,int> End;

	for (int i = 0; i < maxY; i++)
	{
		for (int j = 0; j < maxX; j++)
		{
			if (in.inputLines[i][j] == 'S') Start.insert(make_pair(i, j));
			if (in.inputLines[i][j] == 'E')End = make_pair(i, j);
		}
	}
	cout<< Pathfind(Start, End, in.inputLines);
	//cin >> sum;
	for (int i = 0; i < maxY; i++)
	{
		for (int j = 0; j < maxX; j++)
		{
			
			if (in.inputLines[i][j]=='a')
			{
				Start.insert(make_pair(i, j));
			}
		}
	}

	sum = Pathfind(Start, End, in.inputLines);

	cout <<" "<< sum;
}			