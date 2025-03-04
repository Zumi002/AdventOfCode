#include "../Utility/SupportFunc.h"
#include "Day2.h"
#include <iostream>
#include <stdio.h>

using namespace std;


void Day2()
{
	myFile in = myFile();
	in.Open("Day2/in.txt");
	in.ReadFile();
	int a = 0, b = 0;
	
	for (int i = 0; i < in.nol; i++)
	{
		vector<int> stride;
		for (int j = 0; j < in.inputWords[i].size(); j++)
		{
			stride.push_back(stoi(in.inputWords[i][j]));
		}
		for (int k = -1; k < (int)stride.size(); k++)
		{
			bool side = (stride[0 + (0 == k)] - stride[1+(0==k)+(1==k)]) > 0;
			bool ok = true;
			for (int j = 0; j < stride.size() - 1; j++)
			{
				if (j == k || (j+1 + (j == k - 1)) == stride.size())
				{
					continue;
				}

				if (((stride[j] - stride[j + 1 + (j==k-1)]) > 0) != side || abs(stride[j] - stride[j + 1 + (j == k - 1)]) > 3 || abs(stride[j] - stride[j + 1 + (j == k - 1)]) < 1)
				{
					ok = false;
					break;
				}
			}
			if (ok)
			{
				if (k == -1)
				{
					a++;
				}
				else
				{
					b++;
					break;
				}
			}
		}
		
	}
	cout << a<<" "<<b;
}