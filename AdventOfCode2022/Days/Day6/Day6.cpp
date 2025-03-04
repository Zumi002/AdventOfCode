#include "../../Utility/SupportFunc.h"
#include "Day6.h"
#include <queue>


//added in SupportFunc.cpp
/*
int FirstUniqeCharsIndex(string str, int span, int step)
{
	int sliderLeft = 0, sliderRight = sliderLeft + span;
	while (sliderRight < str.size())
	{
		set<char> lstChars;
		for (char a : str.substr(sliderLeft, span))lstChars.insert(a);
		if (lstChars.size() == span) return sliderRight;
		sliderLeft += step;
		sliderRight += step;
	}
	return -1;
}
*/

void Day6()
{
	myFile in = myFile();
	in.Open("Days/Day6/in.txt");
	in.ReadFile();
	cout<<FirstUniqeCharsIndex(in.inputLines[0], 4, 1)<<" "<< FirstUniqeCharsIndex(in.inputLines[0], 14, 1);
}