#include "../../Utility/SupportFunc.h"
#include "Day12.h"
#include <utility>
#include <set>
#include <unordered_map>

#define PART_ONE false
#define PART_TWO true

class Sol
{
public:
	string s;
	vector<int> groups;
	unordered_map<long long, long long> cache;

	Sol(string str, vector<int> &groupss,bool part2 = false)
	{
		s = str;
		groups = groupss;
		if (part2)
		{
			for (int i = 0; i < 4; i++)
			{
				s += "?";
				s += str;
				groups.insert(groups.begin(), groupss.begin(), groupss.end());
			}
		}
		s += ".";
	}
	long long solve(long long groupsMade = 0, long long groupC = 0, long long possition = 0)
	{
		if (possition == s.size())return (!groupC && groupsMade == groups.size());
		if (cache.count(1000000*groupC+10000*groupsMade+possition))return cache[1000000 * groupC + 10000 * groupsMade + possition];
		long long res = 0;
		if (s[possition] != '.')
		{
			if (!(groupsMade >= groups.size() || groups[groupsMade] < groupC))
			res += solve(groupsMade, groupC+1, possition + 1);
		}
		if (s[possition] != '#')
		{
			if (!(groupC && (groupsMade >= groups.size() || groupC != groups[groupsMade])))
			res += solve(groupsMade+(groupC!=0), 0, possition + 1);
		}
		cache[1000000 * groupC + 10000 * groupsMade + possition] = res;
		return res;
	}
};


void Day12()
{
	myFile in = myFile();
	in.Open("Days/Day12/in.txt");
	in.ReadFile();
	vector<string> ss(in.nol);
	vector<vector<int>>groups(in.nol);

	for (int i = 0; i < in.nol; i++)
	{
		ss[i ]= in.inputWords[i][0];
		for (string b : split(in.inputWords[i][1], ','))
		{
			groups[i].push_back(atoi(b.c_str()));
		}
	}
	long long res1 = 0, res2 =0;
	for (int i = 0; i < in.nol; i++)
	{
		Sol sol1 = Sol(ss[i], groups[i], PART_ONE);
		Sol sol2 = Sol(ss[i], groups[i], PART_TWO);
		res1 += sol1.solve();
		res2 += sol2.solve();
	}

	cout << res1<<" "<<res2;
}			