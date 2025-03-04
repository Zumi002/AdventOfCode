#include "../Utility/SupportFunc.h"
#include <iostream>

void Day1()
{
	myFile in = myFile();
	if (!in.Open("Day1/in.txt"))
	{
		cout << "wtf";
		return;
	}
	in.ReadFile();
	int max = 0, max2 = 0, max3 = 0;
	int current = 0, add = 0;;
	for (int i = 0; i < in.nol; i++)
	{
		if (in.inputLines[i] != "")
		{
			current += stoi(in.inputLines[i]);
		}
		else
		{
			if (current > max3)
			{
				max3 = current;
			}
			if (max3 > max2)
			{
				int tmp = max2;
				max2 = max3;
				max3 = tmp;
			}
			if (max2 > max)
			{
				int tmp = max;
				max = max2;
				max2 = tmp;
			}
			current = 0;
		}

	}
	cout <<max<<"   "<< max + max2 + max3<<"\n---------------\n";
}