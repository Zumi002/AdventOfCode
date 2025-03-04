#include "../Utility/SupportFunc.h"
#include "Day16.h"
#include <map>


class Valve
{
	public:
	int PreasureFlow;
	string name;
	vector<Valve*> connections;
	map<string, int> distances;
	bool full = false;

	void slefCon()
	{
		distances.emplace(name, 0);
	}
	void getMap(map<string, int> other)
	{
		for (auto pair : other)
		{
			if (distances.find(pair.first) == distances.end())
			{
				distances.emplace(pair.first, pair.second+1);
			}
		}
	}
	bool CheckForFullMap(int numberOfEntries)
	{
		if (!full && numberOfEntries == distances.size()) full = true;
		return full;
	}
	void shareDis()
	{
		for (Valve* a : connections)
		{
			a->getMap(distances);
		}
	}

	void printCon()
	{
		std::cout << name;
		for (Valve* a : connections)
		{
			std::cout << " " << a->name;
		}
		std::cout << "\n";
	}
	void printDis()
	{
		std::cout <<"\n------------\n"<< name << " distances:\n";
		for (auto a : distances)
		{
			std::cout << a.first<<" " <<a.second<<"\n";
		}
		std::cout << "\n";
	}
};


//int NextMoveN(Valve* myActive, vector<Valve*>& interestingValves, int timeleft, int myDist, int eleDist)
//{
//	int maxNextMove = -10000;
//	if (timeleft > 0 && interestingValves.size())
//	{
//		int i = 0;
//		if (myDist != 0 && eleDist != 0)
//		{
//			return NextMove(myActive, eleActive, interestingValves, timeleft - 1, myDist - 1, eleDist);
//		}
//		else if (eleDist == 0)
//		{
//			for (Valve* a : interestingValves)
//			{
//				int dist = a->distances[myActive->name];
//				int nextMoveScore = a->PreasureFlow * (timeleft - dist - 1);
//				vector<Valve*> nextInterest = interestingValves;
//				nextInterest.erase(nextInterest.begin() + i);
//				nextMoveScore += NextMove(a, nextInterest, timeleft - 1, dist, 0);
//				if (nextMoveScore > maxNextMove)
//				{
//					maxNextMove = nextMoveScore;
//				}
//				i++;
//			}
//		}
//	}
//	if (maxNextMove < 0)return 0;
//	return maxNextMove;
//}

int NextMove(Valve* myActive, Valve* eleActive,vector<Valve*> &interestingValves, int timeleft,int myDist, int eleDist)
{
	int maxNextMove = -10000;
	if(timeleft > 0 && interestingValves.size())
	{
		
		if (myDist != 0&&eleDist!=0)
		{
			int a = myDist < eleDist ? myDist : eleDist;
			return NextMove(myActive,eleActive, interestingValves, timeleft - a, myDist-a,eleDist-a);
		}
		else if(eleDist==0&&myDist==0)
		{
			//my choice
			int i = 0;
			vector<Valve*> dontrepeat;
			for (Valve* a : interestingValves)
			{
				int dist = a->distances[myActive->name];
				int nextMoveScore = a->PreasureFlow * (timeleft - dist - 1);
				if ((timeleft - dist - 1) < 0) nextMoveScore = 0;
				vector<Valve*> nextInterest = interestingValves;
				nextInterest.erase(nextInterest.begin() + i);
				if(myActive==eleActive)dontrepeat.push_back(a);
				//ele choice
				int j = -1, maxEleScore = -100000;
				for (Valve* b : nextInterest)
				{
					j++;
					bool no = false;
					for (Valve* c : dontrepeat)
					{
						if (c == b)no = true;
					}
					if (no)continue;
					int eleDist = b->distances[eleActive->name];
					int bestEle = b->PreasureFlow * (timeleft - eleDist - 1);
					if ((timeleft - eleDist - 1) < 0) bestEle = 0;
					vector<Valve*> nextnextInterest = nextInterest;
					nextnextInterest.erase(nextnextInterest.begin() + j);
					bestEle += NextMove(a,b, nextnextInterest, timeleft - 1, dist,eleDist);
					if (bestEle > maxEleScore)
					{
						maxEleScore=bestEle;
					}
				}
				nextMoveScore += (maxEleScore > 0 ? maxEleScore : 0);
				if (nextMoveScore > maxNextMove)
				{
					maxNextMove = nextMoveScore;
				}
				i++;
			}
		}
		else if (myDist == 0)
		{
			//my choice
			int i = 0;
			for (Valve* a : interestingValves)
			{
				int dist = a->distances[myActive->name];
				int nextMoveScore = a->PreasureFlow * (timeleft - dist - 1);
				if ((timeleft - dist - 1) < 0) nextMoveScore = 0;
				vector<Valve*> nextInterest = interestingValves;
				nextInterest.erase(nextInterest.begin() + i);
				nextMoveScore += NextMove(a, eleActive, nextInterest, timeleft - 1, dist, eleDist-1);
				if (nextMoveScore > maxNextMove)
				{
					maxNextMove = nextMoveScore;
				}
				i++;
			}
		}
		else if (eleDist == 0)
		{
			//my choice
			int i = 0;
			for (Valve* a : interestingValves)
			{
				int dist = a->distances[eleActive->name];
				int nextMoveScore = a->PreasureFlow * (timeleft - dist - 1);
				if ((timeleft - dist - 1) < 0) nextMoveScore = 0;
				vector<Valve*> nextInterest = interestingValves;
				nextInterest.erase(nextInterest.begin() + i);
				nextMoveScore += NextMove(myActive, a, nextInterest, timeleft - 1, myDist-1, dist);
				if (nextMoveScore > maxNextMove)
				{
					maxNextMove = nextMoveScore;
				}
				i++;
			}
		}
	}
	if (maxNextMove < 0)return 0;
	return maxNextMove;
}


void Day16()
{
	myFile in = myFile();
	in.Open("Day16/in.txt");
	in.ReadFile();


	int sum = 0;
	vector<Valve*> valves;
	vector<string> names;
	for (int i = 0; i < in.nol; i++)
	{
		Valve* tmp = new Valve();
		tmp->name = in.inputWords[i][1];
		names.push_back(in.inputWords[i][1]);
		tmp->PreasureFlow = stoi(split(split(in.inputWords[i][4], '=')[1], ';')[0]);
		valves.push_back(tmp);
	}
	for (int i = 0; i < in.nol; i++)
	{
		for (int j = 9; j < in.inputWords[i].size(); j++)
		{
			string conName = split(in.inputWords[i][j], ',')[0];
			int l;
			for ( l = 0; l < names.size(); l++)
			{
				if (names[l] == conName)break;
			}
			valves[i]->connections.push_back(valves[l]);
		}
	}

	for (Valve* a : valves)
	{
		a->slefCon();
	}

	int full = 0;
	while (full != valves.size())
	{
		full = 0;
		for (Valve *a : valves)
		{
			a->shareDis();
			if (a->CheckForFullMap(valves.size())) full++;
		}
	}

	vector<Valve*> interestingValves;
	int i=0, index = 0;
	for (Valve* a : valves)
	{

		if (a->PreasureFlow > 0)interestingValves.push_back(a);
		if (a->name == "AA") index = i;
		i++;
	}

	
	int timeleft = 26;
	int fullScore = NextMove(valves[index], valves[index], interestingValves, timeleft,0,0);

	std::cout <<fullScore;
	cin >> fullScore;
}