#include "../Utility/SupportFunc.h"
#include "Day25.h"
#include <unordered_map>
#include <queue>
#include <set>

class Node
{
public:
	int id;
	unordered_map<int,int> idx;
	vector<Node*> con;
	vector<int> state;

	Node(int n)
	{
		id = n;
	}
	
	void Connect(Node* a)
	{
		idx[a->id] = con.size();
		con.push_back(a);
		state.push_back(0);
	}

	void ResetStates()
	{
		state.clear();
		state = vector<int>(con.size(), 0);
	}

	void ResetUnBlock()
	{
		for (int i = 0; i < state.size(); i++)
		{
			if(state[i]!=2)state[i] = 0;
		}
	}

	void BackClose()
	{
		//cout << id << " ";
		for (int i = 0; i < con.size(); i++)
		{
			if (state[i] == 1)
			{
				state[i] = 2;
				con[i]->state[con[i]->idx[id]] = 2;
				con[i]->BackClose();
				break;
			}
		}
	}
};

bool BFS(Node* start,Node* stop,unordered_map<int,Node*> &map)
{
	queue<Node*> q;
	set<int> s;
	s.insert(start->id);
	q.push(start);
	while (q.size() && q.front() != stop)
	{
		Node* n = q.front();
		q.pop();
		for (int i =0;i<n->con.size();i++)
		{
			Node* c = n->con[i];
			if (n->state[i] == 0)
			{

				if (!s.count(c->id))
				{
					q.push(c);
					s.insert(c->id);
					c->state[c->idx[n->id]] = 1;
				}
			}
		}
	}
	if (q.size() == 0)return false;
	stop->BackClose();
	//cout << "\n";
	for (int k : s)
	{
		map[k]->ResetUnBlock();
	}
	return true;

}

bool quadBFS(Node* start, Node* stop, unordered_map<int,Node*> &map)
{
	bool sameRegion = true;
	for (int i = 0; i < 4&&sameRegion; i++)
	{
		sameRegion = BFS(start, stop, map);
	}
	return sameRegion;
}

void Day25()
{
	myFile in = myFile();
	in.Open("Day25/in.txt");
	in.ReadFile();
	
	int n = 0;
	unordered_map<string, int> sId;
	unordered_map<int, Node*> map;

	vector<int>area(2, 0);

	for (int i = 0; i < in.nol; i++)
	{
		string s1 = in.inputWords[i][0];
		s1 = s1.substr(0, s1.size() - 1);
		if (!sId.count(s1))
		{
			Node* a = new Node(n);
			map[n] = a;
			sId[s1] = a->id;
			n++;
		}
		for (int j = 1; j < in.inputWords[i].size(); j++)
		{
			string s2 = in.inputWords[i][j];
			if (!sId.count(s2))
			{
				Node* a = new Node(n);
				map[n] = a;
				sId[s2] = a->id;
				n++;
			}
			map[sId[s1]]->Connect(map[sId[s2]]);
			map[sId[s2]]->Connect(map[sId[s1]]);
		}
	}
	area[1]++;
	for (int i = 1; i < n; i++)
	{
		area[quadBFS(map[0], map[i], map)]++;
		for (int j = 0; j < n; j++)map[j]->ResetStates();
	}
	cout << area[0] << " " << area[1] << " " << area[0] * area[1];
}