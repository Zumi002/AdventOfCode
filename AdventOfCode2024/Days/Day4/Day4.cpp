#include "../../Utility/SupportFunc.h"
#include "Day4.h"


void Day4()
{
	myFile in = myFile();
	in.Open("Days/Day4/in.txt");
	in.ReadFile();

	int sum = 0, sum2 = 0;

	string find = "XMAS";
	string f2 = "SAMX";
	string m = "MAS";
	string w = "SAM";
	for (int i = 0; i < in.nol; i++)
	{
		string s = in.inputLines[i];
		for (int j = 0; j < s.size(); j++)
		{
			
			if (s.substr(j, 4) == find || s.substr(j, 4) == f2)
			{
				sum++;
			}
			string v = "";
			if (i < in.nol - 3)
			{
				for (int k = 0; k < 4; k++)
				{
					v += in.inputLines[i + k][j];
				}
			}
			if (v == find || v == f2)
			{
				sum++;
			}
			string lv = "";
			if (i < in.nol - 3&&j<s.size()-3)
			{
				for (int k = 0; k < 4; k++)
				{
					lv += in.inputLines[i + k][j+k];
				}
			}
			if (lv == find || lv == f2)
			{
				sum++;
			}
			string rv = "";
			if (i < in.nol - 3 && j >=3)
			{
				for (int k = 0; k < 4; k++)
				{
					rv += in.inputLines[i + k][j - k];
				}
			}
			if (rv == find || rv == f2)
			{
				sum++;
			}
			string l = "";
			string r = "";
			if (in.inputLines[i][j] == 'A' && i >= 1 && i < in.inputLines.size() - 1 && j >= 1 && j < s.size() - 1)
			{
				l += in.inputLines[i - 1][j - 1];
				l += 'A';
				l += in.inputLines[i + 1][j + 1];
				r += in.inputLines[i + 1][j - 1];
				r += 'A';
				r += in.inputLines[i - 1][j + 1];
			}
			if ((r == w || r == m) && (l == w || l == m))
				sum2++;
		}
		
	}
	std::cout << sum<<" "<<sum2;
}
