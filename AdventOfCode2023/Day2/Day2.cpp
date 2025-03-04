#include "../Utility/SupportFunc.h"
#include "Day2.h"
#include <iostream>
#include <stdio.h>
#include <unordered_map>

using namespace std;


void Day2()
{
	myFile in = myFile();
	in.Open("Day2/in.txt");
	in.ReadFile();
	int score = 0,score2 = 0;
	unordered_map<string, int> maxOf = { {"blue",14},{"red",12},{"green",13} };
	for (int i = 0; i < in.nol; i++)
	{
		bool possible = true;
		int r = 0, g = 0, b = 0;
		for (int j = 2; j < in.now[i]; j += 2)
		{
			int howMuch = stoi(in.inputWords[i][j]);
			//cout << howMuch << " ";
			if (in.inputWords[i][j+1][0] == 'b')
			{
				b = max(b, howMuch);
				if (howMuch > 14)
				{
					possible = false;
				}
			}
			if (in.inputWords[i][j + 1][0] == 'g')
			{
				g = max(g, howMuch);
				if (howMuch > 13)
				{
					possible = false;
				}
			}
			if (in.inputWords[i][j + 1][0] == 'r')
			{
				r = max(r, howMuch);
				if (howMuch > 12)
				{
					possible = false;
				}
			}
		}
		//cout << "\n";
		if (possible)
		{
			//cout << in.inputWords[i][1];
			score += stoi(in.inputWords[i][1]);
		}
		//cout << r <<" "<< b <<" "<< g << "\n";
		score2 += r * b * g;
	}
	cout << score<<" "<<score2;
}