#include "SupportFunc.h"


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