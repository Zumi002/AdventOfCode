#include "../Utility/SupportFunc.h"
#include "Day21.h"
#include <map>



class Monkey
{
public:
	long long number;
	string name;

	string operation = "";
	
	long long getNmber(vector<Monkey*> &monkeList, map<string,int> &names)
	{

		if (operation!="")
		{
			string name1 = split(operation, ' ')[0];
			//cout << name1 << " " << names[name1] << "\n";
			string name2 = split(operation, ' ')[2];

			//cout << name2 << " "<< names[name2]<<"\n";

			long long  num1 = monkeList[names[name1]]->getNmber(monkeList, names);
			long long  num2 = monkeList[names[name2]]->getNmber(monkeList, names);

			string op = split(operation, ' ')[1];

			if (op == "+")
			{
				//cout << name << " " << num1 + num2 << "\n";
				return num1 + num2;
			}

			if (op == "-")
			{
				//cout << name << " " << num1 - num2 << "\n";
				return num1 - num2;
			}

			if (op == "/")
			{
				//cout << name << " " << num1 / num2 << "\n";
				return num1 / num2;
			}

			if (op == "*")
			{
				//cout << name << " " << num1 * num2 << "\n";
				return num1 * num2;
			}
			cout << "wtf\n";
			return -2137;
		}
		else
		{
			//cout << name <<" "<<number<<"\n";
			return number;
		}
	}

	long long Chceck(vector<Monkey*>& monkeList, map<string, int>& names)
	{
		//left side
		//not calculated this, just been checking if 10000000000000 if smaller than target 20000000000000 if bigger than target 15000000000000, few tries and get it right
		monkeList[names["humn"]]->number = 3558714869436;
		string name1 = split(operation, ' ')[0];
		string name2 = split(operation, ' ')[2];
		long long  side1 = monkeList[names[name1]]->getNmber(monkeList, names);
		long long  side2 = monkeList[names[name2]]->getNmber(monkeList, names);
		cout << side1 << " " << side2<<"\n";

		return 0;
	}
};


vector<Monkey*> monkeList;
map<string, int> MonkeyNames;

void Day21()
{
	myFile in = myFile();
	in.Open("Day21/in.txt");
	in.ReadFile();

	long long  sum = 0, sum2 = 0;
	Monkey* monke;
	for (int i = 0; i < in.nol; i++)
	{
		monke = new Monkey();
		string monkeName = in.inputLines[i].substr(0, 4);
		MonkeyNames.emplace(make_pair(monkeName, i));
		monke->name = monkeName;
		if (in.now[i] < 4)
		{
			monke->number = stoi(in.inputWords[i][1]);
		}
		else
		{
			monke->operation = in.inputLines[i].substr(6, 11);
		}
		monkeList.push_back(monke);
	}
	
	sum = monkeList[MonkeyNames["root"]]->Chceck(monkeList, MonkeyNames);

	cout << sum;
}