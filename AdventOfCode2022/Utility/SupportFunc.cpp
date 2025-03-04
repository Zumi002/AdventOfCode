#include "SupportFunc.h"
#include <set>

int ClampS(int x, int a)
{

	return x % a ? x % a : a;
}

vector<string> split(string str, char delimiter)
{
	vector<string> res;
	if (str == "")
	{
		res.push_back("");
	}
	string word = "";
	for (char a : str)
	{
		if (a == delimiter)
		{
			res.push_back(word);
			word = "";
		}
		else
		{
			word += a;
		}
	}
	res.push_back(word);
	return res;
}

int FirstUniqeCharsIndex(string str, int span, int step)
{
	int sliderLeft = 0, sliderRight = sliderLeft + span;
	while (sliderRight < str.size())
	{
		set<char> lstChars;
		for (char a : str.substr(sliderLeft, span))lstChars.insert(a);
		if (lstChars.size() == span) return sliderRight;
		sliderLeft += step;
		sliderRight += step;
	}
	return -1;
}

bool IsSubstrUniqe(string str)
{
	set<char> chars;
	for (char a : str)chars.insert(a);
	if (chars.size() == str.size()) return true;
	return false;
}