#include "../Utility/SupportFunc.h"
#include "Day19.h"
#include <unordered_map>


bool possible(string& check, vector<string>& options, int pos)
{
	if (check.size() == pos)
		return true;
	for (string& opt : options)
	{
		if (check.size() >= pos + opt.size()) 
		{
			int k = 0;
			while (check[pos+k]==opt[k]&&k<opt.size())
			{
				k++;
			}
			if (k == opt.size())
			{
				if (possible(check, options, pos + k))
					return true;
			}
		}
	}
	return false;
}

long long possibleCount(string& check, vector<string>& options, int pos, unordered_map<string, long long>& posibles)
{
	if (check.size() == pos)
		return 1;
	if (posibles.count(check.substr(pos)))
		return posibles[check.substr(pos)];
	long long poss = 0;
	for (string& opt : options)
	{
		if (check.size() >= pos + opt.size())
		{
			int k = 0;
			while (check[pos + k] == opt[k] && k < opt.size())
			{
				k++;
			}
			if (k == opt.size())
			{
				if (posibles.count(check.substr(pos + k)))
					poss += posibles[check.substr(pos + k)];
				else
					poss += possibleCount(check, options, pos + k, posibles);
			}
		}
	}
	posibles[check.substr(pos)] = poss;
	return poss;
}

void Day19()
{
	myFile in = myFile();
	in.Open("Day19/in.txt");
	in.ReadFile();

	vector<string> opt;
	vector<string> toCh;
	
	long long sum = 0, sum2 = 0;

	for (auto s : in.inputWords[0])
	{
		if (s[s.size() - 1] == ',')
			opt.push_back(s.substr(0, s.size() - 1));
		else
			opt.push_back(s);
	}

	for (int i = 2; i < in.nol; i++)
	{
		toCh.push_back(in.inputLines[i]);
	}

	unordered_map<string, long long> posibles;

	for (string& s : toCh)
	{
		if (possible(s, opt, 0))
			sum++;
		sum2 += possibleCount(s, opt, 0, posibles);
		//cout << possibleCount(s, opt, 0, posibles) << " " << s << "\n";
	}
	cout << sum<<" "<<sum2;
}