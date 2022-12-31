#include "../Utility/SupportFunc.h"
#include "Day24.h"
#include <set>
#include <memory>

#define SIZEX 122
#define SIZEY 27

char map[SIZEY][SIZEX];// change here and print constants and wind boundries

class Wind
{
	public:
	//0-right,1-down,2-left,3-up
	int dir = 0;
	//y,x boundires
	int boundry[4]={0,SIZEY - 1,0,SIZEX - 1};
	int x,y;

	void getDirAndCoords(char dr,int a1,int a2)
	{
		if(dr=='^') dir = 3;
		else if(dr == '>') dir = 0;
		else if(dr == '<') dir = 2;
		else if(dr == 'v') dir = 1;
		x = a2;
		y = a1;
	}

	void move()
	{
		//cout<<x<<" "<<y<<"\n";
		if(dir == 3)
		{
			y-=1;
			if(boundry[0]==y)
			{
				y = boundry[1]-1;
			}
		}
		else if(dir == 1)
		{
			y+=1;
			if(boundry[1]==y)
			{
				y = boundry[0]+1;
			}
		}
		else if(dir == 0)
		{
			x+=1;
			if(boundry[3]==x)
			{
				x = boundry[2]+1;
			}
		}
		else if(dir == 2)
		{
			x-=1;
			if(boundry[2]==x)
			{
				x = boundry[3]-1;
			}
		}
	}


};

class Elf
{
	public:
	int x,y;

	Elf(pair<int,int> a)
	{
		x = a.second;
		y = a.first;
	}

	set<pair<int,int>> possibleMoves()
	{
		set<pair<int,int>> ret;
		if(map[y][x]!='#')
		{
			ret.insert(make_pair(y,x));
		}
		if(map[y][x+1]!='#')
		{
			ret.insert(make_pair(y,x+1));
		}
		if(map[y][x-1]!='#')
		{
			ret.insert(make_pair(y,x-1));
		}
		if(y>0&&map[y-1][x]!='#')
		{
			ret.insert(make_pair(y-1,x));
		}
		if(y<SIZEY&&map[y+1][x]!='#')
		{
			ret.insert(make_pair(y+1,x));
		}
		return ret;
	}
};

void printMapp()
{
	for (int i = 0; i < SIZEY; i++)
	{
		for(int j = 0;j<SIZEX;j++)
		{
			std::cout<<map[i][j];
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

void clearMap()
{
	for (int i = 1; i < SIZEY-1; i++)
	{
		for(int j = 1;j<SIZEX-1;j++)
		{
			map[i][j] ='.';
		}
	}
}

void nextWinds(vector<shared_ptr<Wind>> &winds)
{
	clearMap();
	//cout<<"moving wind..";
	int i = 0;
	for(shared_ptr<Wind> a : winds)
	{
		a->move();
		//cout<<i++<<": "<<a->y<<" "<<a->x<<"\n";
		map[a->y][a->x] = '#';
	}
	//cout<<"ok\n";

}

void Day24()
{
	myFile in = myFile();
	in.Open("Day24/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;

	vector<Elf> elfs;
	vector<shared_ptr<Wind>> winds;

	for (int i = 0; i < in.nol; i++)
	{
		for(int j = 0;j<in.inputLines[i].size();j++)
		{
			map[i][j] = in.inputLines[i][j];
			if(in.inputLines[i][j]!='.'&&in.inputLines[i][j]!='#')
			{
				shared_ptr<Wind> a(new Wind());
				a->getDirAndCoords(in.inputLines[i][j],i,j);
				winds.push_back(a);
			}
		}
	}
	Elf first(make_pair(0,1)); 
	elfs.push_back(first);
	set<pair<int,int>> GoNext;

	while(GoNext.find(make_pair(SIZEY-1,SIZEX - 2))== GoNext.end())
	{
		sum+=1;
		//cout<<sum<<"\n";
		nextWinds(winds);
		//cout<<sum;
		//GoNext.clear();
		set<pair<int,int>> nextToGo;
		for(Elf a : elfs)
		{
			set<pair<int,int>> toInsert = a.possibleMoves();
			nextToGo.insert(toInsert.begin(),toInsert.end());
		}
		GoNext = nextToGo;
		elfs.clear();
		elfs.shrink_to_fit();
		for(pair<int,int> a : GoNext)
		{
			//cout<<a.second<<" "<<a.first<<"\n";
			Elf b(a);
			elfs.push_back(b);
			//map[a.first][a.second] = 'E';
		}
		//printMap();
	}
	cout<<sum<<"\n";
	GoNext.clear();
	elfs.clear();
	elfs.shrink_to_fit();
	Elf second(make_pair(SIZEY-1,SIZEX-2)); 
	elfs.push_back(second);
	while(GoNext.find(make_pair(0,1))== GoNext.end())
	{
		sum+=1;
		//cout<<sum<<"\n";
		nextWinds(winds);
		//cout<<sum;
		//GoNext.clear();
		set<pair<int,int>> nextToGo;
		for(Elf a : elfs)
		{
			set<pair<int,int>> toInsert = a.possibleMoves();
			nextToGo.insert(toInsert.begin(),toInsert.end());
		}
		GoNext = nextToGo;
		elfs.clear();
		elfs.shrink_to_fit();
		for(pair<int,int> a : GoNext)
		{
			//cout<<a.second<<" "<<a.first<<"\n";
			Elf b(a);
			elfs.push_back(b);
			//map[a.first][a.second] = 'E';
		}
		//printMap();
	}
	GoNext.clear();
	elfs.clear();
	elfs.shrink_to_fit();
	Elf third(make_pair(0,1)); 
	elfs.push_back(third);
	while(GoNext.find(make_pair(SIZEY-1,SIZEX-2))== GoNext.end())
	{
		sum+=1;
		//cout<<sum<<"\n";
		nextWinds(winds);
		//cout<<sum;
		//GoNext.clear();
		set<pair<int,int>> nextToGo;
		for(Elf a : elfs)
		{
			set<pair<int,int>> toInsert = a.possibleMoves();
			nextToGo.insert(toInsert.begin(),toInsert.end());
		}
		GoNext = nextToGo;
		elfs.clear();
		elfs.shrink_to_fit();
		for(pair<int,int> a : GoNext)
		{
			//cout<<a.second<<" "<<a.first<<"\n";
			Elf b(a);
			elfs.push_back(b);
			//map[a.first][a.second] = 'E';
		}
		//printMap();
	}


	
	std::cout << sum;
}