#include "../Utility/SupportFunc.h"
#include "Day3.h"

using namespace std;

void Day3()
{
	myFile in = myFile();
	in.Open("Day3/in.txt");
	in.ReadFile();
	int sum = 0, sum2 =0;
	int prio1[52]{}, prio2[52]{}, prio3[52]{};
	for (int i = 0; i < in.nol; i++)
	{
		string o = in.inputLines[i];
		string r1 = o.substr(0, o.size() / 2), r2 = o.substr((o.size() / 2), o.size() / 2);

		for (char a : r1) prio1[a <= 'Z' ? a % 'A' + 26 : a % 'a']++;
		for (char a : r2) prio2[a <= 'Z' ? a % 'A' + 26 : a % 'a']++;

		for (int i = 0; i < 52; i++)
		{
			if (prio1[i] && prio2[i])
			{
				sum += i + 1;
			}
			if (prio1[i])prio1[i] = 0;
			if (prio2[i])prio2[i] = 0;
		}
	}
	for (int i = 0; i < in.nol; i+=3)
	{
		string o1 = in.inputLines[i], o2= in.inputLines[i+1], o3=in.inputLines[i+2];

		for (char a : o1) prio1[a <= 'Z' ? a % 'A' + 26 : a % 'a']++;
		for (char a : o2) prio2[a <= 'Z' ? a % 'A' + 26 : a % 'a']++;
		for (char a : o3) prio3[a <= 'Z'?a % 'A' + 26: a % 'a']++;

		for (int i = 0; i < 52; i++)
		{
			if (prio1[i] && prio2[i] && prio3[i])
			{
				sum2 += i + 1;
			}
			if (prio1[i])prio1[i] = 0;
			if (prio2[i])prio2[i] = 0;
			if (prio3[i])prio3[i] = 0;
		}

	}
	cout << sum<<" "<<sum2;
	return;
}