#include "../../Utility/SupportFunc.h"
#include "Day18.h"
#include <tuple>
#include <set>

bool threeDgrid[30][30][30];
bool alreadyBeen[30][30][30];

void Day18()
{
	myFile in = myFile();
	in.Open("Days/Day18/in.txt");
	in.ReadFile();




	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				threeDgrid[i][j][k] = false;
			}
		}
	}
	
	int numOfLava = in.nol;

	for (int i = 0; i < in.nol; i++)
	{
		vector<string> pos = split(in.inputLines[i], ',');
		threeDgrid[stoi(pos[0])+1][stoi(pos[1])+1][stoi(pos[2])+1] = true;
	}

	int lavaChecked = 0;
	int totalUncoveredSides = 0;
	for (int i = 1; i < 29 && lavaChecked != numOfLava; i++)
	{
		for (int j = 1; j < 29 && lavaChecked != numOfLava; j++)
		{
			for (int k = 1; k < 29 && lavaChecked != numOfLava; k++)
			{
				if (threeDgrid[i][j][k])
				{
					lavaChecked += 1;
					totalUncoveredSides += threeDgrid[i - 1][j][k] ? 0 : 1;
					totalUncoveredSides += threeDgrid[i + 1][j][k] ? 0 : 1;
					totalUncoveredSides += threeDgrid[i][j - 1][k] ? 0 : 1;
					totalUncoveredSides += threeDgrid[i][j + 1][k] ? 0 : 1;
					totalUncoveredSides += threeDgrid[i][j][k - 1] ? 0 : 1;
					totalUncoveredSides += threeDgrid[i][j][k + 1] ? 0 : 1;
				}
			}
		}
	}
	int sidesWithoutAirPockets = 0;
	
	set<tuple<int, int, int>> ToGo;

	ToGo.insert(make_tuple(0, 0, 0));

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				alreadyBeen[i][j][k] = false;
			}
		}
	}

	//bfs
	while(ToGo.size()!=0)
	{
		set<tuple<int, int, int>> nextToGo;
		for (tuple<int, int, int> a : ToGo)
		{
			int i = get<0>(a);
			int j = get<1>(a);
			int k = get<2>(a);

			alreadyBeen[i][j][k] = true;
		}
		for (tuple<int, int, int> a : ToGo)
		{
			int i = get<0>(a);
			int j = get<1>(a);
			int k = get<2>(a);

			if (i > 0)
			{
				sidesWithoutAirPockets += threeDgrid[i - 1][j][k] ? 1 : 0;
			}
			if(i < 29)
			{
				sidesWithoutAirPockets += threeDgrid[i + 1][j][k] ? 1 : 0;
			}
			if (j > 0)
			{
				sidesWithoutAirPockets += threeDgrid[i][j - 1][k] ? 1 : 0;
			}
			if (j < 29)
			{
				sidesWithoutAirPockets += threeDgrid[i][j + 1][k] ? 1 : 0;
			}
			
			if (k > 0)
			{
				sidesWithoutAirPockets += threeDgrid[i][j][k - 1] ? 1 : 0;
			}
			if (k < 29)
			{
				sidesWithoutAirPockets += threeDgrid[i][j][k + 1] ? 1 : 0;
			}
			if (i > 0)
			{
				if (!alreadyBeen[i - 1][j][k]&&!threeDgrid[i - 1][j][k])nextToGo.insert(make_tuple(i - 1, j, k));
			}
			if (i < 29)
			{
				if (!alreadyBeen[i + 1][j][k] && !threeDgrid[i + 1][j][k])nextToGo.insert(make_tuple(i + 1, j, k));
			}
			if (j > 0)
			{
				if (!alreadyBeen[i][j - 1][k] && !threeDgrid[i][j - 1][k])nextToGo.insert(make_tuple(i, j - 1, k));
			}
			if (j < 29)
			{
				if (!alreadyBeen[i][j + 1][k] && !threeDgrid[i][j + 1][k])nextToGo.insert(make_tuple(i, j + 1, k));
			}
			if (k > 0)
			{
				if (!alreadyBeen[i][j][k - 1] && !threeDgrid[i][j][k - 1])nextToGo.insert(make_tuple(i, j, k - 1));
			}
			if (k < 29)
			{
				if (!alreadyBeen[i][j][k + 1] && !threeDgrid[i][j][k + 1])nextToGo.insert(make_tuple(i, j, k + 1));
			}
		}
		ToGo.clear();
		ToGo = nextToGo;
		nextToGo.clear();
	}

	cout << totalUncoveredSides << " " << sidesWithoutAirPockets;
}