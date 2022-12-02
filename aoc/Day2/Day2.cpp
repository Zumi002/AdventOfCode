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
	int score = 0, score2 = 0;
	for (int i = 0; i < in.nol; i++)
	{
		int a, b;
		a = in.inputWords[i][0][0] % 'A' + 1;
		b = in.inputWords[i][1][0] % 'X' + 1;
		score += b;
		if (a + 1 == b || a - 2 == b)
		{
			score += 6;
		}
		if (a == b)
		{
			score += 3;
		}

		if (b == 1)
		{
			score2 += a - 1 > 0 ? a - 1 : 3;
		}
		if (b == 2)
		{
			score2 += a;
			score2 += 3;
		}
		if (b == 3)
		{
			score2 += a + 1 < 4 ? a + 1 : 1;
			score2 += 6;
		}
	}
	cout << score << " " << score2;
}