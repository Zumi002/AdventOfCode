#include "../../Utility/SupportFunc.h"
#include "Day11.h"


class Monkey
{
public:
	char operation;
	string argument;
	vector<long long> items;
	int moduloTest;
	int inscpectionCounter = 0;
	int SCM = 1;
	Monkey *ifTrue, *ifFalse;

	void test()
	{
		for(long long item : items)
		{
			inscpectionCounter += 1;
			if (operation == '*')
			{
				if (argument != "old")
				{
					item *= stoi(argument);
				}
				else
				{
					item *= item;
				}
			}
			else
			{
				if (argument != "old")
				{
					item += stoi(argument);
				}
				else
				{
					item += item;
				}
			}
			item /= 3;
			if (item % moduloTest == 0)
			{
				ifTrue->items.push_back(item);
			}
			else
			{
				ifFalse->items.push_back(item);
			}
		}
		items.clear();
	}
	void test2()
	{
		for (long long item : items)
		{
			inscpectionCounter += 1;
			if (operation == '*')
			{
				if (argument != "old")
				{
					item *= stoi(argument);
				}
				else
				{
					item *= item;
				}
			}
			else
			{
				if (argument != "old")
				{
					item += stoi(argument);
				}
				else
				{
					item += item;
				}
			}
			item%=SCM;
			if (item%moduloTest == 0)
			{
				ifTrue->items.push_back(item);
			}
			else
			{
				ifFalse->items.push_back(item);
			}
		}
		items.clear();
	}
};

void Day11()
{
	myFile in = myFile();
	in.Open("Days/Day11/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;
	Monkey monke[8], monke2[8];
	for (int i = 0; i < in.nol; i+=7)
	{
		monke[i/7].operation = in.inputWords[i + 2][6][0];
		monke[i/7].argument = in.inputWords[i + 2][7];
		monke[i/7].moduloTest = stoi(in.inputWords[i + 3][5]);
		monke[i/7].ifTrue = &monke[stoi(in.inputWords[i + 4][9])];
		monke[i/7].ifFalse = &monke[stoi(in.inputWords[i + 5][9])];
		for (int j = 4; j < in.now[i + 1]; j++)
		{
			if (in.inputWords[i + 1][j][in.inputWords[i + 1][j].size() - 1] == ',')
			{
				monke[i/7].items.push_back(stoi(in.inputWords[i + 1][j].substr(0, in.inputWords[i + 1][j].size() - 1)));
			}
			else monke[i/7].items.push_back(stoi(in.inputWords[i + 1][j]));
		}

		//part2 monkes
		monke2[i / 7].operation = in.inputWords[i + 2][6][0];
		monke2[i / 7].argument = in.inputWords[i + 2][7];
		monke2[i / 7].moduloTest = stoi(in.inputWords[i + 3][5]);
		monke2[i / 7].ifTrue = &monke2[stoi(in.inputWords[i + 4][9])];
		monke2[i / 7].ifFalse = &monke2[stoi(in.inputWords[i + 5][9])];
		for (int j = 4; j < in.now[i + 1]; j++)
		{
			if (in.inputWords[i + 1][j][in.inputWords[i + 1][j].size() - 1] == ',')
			{
				monke2[i / 7].items.push_back(stoi(in.inputWords[i + 1][j].substr(0, in.inputWords[i + 1][j].size() - 1)));
			}
			else monke2[i / 7].items.push_back(stoi(in.inputWords[i + 1][j]));
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			monke[j].test();
		}
	}
	long long max = 0, max2 = 0;
	for (int j = 0; j < 8; j++)
	{
		if (monke[j].inscpectionCounter > max)
		{
			max2 = max;
			max = monke[j].inscpectionCounter;
		}
		else if (monke[j].inscpectionCounter > max2)
		{
			max2 = monke[j].inscpectionCounter;
		}
		cout<<"Monke"<<j<<": "<<monke[j].inscpectionCounter;
	}
	cout <<"\n"<< max * max2;

	int testsSCM = 1;
	for (int j = 0; j < 8; j++)
	{
		testsSCM*=monke2[j].moduloTest;
	}
	for (int j = 0; j < 8; j++)
	{
		monke2[j].SCM = testsSCM;
	}
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			monke2[j].test2();
		}
	}
	max = 0, max2 = 0;
	for (int j = 0; j < 8; j++)
	{
		if (monke2[j].inscpectionCounter > max)
		{
			max2 = max;
			max = monke2[j].inscpectionCounter;
		}
		else if (monke2[j].inscpectionCounter > max2)
		{
			max2 = monke2[j].inscpectionCounter;
		}
		cout << "Monke" << j << ": " << monke2[j].inscpectionCounter;
	}
	cout << "\n" << max * max2;
}