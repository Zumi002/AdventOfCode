#include "../../Utility/SupportFunc.h"
#include "Day8.h"
#include <utility>
#include <set>

class Node
{
public:
	string name;
	Node* left, * right;
};

Node* search(string name,vector<Node*> nodes)
{
	for (auto n : nodes)
	{
		if (n->name == name)
		{
			return n;
		}
	}
}



void Day8()
{
	myFile in = myFile();
	in.Open("Days/Day8/in.txt");
	in.ReadFile();

	int sum = 0;
	string inst = in.inputLines[0];
	vector<Node*> nodes(in.nol - 2);
	vector<string> names;
	for (int i = 2; i <in.nol; i++)
	{
		nodes[i - 2] = new Node();
		nodes[i - 2]->name = in.inputWords[i][0];
		names.push_back(nodes[i - 2]->name);
	}
	for (int i = 2; i < in.nol; i++)
	{
		nodes[i - 2]->left = search(in.inputWords[i][2].substr(1, in.inputWords[i][2].size()-2),nodes);
		nodes[i - 2]->right = search(in.inputWords[i][3].substr(0, in.inputWords[i][2].size() - 2), nodes);
	}
	int steps = 0;
	int ins = 0;
	vector<Node*> targets;
	vector<vector<pair<string, int>>> history;

	for (string s : names)
	{
		if (s[2] == 'A')
		{
			vector<pair<string, int>> tmp;
			targets.push_back(search(s, nodes));
			tmp.push_back({ s,0 });
			history.push_back(tmp);
		}
	}

	bool ok = false;
	while (!ok)
	{
		ok = true;
		if (inst[ins] == 'R')
		{
			for (int i = 0; i < targets.size(); i++)
			{
				targets[i] = targets[i]->right;
				if (targets[i]->name[2] != 'Z')ok = false;
				else cout << i << ": " << targets[i]->name << " in " << steps << "\n";
			}
		}
		else
		{
			for (int i = 0; i < targets.size(); i++)
			{
				targets[i] = targets[i]->left;
				if (targets[i]->name[2] != 'Z')ok = false;
				else cout << i << ": " << targets[i]->name << " in " << steps << "\n";
			}
		}
		ins++;
		if (ins == inst.size())ins = 0;
		steps++;
	}

	cout << steps;
}