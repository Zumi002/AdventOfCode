#include "../Utility/SupportFunc.h"
#include "Day7.h"
#include <stack>

bool test(vector<unsigned long long>& n, unsigned long long i, unsigned long long result, unsigned long long target)
{
	if (i >= n.size())
	{
		return result==target;
	}

	result += n[i];
	if (test(n, i + 1, result, target))
		return true;
	result -= n[i];
	result *= n[i];
	if (test(n, i + 1, result, target))
		return true;
	result /= n[i];
	string a = to_string(result);
	string b = to_string(n[i]);
	string c = a + b;
	result = stoull(c);
	if (test(n, i + 1, result, target))
		return true;
	result = stoull(a);
	return false;
}

void Day7()
{
	myFile in = myFile();
	in.Open("Day7/in.txt");
	in.ReadFile();

	unsigned long long sum = 0;

	for (unsigned long long i = 0; i < in.nol; i++)
	{
		
			unsigned long long target = stoull(in.inputWords[i][0].substr(0, in.inputWords[i][0].size() - 1));
			vector<unsigned long long> w;
			for (unsigned long long k = 1; k < in.now[i]; k++)
			{
				w.push_back(stoull(in.inputWords[i][k]));
			}
			if (test(w, 1, w[0], target))
			{
				sum += target;
			}
	
		
	}

	cout << sum;
	
}
