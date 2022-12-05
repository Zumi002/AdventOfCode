#include "../Utility/SupportFunc.h"
#include "Day5.h"

#include <stack>



void Day5()
{
	myFile in = myFile();
	in.Open("Day5/in.txt");
	in.ReadFile();

	stack<string> places[9], places2[9];
	
	//find starting pos of values in file
	int startingPos = 0;
	for (int i = 0; i < in.nol; i++)
	{
		if (in.inputWords[i][0] == "move")
		{
			startingPos = i - 3;
			break;
		}
	}

	//fill stacks with starting values
	for (int i = startingPos; i >= 0; i--)
	{
		for (int j = 0; j < 9; j++)
		{
			string toPlace = in.inputLines[i].substr(j*4, 3);
			if (toPlace != "   ")
			{
				places[j].push(toPlace);
				places2[j].push(toPlace);
			}
			
		}
	}

	for (int i = 10; i < in.nol; i++)
	{
		//get procedure info
		int quantity = stoi(in.inputWords[i][1]),
			from = stoi(in.inputWords[i][3]) - 1,
			to = stoi(in.inputWords[i][5]) - 1;

		stack<string> buffer;
		//part 1: stack->stack || part 2: stack->buffer->stack
		// 	        ^rev -> reverse order  ^rev  + ^rev -> normal  
		for (int j = 0; j < quantity; j++)
		{
			places[to].push(places[from].top());
			places[from].pop();

			buffer.push(places2[from].top());
			places2[from].pop();
		}
		//buffer->stack part from part2
		for (int j = 0; j < quantity; j++)
		{
			places2[to].push(buffer.top());
			buffer.pop();
		}

	}

	//print results
	for (int i = 0; i < 9; i++)
	{
		cout << places[i].top()[1];
	}
	cout << "\n";
	for (int i = 0; i < 9; i++)
	{
		cout << places2[i].top()[1];
	}
}
