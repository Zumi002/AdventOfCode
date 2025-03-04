#include "../Utility/SupportFunc.h"
#include "Day15.h"
#include <set>
#include <math.h>
#include <unordered_map>

int hashBox(int x, int y)
{
	return y * 100 + x;
}

struct box
{
	int x, y;

	box()
	{
		x = 0;
		y = 0;
	}

	box(int X, int Y)
	{
		x = X;
		y = Y;
	}

	void moveBox(char dir, vector<string>& map, unordered_map<int, box>& boxes)
	{
		int dx = 0, dy = 0;
		if (dir == '<')
			dx--;
		if (dir == '>')
			dx++;
		if (dir == 'v')
			dy++;
		if (dir == '^')
			dy--;

		if (dx != 0)
		{
			if(dx>0)
			{
				if (map[y][x + 1 + dx] == '[')
				{
					boxes[hashBox(x+1+dx, y)].moveBox(dir, map, boxes);
				}
			}
			else
			{
				if (map[y][x+dx] == ']')
				{
					boxes[hashBox(x - 1 + dx, y)].moveBox(dir, map, boxes);
				}
			}
		}
		if (dy != 0)
		{
			if (map[y+dy][x] == '[')
			{
				boxes[hashBox(x, y + dy)].moveBox(dir, map, boxes);
			}
			if (map[y+dy][x] == ']')
			{
				boxes[hashBox(x - 1, y + dy)].moveBox(dir, map, boxes);
			}
			if (map[y + dy][x+1] == '[')
			{
				boxes[hashBox(x + 1, y + dy)].moveBox(dir, map, boxes);
			}
		}
		map[y][x] = '.';
		map[y][x+1] = '.';
		x += dx;
		y += dy;
		map[y][x] = '[';
		map[y][x+1] = ']';
		boxes[hashBox(x, y)] = *this;
		
	}

	bool checkMove(char dir, vector<string>& map, unordered_map<int, box>& boxes)
	{
		int dx = 0, dy = 0;
		if (dir == '<')
			dx--;
		if (dir == '>')
			dx++;
		if (dir == 'v')
			dy++;
		if (dir == '^')
			dy--;

		if (dx != 0)
		{
			if (dx > 0)
			{
				if (map[y][x+1+dx] == '.')
					return true;
				else if (map[y][x + 1 + dx] == '#')
					return false;
				return boxes[hashBox(x + 1 + dx, y)].checkMove(dir, map, boxes);
			}
			else
			{
				if (map[y][x+dx] == '.')
					return true;
				else if (map[y][x + dx] == '#')
					return false;
				return boxes[hashBox(x - 1 + dx, y)].checkMove(dir, map, boxes);
			}
		}
		if (dy != 0)
		{
			if (map[y + dy][x] == '.' && map[y+dy][x+1] == '.')
				return true;
			if (map[y + dy][x] == '#' || map[y + dy][x + 1] == '#')
				return false;
			bool comp = true;
			if (map[y + dy][x] == '[')
			{
				comp = (comp && boxes[hashBox(x, y + dy)].checkMove(dir,map, boxes));
			}
			if (map[y + dy][x] == ']')
			{
				comp = (comp && boxes[hashBox(x-1, y + dy)].checkMove(dir, map, boxes));
			}
			if (map[y + dy][x+1] == '[')
			{
				comp = (comp && boxes[hashBox(x+1, y + dy)].checkMove(dir, map, boxes));
			}
			return comp;
		}
		return false;
	}
};

class robot
{
public:
	int x, y;
	robot(int X, int Y)
	{
		x = X;
		y = Y;
	}
	
	void move(char dir, vector<string> &map)
	{
		int dx = 0, dy = 0;
		if (dir == '<')
			dx--;
		if (dir == '>')
			dx++;
		if (dir == 'v')
			dy++;
		if (dir == '^')
			dy--;

		int tmpx = x+dx, tmpy = y+dy;
		bool ok = false;
		while (map[tmpy][tmpx] != '#')
		{
			if (map[tmpy][tmpx] == '.')
			{
				ok = true;
				break;
			}
			tmpy += dy;
			tmpx += dx;
		}

		if (ok)
		{
			if (dx != 0)
			{
				for (int w = tmpx; w != x+dx; w-=dx)
				{
					map[y][w] = 'O';
				}
				x += dx;
				map[y][x] = '.';
			}

			if (dy != 0)
			{
				for (int w = tmpy; w != y+dy; w-=dy)
				{
					map[w][x] = 'O';
				}
				y += dy;
				map[y][x] = '.';
			}
		}
	}

	void moveBig(char dir, vector<string>& map, unordered_map<int, box>& boxes)
	{
		int dx = 0, dy = 0;
		if (dir == '<')
			dx--;
		if (dir == '>')
			dx++;
		if (dir == 'v')
			dy++;
		if (dir == '^')
			dy--;

		map[y][x] = '.';

		if (map[y + dy][x + dx] == '.')
		{
			x += dx;
			y += dy;
			map[y][x] = '@';
			return;
		}
		if (map[y + dy][x + dx] == '#')
		{
			map[y][x] = '@';
			return;
		}
		if (map[y + dy][x + dx] == ']')
		{
			bool m = boxes[hashBox(x + dx - 1, y + dy)].checkMove(dir, map, boxes);
			if (m)
			{
				boxes[hashBox(x + dx - 1, y + dy)].moveBox(dir, map, boxes);
				x += dx;
				y += dy;
			}
			map[y][x] = '@';
			return;
		}
		if (map[y + dy][x + dx] == '[')
		{
			bool m = boxes[hashBox(x + dx, y + dy)].checkMove(dir, map, boxes);
			if (m)
			{
				boxes[hashBox(x + dx, y + dy)].moveBox(dir, map, boxes);
				x += dx;
				y += dy;
			}
			map[y][x] = '@';
			return;
		}
	}
};

void Day15()
{
	myFile in = myFile();
	in.Open("Day15/in.txt");
	in.ReadFile();
	
	long long sum = 0;
	
	vector<string> map;

	vector<string> bigMap;

	string instr = "";
	robot r = robot(0,0) ,bigR = robot(0,0);

	unordered_map<int, box> boxes;

	int i = 0;
	for( ; i < in.nol; i++)
	{
		if (in.inputLines[i].size() < 1)
		{
			i++;
			break;
		}
		string line = "";
		for (int j = 0; j < in.inputLines[i].size(); j++)
		{
			if (in.inputLines[i][j] == '@')
			{
				r = robot(j, i);
				in.inputLines[i][j] = '.';
				bigR = robot(2 * j, i);
				line += "..";
			}
			else if (in.inputLines[i][j]=='O')
			{
				line += "[]";
				boxes[hashBox(2 * j, i)] = box(2 * j, i);
			}
			else
			{
				
				line += string(2, in.inputLines[i][j]);
			}
		}
		map.push_back(in.inputLines[i]);
		bigMap.push_back(line);
	}
	for (; i < in.nol; i++)
	{
		instr += in.inputLines[i];
	}

	for (int i = 0; i < bigMap.size(); i++)
	{

		cout << bigMap[i] << "\n";
	}

	for (auto ch : instr)
	{
		//1
		//r.move(ch,map);
		 
		
		

		//2
		bigR.moveBig(ch,bigMap,boxes);

		/*for (int i = 0; i < bigMap.size(); i++)
		{

			cout << bigMap[i] << "\n";
		}
		cout << "\n";*/
	}

	for (int i = 0; i < bigMap.size(); i++)
	{
		for (int j = 0; j < bigMap[0].size(); j++)
		{
			if (bigMap[i][j] == '[')
			{
				sum += 100 * i + j;
			}
		}
		cout << bigMap[i] << "\n";
	}

	cout << sum;
}