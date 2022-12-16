#include "../Utility/SupportFunc.h"
#include "Day14.h"
#include <set>


class Particle
{
public:
	int x, y;
	int lastmove = 0;
	int move(vector<vector<bool>> &rocks,pair<int,int> sPos)
	{
		x = sPos.first;
		y = sPos.second;
		//cout << "starting: " << x << " " << y << "\n";
		//lstmove -1 left 0 top 1 right;
		
		for (int i = y; i < rocks.size(); i++)
		{
			//cout <<"checking: "<< i << " " << x << "\n";
			if (!rocks[i][x])
			{
				y = i;
				lastmove = 0;
			}
			else if (!rocks[i][x - 1])
			{
				y=i;
				x -= 1;
				lastmove = -1;
			}
			else if (!rocks[i][x + 1])
			{
				y=i;
				x += 1;
				lastmove = 1;
			}
			else
			{
				return 0;
			}
		}
		
		return  1;
	}
};


void Day14()
{
	myFile in = myFile();
	in.Open("Day14/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;

	set<pair<int, int>> rocks;

	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputWords[i].size()-2; j+=2)
		{

			int startx = stoi(split(in.inputWords[i][j],',')[0]),
				starty = stoi(split(in.inputWords[i][j], ',')[1]);
			int stopx = stoi(split(in.inputWords[i][j+2], ',')[0]),
				stopy = stoi(split(in.inputWords[i][j+2], ',')[1]);
			if (startx > stopx)swap(startx, stopx);
			if (starty > stopy)swap(starty, stopy);
			for (int k = startx; k <= stopx; k++)
			{
				for (int g = starty; g <= stopy; g++)
				{
					rocks.insert(make_pair(k,g));
				}
			}
		}
	}

	pair<int, int> sandEmiter = make_pair(500, 0);
	int lowestY = 0,highX = 0;
	for (pair<int, int> a : rocks)
	{
		if (a.second > lowestY)lowestY = a.second;
		if (a.first > highX)highX = a.first;
	}
	lowestY += 2;
	highX += 2*lowestY+1;

	vector<vector<bool>> rockMap;
	for (int i = 0; i < lowestY; i++)
	{
		vector<bool> row;
		for (int j = 0; j < highX; j++)
		{
			row.push_back(false);
		}
		rockMap.push_back(row);
	}
	for (pair<int, int> a : rocks)
	{
		//std::cout << a.second << " " << a.first << "\n";
		rockMap[a.second][a.first] = true;
	}
	//for (int i = 0; i < lowestY; i++)
	//{
	//	for (int j = 450; j < highX; j++)
	//	{
	//		cout << (rockMap[i][j] ? '#' : '.');
	//	}
	//	cout << "\n";
	//}
	//cout << "\n";
	int felloff = 0;
	bool stacked = false;;

	int i = 0;
	pair<int, int> StartPos = sandEmiter;

	while (!stacked)
	{
		i++;
		Particle a;
		a.x = StartPos.first;
		a.y = StartPos.second;
		int move = a.move(rockMap,sandEmiter);
		//cout << a.x << " " << a.y << "\n";
		rockMap[a.y][a.x] = true;
		//StartPos = make_pair(a.x - a.lastmove, a.y - 1);
		if (a.x == 500 && a.y == 0) stacked = true;
		if (move == 1&&felloff==0)
		{
			felloff = i - 1;
		}
	}
	//for (int i = 0; i < lowestY; i++)
	//{
	//	for (int j = 475; j < highX; j++)
	//	{
	//		cout << (rockMap[i][j] ? '#' : '.');
	//	}
	//	cout << "\n";
	//}
	std::cout << felloff<<" "<<i;
}