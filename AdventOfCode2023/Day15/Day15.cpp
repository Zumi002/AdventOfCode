#include "../Utility/SupportFunc.h"
#include "Day15.h"
#include <set>
#include <math.h>
#include <unordered_map>
#include <stack>

int hashS(string s)
{
	int v = 0;
	for (char c : s)
	{
		v += c;
		v *= 17;
		v %= 256;
	}
	return v;
}

void Day15()
{
	myFile in = myFile();
	in.Open("Day15/in.txt");
	in.ReadFile();
	int sum = 0,sum2=0;

	vector<string>seq = split(in.inputLines[0], ',');
	vector<stack<pair<string,int>>> hashmap(256);
	for (string a : seq)
	{
		int h = hashS(a);
		sum += h;
		auto k = split(a, '=').size()==2?split(a,'='):split(a,'-');
		h = hashS(k[0]);
		stack<pair<string, int>> tmp;
		bool pushed = false;
		while (hashmap[h].size()&&hashmap[h].top().first != k[0])
		{
			tmp.push(hashmap[h].top());
			hashmap[h].pop();
		}
		if (hashmap[h].size())
		{
			hashmap[h].pop();
			if (k.size() == 2 && k[1].size() > 0)
			{
				hashmap[h].push({ k[0], atoi(k[1].c_str()) });
				pushed = true;
			}
		}
		while (tmp.size())
		{
			hashmap[h].push(tmp.top());
			tmp.pop();
		}
		if (k.size() == 2 && k[1].size() > 0&&!pushed)
		{
			hashmap[h].push({ k[0], atoi(k[1].c_str()) });
		}
	}
	for (int i = 0; i < 256; i++)
	{
		int v = 0;
		while(hashmap[i].size())
		{
			v += (i+1) * hashmap[i].size() * hashmap[i].top().second;
			hashmap[i].pop();
		}
		sum2 += v;
	}
	cout << sum << " "<<sum2;
}