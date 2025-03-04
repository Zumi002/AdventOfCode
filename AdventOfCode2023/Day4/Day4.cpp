#include "../Utility/SupportFunc.h"
#include "Day4.h"


void Day4()
{
	myFile in = myFile();
	in.Open("Day4/in.txt");
	in.ReadFile();

	int sum = 0, sum2 = 0;

	vector<int> multi(in.nol, 1);

	for (int i = 0; i < in.nol; i++)
	{
		vector<string> winning,myl;

		int s = 0;
		int j = 2;
		for (; in.inputWords[i][j][0]!='|'; j++)
		{
			if(in.inputWords[i][j].size())winning.push_back(in.inputWords[i][j]);
			
		}
		j += 1;
		for (; j < in.now[i]; j++)
		{
			
			for (string a : winning)
			{
				if (in.inputWords[i][j]==a)
				{
					if (s == 0)
					{
						s = 1;
						//cout << in.inputWords[i][j]<<" ";
						break;
					}
					else
					{
						s++;
						//cout << in.inputWords[i][j] << " ";
						break;
					}

				}
			}
			
		}
		for (int k = 0; k < s; k++)
		{
			multi[i + k + 1] += multi[i];
		}
		//cout <<s<< "s\n";
		//sum += s;

	}

	for (int a : multi)
	{
		sum += a;
	}
	cout << sum;
}
