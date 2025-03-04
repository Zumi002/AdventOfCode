#include "../Utility/SupportFunc.h"
#include "Day25.h"
#include <iostream>
#include <unordered_map>

void Day25()
{
	myFile in = myFile();
	if (!in.Open("Day25/in.txt"))
	{
		cout << "wtf";
		return;
	}
	in.ReadFile();
	
	long long sum = 0;

	vector<vector<int>> keys;
	vector<vector<int>> locks;

	int h = 0;

	for (int i = 0; i < in.nol; i++)
	{
		vector<string> keylock;
		int j = i;
		for (; j < in.nol; j++)
		{
			if (in.inputLines[j] == "")
				break;
			keylock.push_back(in.inputLines[j]);
		}
		i = j;
		i++;

		vector<int> kkll;
		char first = keylock[keylock.size() - 1][0];
		h = keylock.size();
		for (int k = 0; k < keylock[0].size(); k++)
		{
			
			int count = -1;
			
			for (int l = keylock.size() - 1; l >= 0; l--)
			{
				if (keylock[l][k] != first)
					break;
				count++;
			}
			kkll.push_back(count);
		}
		if (first == '#')
			keys.push_back(kkll);
		else
			locks.push_back(kkll);
		
		
	}

	for (auto& v : locks)
	{
		
		for (auto& kv : keys)
		{
			bool bad = false;
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i] < kv[i])
				{
					bad = true;
					break;
				}
				
			}
			if (!bad)
				sum++;
		}
		
	}
	
	cout << sum;
}