#include "../Utility/SupportFunc.h"
#include "Day11.h"
#include <set>

bool comp(pair<long long, long long> lhs, pair<long long, long long>rhs)
{
	return lhs.second < rhs.second;
}

void Day11()
{
	myFile in = myFile();
	in.Open("Day11/in.txt");
	in.ReadFile();


	vector<pair<long long,long long>> onX, onY;
	long long id = 0;
	for (long long i = 0; i < in.nol; i++)
	{
		for (long long j = 0; j < in.inputLines[0].size(); j++)
		{
			if (in.inputLines[i][j] == '#')
			{
				onX.push_back({ id,j });
				onY.push_back({ id,i });
				id++;
			}
		}
	}

	long long exX = 0, exY = 0;
	sort(onX.begin(), onX.end(), comp);
	sort(onY.begin(), onY.end(), comp);

	vector<pair<long long, long long>> galaxies(id);

	//p2 change
	long long replace = 1000000;
	for (long long i = 1; i < id; i++)
	{
		exX += onX[i].second - (onX[i - 1].second - exX) - 1 > 0 ? (replace-1)*(onX[i].second - (onX[i - 1].second - exX) - 1) : 0;
		onX[i].second += exX;
		exY += onY[i].second - (onY[i - 1].second - exY) - 1 > 0 ? (replace - 1) *(onY[i].second - (onY[i - 1].second - exY) - 1) : 0;
		onY[i].second += exY;
		galaxies[onY[i].first].first = onY[i].second;
		galaxies[onX[i].first].second = onX[i].second;
	}
	
	long long dist = 0;
	for (long long i = 0; i < id ; i++)
	{
		for (long long j = i + 1; j < id; j++)
		{
			dist += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
		}
	}
	cout << dist;
}