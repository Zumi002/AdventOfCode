#include "../Utility/SupportFunc.h"
#include "Day7.h"
#include <stack>
#include <unordered_map>
#include <set>

bool has5(unordered_map<char,int> s)
{
	int j = s['J'];
	if (j == 5)return true;
	for (auto k : s)
	{
		if (k.first != 'J' && k.second >= 5-j)return true;
	}
	return false;
}

bool has4(unordered_map<char, int> s)
{
	int j = s['J'];
	for (auto k : s)
	{
		if (k.first != 'J' && k.second >= 4-j)return true;
	}
	return false;
}

bool hasFull(unordered_map<char, int> s)
{
	int j = s['J'];
	for (auto k : s)
	{
		if (k.first!='J'&&k.second >= 3 - j)
		{
			int jj = j - 3 + k.second;
			for (auto kk : s)
			{
				if (kk.first != 'J' && k.first!=kk.first&&kk.second >= 2 - jj)
					return true;
			}
		}
	}
	return false;
}
bool has3(unordered_map<char, int> s)
{
	int j = s['J'];
	int three = 0;
	for (auto k : s)
	{
		if (k.second == 3-j)three = 1;
	}
	return three;
}
bool has22(unordered_map<char, int> s)
{
	int j = s['J'];
	int two = 0;
	for (auto k : s)
	{
		if (k.second == 2)two++;
	}
	return two==2;
}
bool has2(unordered_map<char, int> s)
{
	int j = s['J'];
	int two = 0;
	for (auto k : s)
	{
		if (k.second == 2-j)two = 1;
	}
	return two;
}


char value[15] = { 'J','2','3','4','5','6','7','8','9','T','J','Q','K','A' };

int cVal(char c)
{
	for (int i = 0; i < 15; i++)
	{
		if (c == value[i])return i;
	}
	return -1;
}

long long hashh(string abs)
{
	unordered_map<char, int> s;
	for (char c : abs)s[c]++;
	long long h = 0;
	if (has5(s))h += 60000000000;
	else if (has4(s))h += 50000000000;
	else if (hasFull(s))h += 40000000000;
	else if (has3(s))h += 30000000000;
	else if (has22(s))h += 20000000000;
	else if (has2(s))h += 10000000000;
	int mag = 100000000;
	for (int i = 0; i < 5; i++)
	{
		h += mag * cVal(abs[i]);
		mag /= 100;
	}
	return h;
}

void Day7()
{
	myFile in = myFile();
	in.Open("Day7/in.txt");
	in.ReadFile();
	auto cmp = [](pair<long long, long long>lhs, pair<long long, long long>rhs) {return (lhs.first < rhs.first);};
	set < pair<long long, long long>,  decltype(cmp)> hands(cmp);
	int sum = 0;

	for (int i = 0; i < in.nol; i++)
	{
		pair<long long, long long> a = {hashh(in.inputWords[i][0]),strtoll(in.inputWords[i][1].c_str(),NULL,10) };
		hands.insert(a);
	}
	int i = 1;
	for (auto h : hands)
	{
		//cout << h.first << "\n";
		sum += h.second * i;
		i++;
	}
	cout << sum;
}
