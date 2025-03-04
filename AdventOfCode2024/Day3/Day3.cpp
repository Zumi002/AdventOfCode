#include "../Utility/SupportFunc.h"
#include "Day3.h"

using namespace std;

void Day3()
{
	myFile in = myFile();
	in.Open("Day3/in.txt");
	in.ReadFile();
	
	const string map = ".abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	int sum = 0, sum2 =0, sum3 =0, sum4 = 0;
	bool enable = true;
	for (int i = 0; i < in.nol; i++)
	{
		string s = in.inputLines[i];
		string k = "mul(";
		string l = "do()";
		string n = "don't()";
		
		for (int j = 0; j < s.size(); j++)
		{
			int a = 0;
			int b = 0;
			bool sw = false;
			bool wasa = false;
			bool wasb = false;
			bool good = true;
			string w = s.substr(j, 15);
			if (s.substr(j, 4) == l)
			{
				enable = true;
			}
			if (s.substr(j, 7) == n)
			{
				enable = false;
			}
			if (s.substr(j, 4) == k && enable)
			{
				for (int k = j + 4; k < s.size(); k++)
				{
					if (s[k] >= '0' && s[k] <= '9')
					{
						if (sw)
						{
							b *= 10;
							b += s[k] - '0';
							wasb = true;
						}
						else
						{
							a *= 10;
							a += s[k] - '0';
							wasa = true;
						}
					}
					else if (s[k] == ',')
					{
						if (sw)
						{
							good = false;
							break;
						}
						sw = true;

					}
					else if (s[k] == ')')
					{
						if (wasa && wasb)
						{
							sum += a * b;
							break;
						}
						else
							break;
					}
					else
						break;
				}
			}
		}
	}
	
	cout << sum << " ";
	return;
}