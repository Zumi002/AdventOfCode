#include "../Utility/SupportFunc.h"
#include "Day23.h"
#include <set>
#include <unordered_map>

void largestclique(vector<vector<int>>& tab, set<int>& clique, int i, set<int>& biggest)
{
		if (i >= tab.size())
			return;
		
		bool bad = false;
		for (auto &node : clique)
		{
			if (!tab[node][i])
			{
				bad = true;
				break;
			}
		}
		if (!bad)
		{
			clique.insert(i);
			if (clique.size() > biggest.size())
			{
				biggest = set<int>(clique);
			}
			largestclique(tab, clique, i + 1, biggest);
			clique.erase(i);
		}
		largestclique(tab, clique, i + 1, biggest);
	
}

void Day23()
{
	myFile in = myFile();
	in.Open("Day23/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;
	unordered_map<string, int> idx;
	unordered_map<int, string> idxRev;
	vector<string> t;

	for (int i = 0; i < in.nol; i++)
	{
		auto ss = split(in.inputLines[i], '-');
		if (!idx.count(ss[0]))
		{
			if (ss[0][0] == 't')
				t.push_back(ss[0]);
			idx[ss[0]] = idx.size();
			idxRev[idx[ss[0]]] = ss[0];
		}
		if (!idx.count(ss[1]))
		{
			if (ss[1][0] == 't')
				t.push_back(ss[1]);
			idx[ss[1]] = idx.size();
			idxRev[idx[ss[1]]] = ss[1];
		}
	}

	int n = idx.size()+1;
	vector<vector<int>> tab(n, vector<int>(n, 0));
	for (int i = 0; i < in.nol; i++)
	{
		//if (i>1167)
		//	cout << i<<"\n";
		auto ss = split(in.inputLines[i], '-');
		tab[idx[ss[0]]][idx[ss[1]]] = 1;
		tab[idx[ss[1]]][idx[ss[0]]] = 1;
	}
	set<vector<int>> sett;
	for (auto &tnode : t)
	{
		
		int i = idx[tnode];
		for (int j = 0; j < n; j++)
		{
			if (tab[i][j])
			{
				for (int k = 0; k < n; k++)
				{
					if (k == i)
						continue;
					if (tab[j][k] && tab[i][k])
					{
						vector<int> v = { i,j,k };
						sort(v.begin(), v.end());
						sett.insert(v);
					}
				}
			}
		}
	}

	set<int> cl, big;

	largestclique(tab, cl, 0, big);
	vector<string> strs;
	for (auto i : big)
	{
		strs.push_back(idxRev[i]);
	}

	sort(strs.begin(), strs.end());


	cout << sett.size()<<" ";
	cout << strs[0];
	for (int i = 1; i < strs.size(); i++)
	{
		cout << "," << strs[i];
	}
}