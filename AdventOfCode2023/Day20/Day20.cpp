#include "../Utility/SupportFunc.h"
#include "Day20.h"
#include <unordered_map>
#include <queue>

enum Pulse
{
	LOW=0,
	HIGH
};

enum Type
{
	broad =1,
	flip,
	junc
};

struct Signal
{
	int power;
	string from, to;
	Signal(int p,string f,string t)
	{
		from = f;
		to = t;
		power = p;
	}
};

vector<int> pulses;
queue<Signal> sigs;

class Module
{
public:
	string name;
	vector<string> inputs;
	vector<string> outputs;
	unordered_map<string, Module*>& mods;
	vector<int> memory;
	bool flopState = false;
	int type;


	Module(vector<string> out, unordered_map<string, Module*>& ms, int t, string n) :mods(ms)
	{
		type = t;
		name = n;
		outputs = out;
	}
	void GiveIn(string n)
	{
		if (type != junc) return;
		inputs.push_back(n);
		memory.push_back(0);
	}
	void getPulse(int pulse,string n)
	{
		if (this == NULL)return;
		if (type == broad)
		{
			for (auto m : outputs)
			{
				pulses[pulse]++;
				sigs.push(Signal(pulse, name, m));
			}
		}
		else if (type == flip)
		{
			if (pulse == HIGH)return;
			flopState = !flopState;
			for (auto m : outputs)
			{
				pulses[flopState]++;
				sigs.push(Signal(flopState, name, m));
			}
		}
		else if (type == junc)
		{
			for (int i = 0; i < inputs.size(); i++)
			{
				if (inputs[i] == n)
				{
					memory[i] = pulse;
				}
			}
			int send = HIGH;
			for (int i = 0; i < memory.size(); i++)send &= memory[i];
			for (auto m : outputs)
			{
				pulses[send?LOW:HIGH]++;
				sigs.push(Signal(send?LOW:HIGH, name, m));
			}
		}
	}

};

void Day20()
{
	myFile in = myFile();
	in.Open("Day20/in.txt");
	in.ReadFile();

	pulses = vector<int>(2, 0);
	
	unordered_map<string, Module*> mods;
	unordered_map<string, Module*> juncs;
	for (int i = 0; i < in.nol; i++)
	{
		if (in.inputWords[i][0][0] != '%' && in.inputWords[i][0][0] != '&')
		{
			string n = in.inputWords[i][0];
			vector<string> out;
			for (int j = 2; j < in.now[i]; j++)
			{
				if (in.inputWords[i][j][in.inputWords[i][j].size() - 1] == ',')
				{
					out.push_back(in.inputWords[i][j].substr(0, in.inputWords[i][j].size() - 1));
				}
				else
				{
					out.push_back(in.inputWords[i][j]);
				}
			}
			Module* m = new Module(out, mods, broad, n);
			mods[n] = m;
		}
		if (in.inputWords[i][0][0] == '%')
		{
			string n = in.inputWords[i][0].substr(1, in.inputWords[i][0].size()-1);
			vector<string> out;
			for (int j = 2; j < in.now[i]; j++)
			{
				if (in.inputWords[i][j][in.inputWords[i][j].size() - 1] == ',')
				{
					out.push_back(in.inputWords[i][j].substr(0, in.inputWords[i][j].size() - 1));
				}
				else
				{
					out.push_back(in.inputWords[i][j]);
				}
			}
			Module* m = new Module(out, mods, flip, n);
			mods[n] = m;
		}
		if (in.inputWords[i][0][0] == '&')
		{
			string n = in.inputWords[i][0].substr(1, in.inputWords[i][0].size() - 1);
			vector<string> out;
			for (int j = 2; j < in.now[i]; j++)
			{
				if (in.inputWords[i][j][in.inputWords[i][j].size() - 1] == ',')
				{
					out.push_back(in.inputWords[i][j].substr(0, in.inputWords[i][j].size() - 1));
				}
				else
				{
					out.push_back(in.inputWords[i][j]);
				}
			}
			Module* m = new Module(out, mods, junc, n);
			mods[n] = m;
		}
	}

	for (auto p : mods)
	{
		for (auto m : p.second->outputs)
		{
			if(mods.count(m))mods[m]->GiveIn(p.second->name);
		}
	}
	bool exit =false,single = true;
	for (int i = 0; i < 10000; i++)
	{
		single = true;
		pulses[LOW]++;
		sigs.push(Signal(LOW, "button", "broadcaster"));
		while (sigs.size())
		{
			Signal now = sigs.front();
			sigs.pop();
			mods[now.to]->getPulse(now.power, now.from);
			if ((now.from == "nx" || now.from == "sp"|| now.from == "cc"|| now.from == "jq") && now.power == HIGH)
			{
				cout << now.from<<" on "<< i + 1 << "\n";
			}
		}

	}
	cout << (long long)pulses[0] * (long long)pulses[1];
}