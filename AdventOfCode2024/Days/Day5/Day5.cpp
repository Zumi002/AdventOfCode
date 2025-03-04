#include "../../Utility/SupportFunc.h"
#include "Day5.h"

#include <stack>
#include <unordered_map>

struct rule
{
	int first;
	int second;

	rule(int f, int s)
	{
		first = f;
		second = s;
	}
};

void Day5()
{
	myFile in = myFile();
	in.Open("Days/Day5/in.txt");
	in.ReadFile();

	int sum = 0, sum2 = 0;
	vector<rule> rules;
	int i = 0;
	for (; in.inputLines[i].size()>0; i++)
	{
		string s = in.inputLines[i];
		auto sp = split(s, '|');
		int a = stoi(sp[0]);
		int b = stoi(sp[1]);
		rules.push_back(rule(a, b));
	}

	for (i=i+1; i < in.nol; i++)
	{
		string s = in.inputLines[i];
		auto se = split(s, ',');
		unordered_map<int,int> printed;
		bool bad = false;
		int w = 1;
		for (string as : se)
		{
			int c = stoi(as);
			printed[c] = w++;
			
			for (auto r : rules)
			{
				if (printed[r.first] > 0 && printed[r.second] > 0 && printed[r.first]>printed[r.second])
				{

					bad = true;
					break;
				}
			}
			if (bad)
				break;
		}
		if (!bad)
		{
			sum += stoi(se[(se.size()) / 2]);
		}
		else
		{
			sort(se.begin(), se.end(), [&](string& lhs, string& rhs) {
				int a = stoi(lhs);
				int b = stoi(rhs);
				for (auto& r : rules)
				{
					if (r.first == a && r.second == b)
						return true;
					else if (r.second == a && r.first == b)
						return false;
				}
				return true;
				});
			sum2 += stoi(se[(se.size() / 2)]);
		}
	}

	cout <<sum<<" "<< sum2;
}
