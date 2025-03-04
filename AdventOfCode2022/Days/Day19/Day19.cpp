#include "../../Utility/SupportFunc.h"
#include "Day19.h"

class Resources
{
public:
	Resources()
	{
		vals[0] = 0;
		vals[1] = 0;
		vals[2] = 0;
		vals[3] = 0;
	}

	void printRes()
	{
		cout << "-ore: " << vals[0]<<"\n";
		cout << "-clay: " << vals[1] << "\n";
		cout << "-obsidian: " << vals[2] << "\n";
		cout << "-geode: " << vals[3] << "\n\n";
	}
	void buyWith(Resources cost)
	{
		for (int i = 0; i < 4; i++)
		{
			vals[i] -= cost.vals[i];
		}
	}
	int vals[4];
};

class BluePrint
{
public:
	
	//0 - ore cost, 1 - clay cost, 2 - obsidian cost, 3 - geode cost
	Resources costs[4];

	int maxNeeded[4];
	//id * most geo
	int value = 0;

	void giveCost(string type, int quantity, string what)
	{
		int res = 0;
		int whatRes = 0;
		if (type == "ore") res = 0;
		else if (type == "clay") res = 1;
		else if (type == "obsidian") res = 2;
		else if (type == "geode") res = 3;

		if (what == "ore") whatRes = 0;
		else if (what == "clay") whatRes = 1;
		else if (what == "obsidian") whatRes = 2;
		else if (what == "geode") whatRes = 3;

		costs[res].vals[whatRes] = quantity;
		if (maxNeeded[whatRes] < quantity) maxNeeded[whatRes] = quantity;
		maxNeeded[3] = 25;
	}

	void printCosts()
	{
		cout << "Ore :\n";
		costs[0].printRes();
		cout << "Clay :\n";
		costs[1].printRes();
		cout << "Obsidian :\n";
		costs[2].printRes();
		cout << "Geode :\n";
		costs[3].printRes();
	}

};

bool afford(Resources buyWith, Resources costs)
{
	for (int i = 0; i < 4; i++)
	{
		if (buyWith.vals[i] < costs.vals[i]) return false;
	}
	return true;
}

//options are: 0-wait, 1-build ore, 2-clay, 3-obsidian, 4-geode
int NextMinute(int minutesleft, int option, BluePrint *scheme, Resources myRes, int oreBots,int clayBots, int obsBots,int geoBots,int botsSum)
{
	//add ores
	
	myRes.vals[0] += oreBots;
	myRes.vals[1] += clayBots;
	myRes.vals[2] += obsBots;
	myRes.vals[3] += geoBots;
	//if (botsSum < 2 && minutesleft < 14)return 0;
	if (minutesleft == 1)
	{
		return myRes.vals[3];
	}
	//build robots if option says
	if (option != 0)
	{
		switch (option)
		{
			case 1:
				oreBots += 1;
				break;
			case 2:
				clayBots += 1;
				break;
			case 3:
				obsBots += 1;
				break;
			case 4:
				geoBots += 1;
				break;
		}
		botsSum += 1;
		myRes.buyWith(scheme->costs[option-1]);
	}

	//search options
	vector<int> options;
	bool canBuildGeos = false;

	if (oreBots < scheme->maxNeeded[0])
	{
		if (afford(myRes, scheme->costs[0]))
		{
			options.push_back(1);
		}
	}
	if (clayBots < scheme->maxNeeded[1])
	{
		if (afford(myRes, scheme->costs[1]))
		{
			options.push_back(2);
		}
	}
	if (obsBots < scheme->maxNeeded[2])
	{
		if (afford(myRes, scheme->costs[2]))
		{
			options.push_back(3);
		}
	}
	if (afford(myRes, scheme->costs[3]))
	{
			options.push_back(4);
	}
	if(botsSum<3||options.size()==0)options.push_back(0);

	//consider each option
	//take max value of them
	int maxScore = 0;
	if (canBuildGeos)
	{
		maxScore = NextMinute(minutesleft - 1, 4, scheme, myRes, oreBots,clayBots,obsBots,geoBots,botsSum);
	}
	else
	{
		for (int a : options)
		{
			int score = NextMinute(minutesleft - 1, a, scheme, myRes, oreBots, clayBots, obsBots, geoBots,botsSum);
			if (score > maxScore)maxScore = score;
			//if (minutesleft == 20) cout << "One path led to " << score << " score\n";
		}
	}
	return maxScore;
}

void Day19()
{
	myFile in = myFile();
	in.Open("Days/Day19/in.txt");
	in.ReadFile();

	//0- ore 1-clay 2- obsidian 3-geode
	vector<int> resources;
	vector<BluePrint*> schemats;

	int sum = 0;

	for (int i = 0; i < in.nol; i++)
	{
		BluePrint* a = new BluePrint();
		schemats.push_back(a);

		string type = "";
		int quantity = 0;
		string what = "";
		for (int j = 0; j < in.now[i]; j++)
		{
			if (in.inputWords[i][j] == "Each")
			{
				j++;
				type = in.inputWords[i][j];
				j++;
			}
			if (in.inputWords[i][j] == "costs")
			{
				do
				{
					j++;
					quantity = stoi(in.inputWords[i][j]);
					j++;
					what = split(in.inputWords[i][j], '.')[0];
					j++;

					a->giveCost(type, quantity, what);
				}
				while (in.inputWords[i][j] == "and");
				j--;
			}
			
		}
	}
	int best[3];
	/*
	* ONLY PART TWO, FOR PART 1 COMENTED, AND YOU SHOULD CHANGE i<3 TO i<schemats.size()
	*/
	for (int i = 0;i<3;i++)
	{
		BluePrint* a = schemats[i];

		Resources myres;
		//int score = NextMinute(24, 0, a, myres, 1,0,0,0,1);
		best[i] = NextMinute(32, 0, a, myres, 1, 0, 0, 0, 1);
		cout << best[i] << " \n";
	}

	cout<<"\n" << best[0]*best[1]*best[2];
}