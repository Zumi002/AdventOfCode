#include "../../Utility/SupportFunc.h"
#include "Day9.h"
#include <set>
#include <utility>


class Tail
{
	public:

	int x = 0, y = 0;

	Tail* myTail;
	bool tailSet = false,
		 chosen = false;

	set<pair<int, int>> visited;

	void Choose()
	{
		chosen = true;
	}

	void GiveTail(Tail *t)
	{
		myTail = t;
		tailSet = true;
	}

	void KeepUp(int xTo, int yTo)
	{
		int xDiff = xTo - x,
			yDiff = yTo - y;

		if (xDiff > 1||xDiff <-1)
		{
			x += xDiff>0?1:-1;
			if (yDiff == 1 || yDiff == -1)
			{
				y += yDiff > 0 ? 1 : -1;
			}
		}
		if (yDiff > 1 || yDiff < -1)
		{
			y += yDiff > 0 ? 1 : -1;
			if (xDiff == 1||xDiff==-1)
			{
				x += xDiff>0?1:-1;
			}
		}
		if(tailSet) myTail->KeepUp(x, y);
		if(chosen) visited.insert(make_pair(x, y));
	}
};


class Head
{
	public:

	int x=0, y=0;

	Tail* myTail;

	void GiveTail(Tail* t)
	{
		myTail = t;
	}

	void go(char dir,int steps)
	{
		for (int i = 0; i < steps; i++)
		{
			if (dir == 'L'||dir== 'R')
			{
				x += dir=='R'?1:-1;
			}
			else if (dir == 'U'||dir=='D')
			{
				y += dir == 'U' ? 1 : -1;
			}

			myTail->KeepUp(x,y);
		}
	}
};




void Day9()
{
	myFile in = myFile();
	in.Open("Days/Day9/in.txt");
	in.ReadFile();

	//part 1 - H and T
	Head h;
	Tail t;
	t.Choose();

	h.GiveTail(&t);

	//part2 = part1 + 8 knots 
	Tail knots[8];
	knots[7].Choose();

	//bond knots ant T together
	t.GiveTail(&knots[0]);
	for (int i = 0; i < 7; i++)
	{
		knots[i].GiveTail(&knots[i + 1]);
	}

	//move H
	for (int i = 0; i < in.nol; i++)
	{
		h.go(in.inputWords[i][0][0],stoi(in.inputWords[i][1]));
	}

	cout << t.visited.size() << " " << knots[7].visited.size();
}