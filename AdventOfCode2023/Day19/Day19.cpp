#include "../Utility/SupportFunc.h"
#include "Day19.h"
#include <unordered_map>

enum prop
{
	X =0,
	M,
	A,
	S
};

enum Type
{
	Controll = 1,
	Move,
	Accept,
	Reject,
	ACC,
	REJ
};

struct Condition
{
	int w = 0;
	bool greater = 0;
	int v = 0; 
	string to = "";
	int type = Controll;
	Condition(int a, bool b,int vv, string c,int t)
	{
		w = a;
		greater = b;
		to = c;
		type = t;
		v = vv;
	}
	Condition(string c,int t)
	{
		to = c;
		type = t;
	}

};

struct Part
{
	vector<int> prop;
	Part(int x, int m, int a, int s)
	{
		prop = vector<int>(4, 0);
		prop[0] = x;
		prop[1] = m;
		prop[2] = a;
		prop[3] = s;
	}
};

struct PartRange
{
	vector<vector<int>> prop;
	string startFrom;
	bool accepted = false;
	PartRange(vector<int> x, vector<int> m, vector<int> a, vector<int> s,string start)
	{
		prop = vector<vector<int>>(4);
		prop[0] = x;
		prop[1] = m;
		prop[2] = a;
		prop[3] = s;
		startFrom = start;
	}
	PartRange(PartRange *e)
	{
		prop = e->prop;
		startFrom = e->startFrom;
	}

};

class WorkFlow
{
	public:
	vector<Condition> cond;
	string name;
	unordered_map<string, WorkFlow*>& workflows;
	vector<PartRange*>& partRanges;
	WorkFlow(vector<Condition> conds, unordered_map<string, WorkFlow*>& wf, vector<PartRange*>& pr) :workflows(wf),partRanges(pr)
	{
		cond = conds;
	}

	int evalPart(Part e)
	{
		for (Condition a : cond)
		{
			if (a.type == Controll)
			{
				if (a.greater)
				{
					if (e.prop[a.w] > a.v)
					{
						return workflows[a.to]->evalPart(e);
					}
				}
				else
				{
					if (e.prop[a.w] < a.v)
					{
						return workflows[a.to]->evalPart(e);
					}
				}
			}
			else if (a.type == Move)
			{
				return workflows[a.to]->evalPart(e);
			}
			else if (a.type == Accept)
			{
				if (a.greater)
				{
					if (e.prop[a.w] > a.v)
					{
						int sum = 0;
						for (int k : e.prop)sum += k;
						return sum;

					}
				}
				else
				{
					if (e.prop[a.w] < a.v)
					{
						int sum = 0;
						for (int k : e.prop)sum += k;
						return sum;
					}
				}
			}
			else if (a.type == Reject)
			{
				if (a.greater)
				{
					if (e.prop[a.w] > a.v)
					{
						return 0;
					}
				}
				else
				{
					if (e.prop[a.w] < a.v)
					{
						return 0;
					}
				}
			}
			else if (a.type == ACC)
			{
				int sum = 0;
				for (int k : e.prop)sum += k;
				return sum;
			}
			else if (a.type == REJ)
			{
				return 0;
			}
		}
	}

	void evalPartRange(PartRange* e)
	{
		for (Condition a : cond)
		{
			if (a.type == Controll)
			{
				if (a.greater)
				{
					if (e->prop[a.w][0] > a.v)
					{
					   workflows[a.to]->evalPartRange(e);
					   return;
					}
					else if (e->prop[a.w][1]-1 > a.v)
					{
						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][1] = a.v + 1;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][0] = a.v+1;
						workflows[a.to]->evalPartRange(e);
						return;
					}
				}
				else
				{
					if (e->prop[a.w][1] <= a.v)
					{
						workflows[a.to]->evalPartRange(e);
						return;
					}
					else if (e->prop[a.w][0] < a.v)
					{
						
						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][0] = a.v;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][1] = a.v;
						workflows[a.to]->evalPartRange(e);
						return;
					}
				}
			}
			else if (a.type == Move)
			{
				 workflows[a.to]->evalPartRange(e);
				 return;
			}
			else if (a.type == Accept)
			{
				if (a.greater)
				{
					if (e->prop[a.w][0] > a.v)
					{
						e->accepted = true;
						return;
					}
					else if (e->prop[a.w][1] - 1 > a.v)
					{
						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][1] = a.v+1;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][0] = a.v + 1;
						e->accepted = true;
						return;
					}
				}
				else
				{
					if (e->prop[a.w][1] <= a.v)
					{
						e->accepted = true;
						return;
					}
					else if (e->prop[a.w][0] < a.v)
					{

						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][0] = a.v;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][1] = a.v;
						e->accepted = true;
						return;
					}
				}
			}
			else if (a.type == Reject)
			{
				if (a.greater)
				{
					if (e->prop[a.w][0] > a.v)
					{
						return;
					}
					else if (e->prop[a.w][1] - 1 > a.v)
					{
						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][1] = a.v + 1;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][0] = a.v + 1;
						return;
					}
				}
				else
				{
					if (e->prop[a.w][1] <= a.v)
					{
						return;
					}
					else if (e->prop[a.w][0] < a.v)
					{

						PartRange* newPartRange = new PartRange(e);
						newPartRange->prop[a.w][0] = a.v;
						newPartRange->startFrom = name;
						partRanges.push_back(newPartRange);
						e->prop[a.w][1] = a.v;
						return;
					}
				}
			}
			else if (a.type == ACC)
			{
				e->accepted = true;
				return;
			}
			else if (a.type == REJ)
			{
				return;
			}
		}
	}


};


void Day19()
{
	myFile in = myFile();
	in.Open("Day19/in.txt");
	in.ReadFile();

	unordered_map<string, WorkFlow*> wfs;
	vector<PartRange*> partRanges;

	int i = 0;
	for (; i < in.nol; i++)
	{
		if (in.inputLines[i].size() == 0)
		{
			i += 1;
			break;
		}
		string name = split(in.inputLines[i], '{')[0];
		string tmp = split(split(in.inputLines[i], '{')[1], '}')[0];
		vector<Condition> conds;
		vector<string> inst = split(tmp, ',');

		for (string ins : inst)
		{
			if (split(ins, ':').size() <= 1)
			{
				if (ins == "A")
				{
					conds.push_back(Condition("", ACC));
				}
				else if (ins == "R")
				{
					conds.push_back(Condition("", REJ));
				}
				else
				{
					conds.push_back(Condition(ins, Move));
				}
			}
			else
			{
				int prop = 0;
				int v = 0;
				bool g = 0;
				string to = "";
				if (ins[0] == 'a')prop = A;
				else if (ins[0] == 'x')prop = X;
				else if (ins[0] == 'm')prop = M;
				else if (ins[0] == 's')prop = S;
				if (ins[1] == '<')g = false;
				else g = true;
				
				vector<string> other = split(split(ins, g?'>':'<')[1],':');
				v = atoi(other[0].c_str());
				to = other[1];
				if (to == "A")
				{
					conds.push_back(Condition(prop, g, v, to, Accept));
				}
				else if (to == "R")
				{
					conds.push_back(Condition(prop, g, v, to, Reject));
				}
				else
				{
					conds.push_back(Condition(prop,g,v,to,Controll));
				}
			}
		}

		wfs[name] = new WorkFlow(conds, wfs,partRanges);
		wfs[name]->name = name;

	}
	/*P1
	vector<Part> parts;
	for (; i < in.nol; i++)
	{
		vector<string> tmp = split(split(in.inputLines[i],'}')[0], '=');
		vector<string> tmp2;
		for (string s : tmp)
		{
			for (string k : split(s, ','))
			{
				tmp2.push_back(k);
			}
		}
		int x = atoi(tmp2[1].c_str()),
			m = atoi(tmp2[3].c_str()),
			a = atoi(tmp2[5].c_str()),
			s = atoi(tmp2[7].c_str());
		parts.push_back(Part(x, m, a, s));
	}
	int sum = 0;
	for (Part e : parts)
	{
		sum+=wfs["in"]->evalPart(e);
	}*/
	partRanges.push_back(new PartRange({ 1,4001 }, { 1,4001 }, { 1,4001 }, { 1,4001 },"in"));
	long long count = 0;
	for (i = 0; i < partRanges.size(); i++)
	{
		wfs[partRanges[i]->startFrom]->evalPartRange(partRanges[i]);
		if (partRanges[i]->accepted)
		{
			long long sum = 1;
			for (int j = 0; j < 4; j++)
			{
				sum *= (long long)partRanges[i]->prop[j][1] - (long long)partRanges[i]->prop[j][0];
			}
			count += sum;
		}
	}
	cout << count;
}