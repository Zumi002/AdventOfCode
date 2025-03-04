#include "../Utility/SupportFunc.h"
#include "Day10.h"
#include <Windows.h>

#define STRENGHTEN_SIGNAL_CHECK if ((clock - 20) % 40 == 0)sum += clock * reg;
#define CLOCK_TICK clock += 1;
#define ADD_TO_REGISTER reg += stoi(in.inputWords[i][1]);
#define CRT_PIXEL_DRAW cout << (((clock-1) % 40 >= reg - 1 && (clock-1) % 40 <= reg + 1) ? "#" : ".");
#define CRT_NEWLINE_CHECK if (clock % 40 == 0)cout << "\n";
#define COMPUTER_TICK CLOCK_TICK\
					  STRENGHTEN_SIGNAL_CHECK\
					  CRT_PIXEL_DRAW\
					  CRT_NEWLINE_CHECK

void Day10()
{
	myFile in = myFile();
	in.Open("Day10/in.txt");
	in.ReadFile();

	int clock = 0,
		reg   = 1,
		sum   = 0;
	for (int i = 0; i < in.nol; i++)
	{
		COMPUTER_TICK
		if (in.inputWords[i][0] == "addx")
		{
			COMPUTER_TICK
			ADD_TO_REGISTER
		}
	}
	cout << sum;
}
