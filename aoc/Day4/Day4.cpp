#include "../Utility/SupportFunc.h"
#include "Day4.h"


void Day4()
{
	myFile in = myFile();
	in.Open("Day4/in.txt");
	in.ReadFile();

	int sum = 0, sum2 = 0;

	for (int i = 0; i < in.nol; i++)
	{
		vector<string> leftRange = split(split(in.inputLines[i], ',')[0], '-'),
			       rightRange = split(split(in.inputLines[i], ',')[1], '-');

		int a = stoi(leftRange[0]),  b = stoi(leftRange[1]),
		    c = stoi(rightRange[0]), d = stoi(rightRange[1]);
		
		// part 1
		if (a <= c && d <= b)
		{
			sum++;
		}
		else if (c <= a && b <= d)
		{
			sum++;
		}

		// part 2
		if ((a <= c && c <= b) || (a <= d && d <= b))
		{
			sum2++;
		}
		else if ((c <= b && b <= d) || (c <= a && a <= d))
		{
			sum2++;
		}
	}
	cout << sum<<" " <<sum2;
}
