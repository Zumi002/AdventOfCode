#include "../../Utility/SupportFunc.h"
#include <iostream>
#include <unordered_map>
void Day1()
{
	myFile in = myFile();
	if (!in.Open("Days/Day1/in.txt"))
	{
		cout << "wtf";
		return;
	}
	in.ReadFile();
	int first, last;
	int current = 0, add = 0;
	unordered_map<string, int> vals = { {"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9} };
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] <= '9' && in.inputLines[i][j] >= '0')
			{
				first = 10 * (in.inputLines[i][j] - '0');
				break;
			}
			else
			{
				if (vals.find(in.inputLines[i].substr(j, 3)) != vals.end())
				{
					first = 10 * vals[in.inputLines[i].substr(j, 3)];
					break;
				}
				if (vals.find(in.inputLines[i].substr(j, 4)) != vals.end())
				{
					first = 10 * vals[in.inputLines[i].substr(j, 4)];
					break;
				}
				if (vals.find(in.inputLines[i].substr(j, 5)) != vals.end())
				{
					first = 10 * vals[in.inputLines[i].substr(j, 5)];
					break;
				}
			}
		}
		for (int j = in.inputLines[i].size()-1; j >=0; j--)
		{
			if (in.inputLines[i][j] <= '9' && in.inputLines[i][j] >= '0')
			{
				last = in.inputLines[i][j] - '0';
				break;
			}
			else
			{
				if (vals.find(in.inputLines[i].substr(j, 3)) != vals.end())
				{
					last = vals[in.inputLines[i].substr(j, 3)];
					break;
				}
				if (vals.find(in.inputLines[i].substr(j, 4)) != vals.end())
				{
					last = vals[in.inputLines[i].substr(j, 4)];
					break;
				}
				if (vals.find(in.inputLines[i].substr(j, 5)) != vals.end())
				{
					last = vals[in.inputLines[i].substr(j, 5)];
					break;
				}
			}
		}
		current += first + last;
		cout << first <<" "<< last << "\n";
	}
	cout << current;
}