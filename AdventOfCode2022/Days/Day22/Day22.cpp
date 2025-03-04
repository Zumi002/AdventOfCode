#include "../../Utility/SupportFunc.h"
#include "Day22.h"
#include <utility>

#define SIDEL 50

/*
* 
* ONLY PART TWO WHICH IS MUCH HARDER THAN PART ONE
* 
*/

class Side
{
	public:
		int id = 0;
		char sideMap[SIDEL + 2][SIDEL + 2];

		Side* Right = nullptr;
		Side* Down = nullptr;
		Side* Left = nullptr;
		Side* Up = nullptr;

		int faceChanging[4];

		Side()
		{
			for (int i = 0; i < SIDEL + 2; i++)
			{
				for (int j = 0; j < SIDEL+2; j++)
				{
					sideMap[i][j] = ' ';
				}
			}
			faceChanging[0] = 0;
			faceChanging[1] = 0;
			faceChanging[2] = 0;
			faceChanging[3] = 0;
		}

		void giveMap(vector<vector<char>> map)
		{
			for (int i = 1; i < SIDEL+1; i++)
			{
				for (int j = 1; j < SIDEL+1; j++)
				{
					sideMap[i][j] = map[i-1][j-1];
				}
			}
		}

		void giveSides(int a, int b, int c, int d, Side* right1, Side* down1, Side* left1, Side* up1)
		{
			faceChanging[0] = a;
			faceChanging[1] = b;
			faceChanging[2] = c;
			faceChanging[3] = c;

			Right = right1;
			Down = down1;
			Left = left1;
			Up = up1;
		}

		void printSide()
		{
			for (int i = 0; i < SIDEL + 2; i++)
			{
				for (int j = 0; j < SIDEL + 2; j++)
				{
					std::cout<<sideMap[i][j];
				}
				cout << "\n";
			}
			cout << "\n";
		}
};

pair<int, int> MakeMoveOnSide(pair<int, int> Pos, int* facing, Side &CurrSide, bool *hittedWall)
{
	pair<int, int> currPos = Pos;
	int x = currPos.second, y = currPos.first;
	//cout << x << " " << y << "\n";
	if (*facing == 3)
	{
		//cout << CurrSide.sideMap[y][x - 1] << "\n";
		if (CurrSide.sideMap[y - 1][x] == '.')
		{
			y -= 1;
			Pos = make_pair(y, x);
		}
		else
		{
			if (CurrSide.sideMap[y - 1][x] == ' ')
			{
				int nX = x, nY = 51-y;
				if (CurrSide.faceChanging[3] == 1)
				{
					nX = y;
					nY = x;
				}
				else if (CurrSide.faceChanging[3] == 2)
				{
					nX = 51-x;
					nY = y;
				}
				else if (CurrSide.faceChanging[3] == 3)
				{
					nX = y;
					nY = 51 - x;
				}
				if (CurrSide.Up->sideMap[nY][nX] == '.')
				{
					*facing += CurrSide.faceChanging[3];
					if (*facing <= -1) *facing += 4;
					if (*facing >= 4) *facing -= 4;
					cout << "changing cube from " << CurrSide.id << " to " << CurrSide.Up->id << "\n";
					CurrSide = *CurrSide.Up;
					cout << "current " << CurrSide.id << "\n";
					Pos = make_pair(nY, nX);
					
				}
				else
				{
					*hittedWall = true;
				}
			}
			else
			{
				*hittedWall = true;
			}
		}
	}
	else if (*facing == 1)
	{
		//cout << CurrSide.sideMap[y + 1][x] << "\n";
		//CurrSide.printSide();
		if (CurrSide.sideMap[y + 1][x] == '.')
		{
			y += 1;
			Pos = make_pair(y, x);
		}
		else
		{
			if (CurrSide.sideMap[y + 1][x] == ' ')
			{
				int nX = x, nY = 51-y;
				if (CurrSide.faceChanging[1] == 1)
				{
					nX = y;
					nY = x;
				}
				else if (CurrSide.faceChanging[1] == 2)
				{
					nX = 51 - x;
					nY = y;
				}
				else if (CurrSide.faceChanging[1] == 3)
				{
					nX = y;
					nY = 51 - x;
				}
				if (CurrSide.Down->sideMap[nY][nX] == '.')
				{
					*facing += CurrSide.faceChanging[1];
					if (*facing <= -1) *facing += 4;
					if (*facing >= 4) *facing -= 4;
					cout << "changing cube from " << CurrSide.id << " to " << CurrSide.Down->id << "\n";
					CurrSide = *CurrSide.Down;
					cout << "current " << CurrSide.id << "\n";
					Pos = make_pair(nY, nX);
					

				}
				else
				{
					*hittedWall = true;
				}
			}
			else
			{
				*hittedWall = true;
			}
		}
	}
	else if (*facing == 0)
	{
		//CurrSide.printSide();
		//cout << CurrSide.sideMap[y][x + 1] << "\n";
		if (CurrSide.sideMap[y][x + 1] == '.')
		{
			x += 1;
			Pos = make_pair(y, x);
		}
		else
		{
			if (CurrSide.sideMap[y][x + 1] == ' ')
			{
				int nX = 51-x, nY = y;
				if (CurrSide.faceChanging[0] == 1)
				{
					nX = 51-y;
					nY = x;
				}
				else if (CurrSide.faceChanging[0] == 2)
				{
					nX = x;
					nY = 51-y;
				}
				else if (CurrSide.faceChanging[0] == 3)
				{
					nX = y;
					nY = x;
				}
				if (CurrSide.Right->sideMap[nY][nX] == '.')
				{
					*facing += CurrSide.faceChanging[0];
					if (*facing <= -1) *facing += 4;
					if (*facing >= 4) *facing -= 4;
					cout << "changing cube from " << CurrSide.id << " to " << CurrSide.Right->id << "\n";
					CurrSide = *CurrSide.Right;
					cout << "current " << CurrSide.id << "\n";
					Pos = make_pair(nY, nX);

				}
				else
				{
					*hittedWall = true;
				}
			}
			else
			{
				*hittedWall = true;
			}
		}
	}
	else if (*facing == 2)
	{
		//cout << CurrSide.sideMap[y][x - 1] << "\n";
		if (CurrSide.sideMap[y][x - 1] == '.')
		{
			x -= 1;
			
			Pos = make_pair(y, x);
		}
		else
		{
			if (CurrSide.sideMap[y][x - 1] == ' ')
			{
				int nX = 51-x, nY = y;
				if (CurrSide.faceChanging[2] == 1)
				{
					nX = 51 - y;
					nY = x;
				}
				else if (CurrSide.faceChanging[2] == 2)
				{
					nX = x;
					nY = 51 - y;
				}
				else if (CurrSide.faceChanging[2] == 3)
				{
					nX = y;
					nY = x;
				}
				if (CurrSide.Left->sideMap[nY][nX] == '.')
				{
					*facing += CurrSide.faceChanging[2];
					if (*facing <= -1) *facing += 4;
					if (*facing >= 4) *facing -= 4;
					cout << "changing cube from " << CurrSide.id << " to " << CurrSide.Left->id << "\n";
					CurrSide = *CurrSide.Left;
					cout << "current " << CurrSide.id << "\n";
					Pos = make_pair(nY, nX);

				}
				else
				{
					*hittedWall = true;
				}
			}
			else
			{
				*hittedWall = true;
			}
		}
	}
	return Pos;
}

pair<int, int> MakeMove(pair<int, int> startPos, int facing, int steps, vector<vector<char>>& map)
{
	pair<int, int> currPos = startPos;
	int x = currPos.second, y = currPos.first;
	if (facing == 3)
	{
		for (int i = 0; i < steps; i++)
		{
			
			if (map[y - 1][x] == '.')
			{
				y -= 1;
			}
			else
			{
				if (map[y - 1][x] == ' ')
				{
					int nY = y+1;
					while (map[nY][x] != ' ')
					{
						nY += 1;
					}
					if (map[nY - 1][x] == '.')
					{
						y = nY-1;
						continue;
					}
				}
				break;
			}
			
		}
	}
	else if (facing == 1)
	{
		for (int i = 0; i < steps; i++)
		{

			if (map[y + 1][x] == '.')
			{
				y += 1;
			}
			else
			{
				if (map[y + 1][x] == ' ')
				{
					int nY = y-1;
					while (map[nY][x] != ' ')
					{
						nY -= 1;
					}
					if (map[nY + 1][x] == '.')
					{
						y = nY+1;
						continue;
					}
				}
				break;
			}

		}
	}
	else if (facing == 0)
	{
		for (int i = 0; i < steps; i++)
		{

			if (map[y][x + 1] == '.')
			{
				x+= 1;
			}
			else
			{
				if (map[y][x+1] == ' ')
				{
					int nX = x-1;
					while (map[y][nX] != ' ')
					{
						nX -= 1;
					}
					if (map[y][nX+1] == '.')
					{
						x = nX+1;
						continue;
					}
				}
				break;
			}

		}
	}
	else if (facing == 2)
	{
		for (int i = 0; i < steps; i++)
		{

			if (map[y][x-1] == '.')
			{
				x -= 1;
			}
			else
			{
				if (map[y][x-1] == ' ')
				{
					int nX = x+1;
					while (map[y][nX] != ' ')
					{
						nX += 1;
					}
					if (map[y][nX-1] == '.')
					{
						x = nX-1;
						continue;
					}
				}
				break;
			}

		}
	}
	return make_pair(y, x);
}


void Day22()
{
	myFile in = myFile();
	in.Open("Days/Day22/in.txt");
	in.ReadFile();


	vector<vector<char>> map;
	int longest = 0;
	for (int i = 0; i < in.nol - 2; i++)
	{
		if (longest < in.inputLines[i].size())
		{
			longest = in.inputLines[i].size();
		}
	}
	vector<char> a;
	for (int i = 0; i < longest+2; i++)
	{
		a.push_back(' ');
	}
	//map.push_back(a);
	for (int i = 0; i < in.nol-2; i++)
	{
		vector<char> line;
		
		for (char a : in.inputLines[i])
		{
			line.push_back(a);
		}
		while (line.size() < longest)
		{
			line.push_back(' ');
		}
		//line.insert(line.begin(),' ');
		//line.push_back(' ');
		map.push_back(line);
	}
	//map.push_back(a);
	
	vector<Side*> cubeSides;
	
	for(int i = 0;i<12;i++)
	{
	
		//cout << (i / 3) * 50 << " " << (i % 3) * 50 << " ";
		if (map[(i / 3) * 50][(i%3)*50] != ' ')
		{
			//cout << "wee\n";
			vector<vector<char>> mapToAdd;
			for (int j = 0; j < 50; j++)
			{
				vector<char> line;
				for (int k = 0; k < 50; k++)
				{
					//cout << (((i + 1) / 3) * 50) + j<<" "<<((i % 3) * 50) + k<<" ";
					line.push_back(map[((i / 3) * 50) + j][((i % 3) * 50) + k]);
				}
				//cout << "\n";
				mapToAdd.push_back(line);
			}
			Side* a = new Side();
			a->id = cubeSides.size() + 1;
			a->giveMap(mapToAdd);
			cubeSides.push_back(a);
		}
	}
	
	for (Side* a : cubeSides)
	{
	//	a->printSide();
		//cout << a->id << "\n";
	}
	

	//hardcodnig part xd

	//side 1
	cubeSides[0]->Right = cubeSides[1];
	cubeSides[0]->Left = cubeSides[3];
	cubeSides[0]->Down = cubeSides[2];
	cubeSides[0]->Up = cubeSides[5];
	cubeSides[0]->faceChanging[0] = 0;
	cubeSides[0]->faceChanging[1] = 0;
	cubeSides[0]->faceChanging[2] = 2;
	cubeSides[0]->faceChanging[3] = 1;

	//side 2
	cubeSides[1]->Right = cubeSides[4];
	cubeSides[1]->Left = cubeSides[0];
	cubeSides[1]->Down = cubeSides[2];
	cubeSides[1]->Up = cubeSides[5];
	cubeSides[1]->faceChanging[0] = 2;
	cubeSides[1]->faceChanging[1] = 1;
	cubeSides[1]->faceChanging[2] = 0;
	cubeSides[1]->faceChanging[3] = 0;

	//side 3
	cubeSides[2]->Right = cubeSides[1];
	cubeSides[2]->Left = cubeSides[3];
	cubeSides[2]->Down = cubeSides[4];
	cubeSides[2]->Up = cubeSides[0];
	cubeSides[2]->faceChanging[0] = 3;
	cubeSides[2]->faceChanging[1] = 0;
	cubeSides[2]->faceChanging[2] = 3;
	cubeSides[2]->faceChanging[3] = 0;

	//side 4
	cubeSides[3]->Right = cubeSides[4];
	cubeSides[3]->Left = cubeSides[0];
	cubeSides[3]->Down = cubeSides[5];
	cubeSides[3]->Up = cubeSides[2];
	cubeSides[3]->faceChanging[0] = 0;
	cubeSides[3]->faceChanging[1] = 0;
	cubeSides[3]->faceChanging[2] = 2;
	cubeSides[3]->faceChanging[3] = 1;

	//side 5
	cubeSides[4]->Right = cubeSides[1];
	cubeSides[4]->Left = cubeSides[3];
	cubeSides[4]->Down = cubeSides[5];
	cubeSides[4]->Up = cubeSides[2];
	cubeSides[4]->faceChanging[0] = 2;
	cubeSides[4]->faceChanging[1] = 1;
	cubeSides[4]->faceChanging[2] = 0;
	cubeSides[4]->faceChanging[3] = 0;

	//side 6
	cubeSides[5]->Right = cubeSides[4];
	cubeSides[5]->Left = cubeSides[0];
	cubeSides[5]->Down = cubeSides[1];
	cubeSides[5]->Up = cubeSides[3];
	cubeSides[5]->faceChanging[0] = 3;
	cubeSides[5]->faceChanging[1] = 0;
	cubeSides[5]->faceChanging[2] = 3;
	cubeSides[5]->faceChanging[3] = 0;


	string stepInput = "";
	for (char a : in.inputLines[in.nol - 1])
	{
		if (a == 'L' || a == 'R')
		{
			stepInput += " ";
			stepInput += a;
			stepInput += " ";
		}
		else
		{
			stepInput += a;
		}
	}
	vector<string> instructions = split(stepInput,' ');

	
	int start = 0;
	for (int i = 0; i < map[1].size(); i++)
	{
		if (map[1][i] == '.')
		{
			start = i;
			break;
		}
	}

	pair<int, int> pos = make_pair(1, 1);
	//  0 - right, 1 - down, 2 - left, 3 - top
	Side currSide = *cubeSides[0];
	int facing = 0;
	for (int i = 0; i < instructions.size(); i += 2)
	{
		bool hittedWall = false;
		cout << facing << "\n";
		for (int j = 0; j < stoi(instructions[i]); j++)
		{
			pos = MakeMoveOnSide(pos, &facing, currSide, &hittedWall);
			if (hittedWall) break;
		}
		if(i+1<instructions.size())facing += instructions[i + 1] == "R" ? 1 : -1;
		if (facing <= -1) facing += 4;
		if (facing >= 4) facing -= 4;
	
	}
	cout << pos.first <<" "<< pos.second<<" "<<currSide.id<<" "<<facing;
}