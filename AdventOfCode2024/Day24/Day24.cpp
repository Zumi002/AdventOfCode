#include "../Utility/SupportFunc.h"
#include "Day24.h"
#include <set>
#include <unordered_map>
#include <queue>

enum op
{
	OR,
	XOR,
	AND
};

void reset(long long x, long long y, vector<short> &vals, vector<bool> &was,queue<int> &q)
{
	for (int i = 0; i < vals.size(); i++)
	{
		vals[i] = -1;
		was[i] = false;
	}
	for (int i = 0; i < 45; i++)
	{
		vals[i] = (x & ((long long)1 << i))>0;
		vals[i + 45] = (y & ((long long)1 << i))>0;
		q.push(i);
		q.push(i + 45);
	}
}

void analyze(queue<int> q,
	vector<vector<bool>>& adjTab,
	vector<vector<vector<pair<string, op>>>>& tab,
	vector<bool> was,
	vector<short> vals,
	unordered_map<string, int>& idx,
	vector<string>& zwires)
{
	vector<string> ands(45);
	vector<string> ands2(45);
	vector<string> xors(45);
	vector<string> xors2(45);
	vector<string> ors(45);
	int n = vals.size();
	for (int i = 0; i < 45; i++)
	{
		int xorr = 0;
		int andd = 0;
		
	}
	
}

long long solve(queue<int> q, 
	vector<vector<bool>>& adjTab, 
	vector<vector<vector<pair<string,op>>>> &tab,
	vector<bool> was,
	vector<short> vals,
	unordered_map<string,int> &idx,
	vector<string> &zwires)
{
	int n = vals.size();
	while (q.size())
	{
		int v = q.front();
		q.pop();

		if (was[v])
			continue;
		was[v] = true;

		for (int j = 0; j < n; j++)
		{
			if (!adjTab[v][j] || v == j)
				continue;
			if (vals[j] != -1)
			{
				for (int w = 0; w < tab[v][j].size(); w++)
				{
					short opRes = 0;
					if (tab[v][j][w].second == op::OR)
					{
						opRes = vals[j] | vals[v];
					}
					if (tab[v][j][w].second == op::XOR)
					{
						opRes = vals[j] ^ vals[v];
					}
					if (tab[v][j][w].second == op::AND)
					{
						opRes = vals[j] & vals[v];
					}
					vals[idx[tab[v][j][w].first]] = opRes;




					q.push(idx[tab[v][j][w].first]);
				}
			}
		}
	}
	long long sum = 0;
	for (auto& zs : zwires)
	{
		int place = stoi(zs.substr(1));
		sum += (long long)(vals[idx[zs]]) << place;

	}
	return sum;
}

void Day24()
{
	myFile in = myFile();
	in.Open("Day24/in.txt");
	in.ReadFile();


	long long sum = 0, sum2 = 0;

	unordered_map<string, int> idx;
	unordered_map<int, string> idxRev;
	vector<short> vals;
	vector<string> zwires;
	queue<int> q;

	int i = 0;
	for (; i < in.nol; i++)
	{
		if (in.inputLines[i] == "")
			break;

		string s = in.inputWords[i][0].substr(0, 3);

		if (!idx.count(s))
		{
			if (s[0] == 'z')
				zwires.push_back(s);
			idx[s] = vals.size();
			idxRev[idx[s]] = s;
			vals.push_back(in.inputWords[i][1] == "1");
			q.push(idx[s]);
		}

	}
	i++;
	int tmp = i;

	for (; i < in.nol; i++)
	{
		string s1 = in.inputWords[i][0];
		string s2 = in.inputWords[i][2];
		string s3 = in.inputWords[i][4];
		if (!idx.count(s1))
		{
			if (s1[0] == 'z')
				zwires.push_back(s1);
			idx[s1] = vals.size();
			idxRev[idx[s1]] = s1;
			vals.push_back(-1);
		}
		if (!idx.count(s2))
		{
			if (s2[0] == 'z')
				zwires.push_back(s2);
			idx[s2] = vals.size();
			idxRev[idx[s2]] = s2;
			vals.push_back(-1);
		}
		if (!idx.count(s3))
		{
			if (s3[0] == 'z')
				zwires.push_back(s3);
			idx[s3] = vals.size();
			idxRev[idx[s3]] = s3;
			vals.push_back(-1);
		}
	}
	i = tmp;
	int n = vals.size();
	vector<vector<bool>> adjTab(n, vector<bool>(n, false));
	vector<vector<vector<pair<string, op>>>> tab(n, vector<vector<pair<string, op>>>(n));
	for (; i < in.nol; i++)
	{
		string s1 = in.inputWords[i][0];
		string s2 = in.inputWords[i][2];
		string s3 = in.inputWords[i][4];

		op operation = in.inputWords[i][1] == "OR" ? op::OR : (in.inputWords[i][1] == "XOR" ? op::XOR : op::AND);

		tab[idx[s1]][idx[s2]].push_back({ s3,operation });
		tab[idx[s2]][idx[s1]].push_back({ s3,operation });
		adjTab[idx[s1]][idx[s2]] = true;
		adjTab[idx[s2]][idx[s1]] = true;
	}

	vector<bool> was(n, false);

	cout << solve(q, adjTab, tab, was, vals, idx, zwires)<<"\n";

	//FOR PART 2, then with pen and paper using binary adder schema 
	for (long long i = 0; i < 45; i++)
	{
		cout << i << ":\n";
		reset((long long)1 << i, 0, vals, was, q);
		long long res = solve(q, adjTab, tab, was, vals, idx, zwires);
		cout << res<< " " << (res == ((long long)1 << i)) << "\n";
		reset(0, (long long)1 << i, vals, was, q);
		res = solve(q, adjTab, tab, was, vals, idx, zwires);
		cout << res << " " << (res == ((long long)1 << i)) << "\n";
		reset((long long)1<<i, (long long)1 << i, vals, was, q);
		res = solve(q, adjTab, tab, was, vals, idx, zwires);
		cout << res << " " << (res == ((long long)1 << (i+1))) << "\n\n";
	}
	


	
	cout << "\n"<<sum;
}