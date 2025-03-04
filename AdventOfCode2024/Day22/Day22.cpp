#include "../Utility/SupportFunc.h"
#include "Day22.h"
#include <utility>
#include <unordered_map>
#include <set>
#include <unordered_set>

#define MOD 16777216

constexpr long long mod = (1 << 24) - 1;

long long hashChange(int a, int b, int c, int d)
{
	return (long long)(a+9) * 1000000 + (long long)(b+9) * 10000 + (long long)(c+9) * 100 + (long long)(d+9);
}


struct secretN
{
	long long secret;
	int seq;
	vector<char> changes;
	vector<char> vals;

	secretN(long long s)
	{
		secret = s;
		seq = 0;
		changes.reserve(2000);
		vals.reserve(2000);
	}

	void GenNewSec()
	{
			long long old = secret;
			long long tmp = secret << 6;
			tmp ^= secret;
			tmp &=  mod;
			secret = tmp;
			tmp >>= 5;
			tmp ^= secret;
			tmp &= mod;
			secret = tmp;
			tmp <<= 11;
			tmp ^= secret;
			tmp &= mod;
			secret = tmp;
			changes.emplace_back((secret % 10) - (old % 10));
			vals.emplace_back((secret % 10));
	}
};


void Day22()
{
	myFile in = myFile();
	in.Open("Day22/in.txt");
	in.ReadFile();

	long long sum = 0;
	
	vector<secretN> secrets;
	


	for (int i = 0; i < in.nol; i++)
	{
		long long num = stoll(in.inputLines[i]);
		secrets.push_back(secretN(num));
	}
	unordered_map<long long, int> bananas;
	for(auto & secret : secrets)
	{
		for (int i = 0; i < 2000; i++)
		{
			secret.GenNewSec();
		}
		sum += secret.secret;
		//PART 2
		unordered_set<long long> usedHashes;
		for (int i = 0; i < 1996; i++)
		{
			
			int h = hashChange(secret.changes[i], secret.changes[i + 1], secret.changes[i + 2], secret.changes[i + 3]);
			if(usedHashes.find(h)==usedHashes.end())
				bananas[h] += secret.vals[i + 3];
			usedHashes.insert(h);
		}
		
	}
	long long maxBananas = 0;
	for (auto p : bananas)
	{
		maxBananas = max(maxBananas, (long long)p.second);
	}

	cout << sum<<"\n"<<maxBananas;
}