#include "../Utility/SupportFunc.h"
#include "Day14.h"
#include <set>


#define sizeX 101
#define sizeY 103

class robot
{
public:
	int px, py;
	int vx, vy;

	robot(int x, int y, int vX, int vY)
	{
		px = x;
		py = y;
		vx = vX;
		vy = vY;
	}

	robot step()
	{
		px += vx;
		py += vy;
		
		px %= sizeX;
		py %= sizeY;

		while (px < 0)
			px += sizeX;

		while (py < 0)
			py += sizeY;

		return *this;
	}
};

void Day14()
{
	myFile in = myFile();
	in.Open("Day14/in.txt");
	in.ReadFile();


	int sum = 0;

	vector<robot> robots;

	for (int i = 0; i < in.nol; i++)
	{
		string inp = in.inputWords[i][0];
		inp = split(inp, '=')[1];
		string l = split(inp, ',')[0];
		string r = split(inp, ',')[1];

		string inp1 = in.inputWords[i][1];
		inp1 = split(inp1, '=')[1];
		string l1 = split(inp1, ',')[0];
		string r1 = split(inp1, ',')[1];

		robots.push_back(robot(stoi(l), stoi(r), stoi(l1), stoi(r1)));
	}

	for (int i = 0; i < 100000; i++)
	{
		for (int j = 0; j < robots.size(); j++)
		{
			robots[j] = robots[j].step();
		}
		//cout << "\n\n" << i + 1 << " \n";
		string pic = string(sizeX * sizeY,'.');

		int bad = false;
		for (auto& r : robots)
		{
			if (pic[r.px + r.py * sizeX] == '#')
				bad = true;
			pic[r.px + r.py * sizeX] = '#';
			
		}

		if (!bad)
		{
			cout << "\n\n" << i + 1 << " \n";
			for (int k = 0; k < sizeY; k++)
			{
				cout << pic.substr(k * sizeX, sizeX)<<"\n";
			}
		}
		///cout << "\n";
	}

	vector<int> quads(4,0);

	for (int j = 0; j < robots.size(); j++)
	{
		if (robots[j].px > sizeX / 2)
		{
			if (robots[j].py > sizeY / 2)
			{
				quads[3]++;
			}
			else if (robots[j].py < sizeY / 2)
			{
				quads[2]++;
			}
		}
		else if (robots[j].px < sizeX / 2)
		{
			if (robots[j].py > sizeY / 2)
			{
				quads[1]++;
			}
			else if (robots[j].py < sizeY / 2)
			{
				quads[0]++;
			}
		}
	}

	sum = 1;
	for (int i = 0; i < 4; i++)
		sum *= quads[i];
	
	std::cout << sum;
}