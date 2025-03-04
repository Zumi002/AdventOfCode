#include "../Utility/SupportFunc.h"
#include <iostream>
#include <unordered_map>

void Day1()
{
	myFile in = myFile();
	if (!in.Open("Day1/in.txt"))
	{
		cout << "wtf";
		return;
	}
	in.ReadFile();
	int star1 = 0,
		star2 = 0;
	vector<int> left;
	vector<int> right;
	unordered_map<int, int> timesInRight;
	for (auto v : in.inputWords)
	{
		string s = v[0];
		string s2 = v[3];
		left.push_back(stoi(s));
		right.push_back(stoi(s2));
		timesInRight[right.back()]++;
	}

	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	
	for (int i = 0; i < left.size(); i++)
	{
		star1 += abs(left[i] - right[i]);
		star2 += left[i] * timesInRight[left[i]];
	}
	cout << star1 << " "<< star2;
}