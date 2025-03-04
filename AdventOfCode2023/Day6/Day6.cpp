#include "../Utility/SupportFunc.h"
#include "Day6.h"
#include <queue>

int canWin(long long time, long long dist)
{
	long long res = 0;
	for (long long i = 1; i < time; i++)
	{
		if ((time - i) * i > dist)res++;
	}
	return res;
}

void Day6()
{
	myFile in = myFile();
	in.Open("Day6/in.txt");
	in.ReadFile();

	int sum = 0;
	vector<long long> time,distance;
	for (int j = 1; j < in.inputWords[0].size(); j++)
	{
		if (in.inputWords[0][j] == "")continue;
		time.push_back(strtoll(in.inputWords[0][j].c_str(), NULL, 10));
	}
	for (int j = 1; j < in.inputWords[1].size(); j++)
	{
		if (in.inputWords[1][j] == "")continue;
		distance.push_back(strtoll(in.inputWords[1][j].c_str(),NULL,10));
	}
	int multi = 1;
	for (int i = 0; i < time.size(); i++)
	{
		multi *= canWin(time[i], distance[i]);
	}

	cout << multi;
}