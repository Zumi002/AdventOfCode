#include "../../Utility/SupportFunc.h"
#include "Day5.h"

#include <stack>

#define ll long long

void Day5()
{
	myFile in = myFile();
	in.Open("Days/Day5/in.txt");
	in.ReadFile();

	vector<pair<ll,ll>> seeds;
	for (int i = 1; i < in.now[0]; i+=2)
	{
		seeds.push_back({ strtoll(in.inputWords[0][i].c_str(), NULL, 10), strtoll(in.inputWords[0][i+1].c_str(), NULL, 10)-1});
	}
	vector<bool> converted(seeds.size(), false);
	for (int i = 1; i < in.nol; i++)
	{
		if (in.inputWords[i][1] == "map:")continue;
		if (in.inputLines[i] == "")
		{
			for (int k = 0; k < converted.size(); k++)converted[k] = false;
			for (auto seed : seeds)
			{
				cout << seed.first << " " << seed.second << "\n";
			}
			cout << "-----\n";
			continue;
		}
		ll d = strtoll(in.inputWords[i][0].c_str(),NULL,10);
		ll s = strtoll(in.inputWords[i][1].c_str(), NULL, 10);
		ll r = strtoll(in.inputWords[i][2].c_str(), NULL, 10);
		int m = seeds.size();
		for (int k = 0; k < m; k++)
		{
			ll a = seeds[k].first;
			ll ar = seeds[k].second;
			if (converted[k])continue;
			if (a >= s&& a<=s+r)
			{
				if (ar + a < s + r)
				{
					seeds[k].first = seeds[k].first - s + d;
					converted[k] = true;
				}
				else
				{
					seeds[k].first = seeds[k].first - s + d;
					seeds[k].second = s + r-1 - a;
					seeds.push_back({ s + r,a + ar - 1 - s - r });
					converted.push_back(false);
					converted[k] = true;
				}
			}
			else if (a+ar >= s && a <= s)
			{
				if (ar + a >= s + r)
				{
					seeds[k].second = s - a - 1;
					seeds.push_back({ d,r-1 });
					seeds.push_back({ s + r,a + ar - 1 - s - r });
					converted.push_back(true);
					converted.push_back(false);
				}
				else
				{
					seeds[k].second = s - a - 1;
					seeds.push_back({ d, a + ar -s -1});
					converted.push_back(true);
				}
			}

		}

	}

	ll mmin = INT_MAX;
	for (auto seed : seeds)
	{
		mmin = min(seed.first, mmin);
		cout << seed.first << " "<<seed.second<<"\n";
	}
	cout << mmin;
	return;
}
