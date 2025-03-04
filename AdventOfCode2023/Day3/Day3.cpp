#include "../Utility/SupportFunc.h"
#include "Day3.h"

using namespace std;

void Day3()
{
	myFile in = myFile();
	in.Open("Day3/in.txt");
	in.ReadFile();
	
	

	int sum = 0;
	vector<vector<int>> gears;
	vector<vector<int>> gearN;
	for (int i = 0; i < in.nol; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			tmp.push_back(0);
		}
		gearN.push_back(tmp);
		gears.push_back(tmp);
	}
	for (int i = 0; i < in.nol; i++)
	{
		int num = 0;
		int count = 0;
		int gi, gj;
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] > '9' || in.inputLines[i][j] < '0')
			{
				
				if (count)
				{
					gearN[gi][gj]++;
					if (gearN[gi][gj] > 1)gears[gi][gj] *= num;
					else gears[gi][gj] += num;
					count = 0;
				}
				num = 0;
			}
			else
			{
				num *= 10;
				num += in.inputLines[i][j] - '0';
				if (!count&&j > 0)
				{
					if (in.inputLines[i][j - 1] == '*' && (in.inputLines[i][j - 1] > '9' || in.inputLines[i][j - 1] < '0'))
					{
						count = 1;
						gi = i;
						gj = j-1;
					}
				}
				if (!count && j < in.inputLines[i].size()-1)
				{
					if (in.inputLines[i][j + 1] == '*' && (in.inputLines[i][j+1] > '9' || in.inputLines[i][j+1] < '0')) {
						count = 1;
						gi = i;
						gj = j+1;
					}
				}
				if (!count && i > 0)
				{
					if (in.inputLines[i-1][j] == '*' && (in.inputLines[i-1][j] > '9' || in.inputLines[i-1][j] < '0')) {
						count = 1;
						gi = i-1;
						gj = j;
					}
					if (!count && j > 0)
					{
						if (in.inputLines[i-1][j - 1] == '*' && (in.inputLines[i-1][j - 1] > '9' || in.inputLines[i-1][j - 1] < '0')) {
							count = 1;
							gi = i-1;
							gj = j-1;
						}
					}
					if (!count && j < in.inputLines[i].size() - 1)
					{
						if (in.inputLines[i-1][j + 1] == '*' && (in.inputLines[i-1][j + 1] > '9' || in.inputLines[i-1][j + 1] < '0')) {
							count = 1;
							gi = i-1;
							gj = j+1;
						}
					}
				}
				if (!count && i < in.inputLines[i].size() - 1)
				{
					if (in.inputLines[i+1][j] == '*' && (in.inputLines[i+1][j] > '9' || in.inputLines[i+1][j] < '0')) {
						count = 1;
						gi = i+1;
						gj = j;
					}
					if (!count && j > 0)
					{
						if (in.inputLines[i+1][j - 1] == '*' && (in.inputLines[i+1][j - 1] > '9' || in.inputLines[i+1][j - 1] < '0')) {
							count = 1;
							gi = i+1;
							gj = j-1;
						}
					}
					if (!count && j < in.inputLines[i].size() - 1)
					{
						if (in.inputLines[i+1][j + 1] == '*' && (in.inputLines[i+1][j + 1] > '9' || in.inputLines[i+1][j + 1] < '0')) {
							count = 1;
							gi = i+1;
							gj = j+1;
						}
					}
				}
			}
		}
		if (count)
		{
			gearN[gi][gj]++;
			if (gearN[gi][gj] > 1)gears[gi][gj] *= num;
			else gears[gi][gj] += num;
			count = 0;
		}
	}
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (gearN[i][j] == 2)sum += gears[i][j];
		}
	}
	cout << sum;
	return;
}