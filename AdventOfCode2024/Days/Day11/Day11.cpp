#include "../../Utility/SupportFunc.h"

#include "Day11.h"

#include <unordered_map>

#define div 75

struct PairHash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& v) const
	{
		return std::hash<T1>()(v.first) ^ hash<T2>()(v.second)<<32;
		//return std::hash<T1>{}(v.first) ^ hash<T2>{}(v.second) << 1;    //same as above
	}
};

struct PairEqual {
	template <class T1, class T2>
	bool operator () (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const {
		return p1.first == p2.first && p1.second == p2.second;
	}
};
unordered_map<pair<long long, int>, long long, PairHash, PairEqual> splits;
class stone
{
public:
	
	long long val;
	string valS;

	stone(string v)
	{
		val = stoll(v);
	}

	stone(long long v)
	{
		val = v;
	}

	vector<stone> blink()
	{
		vector<stone> res;
		res.reserve(2);
		if (val == 0)
		{
			res.push_back(stone(1));
			return res;
		}
		valS = to_string(val);
		if (valS.size() % 2==0)
		{
			int h = valS.size() / 2;
			string f = valS.substr(0, h),
					s = valS.substr(h,h);

			res.push_back(stone(f));
			res.push_back(stone(s));
			return res;
		}
		res.push_back(stone(val*2024));
		return res;
	}

	//unordered_map<pair<long long, int>, long long, PairHash, PairEqual> stone::splits;

	long long eval(int splitsToGo)
	{
		if (splitsToGo == 0)
		{
			return 1;
		}
		if (splits.find({val, splitsToGo})==splits.end())
		{
			long long sum = 0;
			for (auto s : blink())
			{
				sum += s.eval(splitsToGo-1);
			}
			splits[{val, splitsToGo}] = sum;
		} 
		return splits[{val, splitsToGo}];
	}

};

void Day11()
{
	myFile in = myFile();
	in.Open("Days/Day11/in.txt");
	in.ReadFile();

	splits.clear();

	long long sum = 0;

	for (auto w : in.inputWords[0])
	{
		sum += stone(w).eval(div);
	}


	

	cout << sum;
}