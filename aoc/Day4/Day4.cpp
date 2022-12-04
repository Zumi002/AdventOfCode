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
		int a = stoi(in.inputWords[i][0]), b = stoi(in.inputWords[i][1]), c = stoi(in.inputWords[i][2]), d = stoi(in.inputWords[i][3]);
		
			if (a <= c && d <= b)
			{
				sum++;
			}
			else if (c <= a && b <= d)
			{
				sum++;
			}

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