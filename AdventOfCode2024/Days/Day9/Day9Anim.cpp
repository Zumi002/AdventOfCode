#include "../../Utility/SupportFunc.h"
#include "Day9Anim.h"
#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <vector>
#include <String>
#include <algorithm>
#include <Windows.h>

using namespace std;

class View
{
	vector<pair<int, int>> Special;
	vector<pair<int, int>> ImportantForNowSpecial;

	vector<pair<int, int>> RopeChunks;
	vector<pair<int, int>> LastRopeChunks;
	//camera pos sees 50 to right and fifty up
	int x = 0, y = 0;
	int minX = 0, maxX = 50,
		minY = 0, maxY = 25;
public:
	const char emptyRow[52] = "**************************************************\n";

	void draw()
	{
		printf("\033[%d;%dHCAM: PosX - %d PosY - %d", 26, 0, x, y);
		for (pair<int, int> cords : ImportantForNowSpecial)
		{
			printf("\033[%d;%dH#", 25 - (cords.second - y), cords.first - x);
		}
		int what = 10;
		for (pair<int, int> cords : LastRopeChunks)
		{
			if (cords.first - x < 0 || cords.first - x > 50 || cords.second - y < 0 || cords.second - y > 24)continue;
			printf("\033[%d;%dH*", 25 - (cords.second - y), cords.first - x);
		}
		for (pair<int, int> cords : RopeChunks)
		{
			what--;
			if (cords.first - x < 0 || cords.first - x > 50 || cords.second - y < 0 || cords.second - y > 24)continue;
			printf("\033[%d;%dH%c", 25 - (cords.second - y), cords.first - x, what > 0 ? (char)what + 48 : 'H');

		}
	}

	void newImportantSpecials()
	{
		ImportantForNowSpecial.clear();
		sort(Special.begin(), Special.end());
		for (int i = 0; i < Special.size(); i++)
		{
			if (Special[i].first < x)continue;
			if (Special[i].first > x + 49)break;
			if (Special[i].second<y || Special[i].second>y + 24)continue;
			ImportantForNowSpecial.push_back(Special[i]);
		}
	}

	void updateRopePosition(vector<pair<int, int>> newChunks)
	{
		LastRopeChunks.clear();
		for (pair<int, int> a : RopeChunks) LastRopeChunks.push_back(a);
		RopeChunks.clear();
		RopeChunks = newChunks;
		bool cameraChange = false;
		if (RopeChunks[9].first - x > 49)
		{
			x += 50;
			if (x > maxX)maxX = x + 50;
			cameraChange = true;
		}
		if (RopeChunks[9].first - x < 0)
		{
			x -= 50;
			if (x < minX)minX = x;
			cameraChange = true;
		}
		if (RopeChunks[9].second - y > 24)
		{
			y += 25;
			if (y > maxY)maxY = y + 25;
			cameraChange = true;
		}
		if (RopeChunks[9].second - y < 0)
		{
			y -= 25;
			if (y < minY)minY = y;
			cameraChange = true;
		}
		if (cameraChange)
		{
			newImportantSpecials();
			Start();
		}

	}

	void Start()
	{
		system("cls");
		printf("\033[2J");
		for (int i = 0; i < 25; i++)
		{
			printf("%s", emptyRow);
		}
	}

	void addSpecial(pair<int, int> newSpecial)
	{
		Special.push_back(newSpecial);
		newImportantSpecials();
	}

	string ToString()
	{
		string a = "";
		vector<string> lines;
		string tmp = "";
		maxY += 25;
		maxX += 50;
		for (int y = minY; y < maxY; y++)
		{
			tmp = "";
			for (int x = minX; x < maxX; x++)
			{
				tmp += "*";
			}
			tmp += "\n";
			lines.push_back(tmp);

		}

		for (pair<int, int> cords : Special)
		{
			lines[maxY - cords.second][cords.first - minX] = '#';

		}
		int what = 10;
		for (pair<int, int> cords : RopeChunks)
		{
			what--;
			lines[maxY - cords.second][cords.first - minX] = what > 0 ? (char)what + 48 : 'H';
		}
		lines[maxY - 0][0 - minX] = 'S';
		for (string b : lines)
		{
			a += b;
		}
		return a;
	}
};

class Rope
{
public:

	int x = 0, y = 0;

	Rope* myTail = nullptr;
	bool tailSet = false,
		chosen = false;

	int countVisisted = 0;
	View* Camera;
	set<pair<int, int>> visited;

	void Choose()
	{
		chosen = true;
	}

	void GiveTail(Rope* t)
	{
		myTail = t;
		tailSet = true;
	}

	void KeepUp(int xTo, int yTo)
	{
		int xDiff = xTo - x,
			yDiff = yTo - y;

		if (xDiff > 1 || xDiff < -1)
		{
			x += xDiff > 0 ? 1 : -1;
			if (yDiff == 1 || yDiff == -1)
			{
				y += yDiff > 0 ? 1 : -1;
			}
		}
		if (yDiff > 1 || yDiff < -1)
		{
			y += yDiff > 0 ? 1 : -1;
			if (xDiff == 1 || xDiff == -1)
			{
				x += xDiff > 0 ? 1 : -1;
			}
		}
		if (tailSet) myTail->KeepUp(x, y);
		if (chosen)
		{
			countVisisted = visited.size();
			visited.insert(make_pair(x, y));
			if (countVisisted < visited.size())Camera->addSpecial(make_pair(x, y));
		}
	}

	void go(char dir)
	{
		if (dir == 'L' || dir == 'R')
		{
			x += dir == 'R' ? 1 : -1;
		}
		else if (dir == 'U' || dir == 'D')
		{
			y += dir == 'U' ? 1 : -1;
		}

		myTail->KeepUp(x, y);
	}
};






void Day9Anim()
{
	myFile in = myFile();
	in.Open("Days/Day9/in.txt");
	in.ReadFile();

	ofstream out;

	Rope knots[10];

	//bond knots ant T together
	for (int i = 0; i < 9; i++)
	{
		knots[i].GiveTail(&knots[i + 1]);
	}

	knots[9].Choose();

	View Camera;
	knots[9].Camera = &Camera;
	Camera.Start();
	//move H
	for (int i = 0; i < in.nol; i++)
	{
		for (int g = 0; g < stoi(in.inputWords[i][1]); g++)
		{
			knots[0].go(in.inputWords[i][0][0]);
			vector<pair<int, int>> updatedCoords;
			for (int j = 9; j >= 0; j--)
			{
				updatedCoords.push_back(make_pair(knots[j].x, knots[j].y));
			}
			Camera.updateRopePosition(updatedCoords);
			Sleep(10);
			Camera.draw();

		}
	}
	out.open("Day9/out.txt");
	out << Camera.ToString();
	cout << "\n" << knots[9].visited.size();
}