#include "../../Utility/SupportFunc.h"
#include "Day17.h"

//coordinates form y x

class Rock 
{
public:
	bool collider[4][4];
	int simpleColX = 0, simpleColY = 0;
	int y, x;
	bool OnGround = false;

	Rock(int type,int tx ,int ty)
	{
		x = tx;
		y = ty;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				collider[i][j] = false;
			}
		}
		switch (type)
		{
			case 1:
			{
				collider[0][0] = true;
				collider[0][1] = true;
				collider[0][2] = true;
				collider[0][3] = true;
				simpleColX = 3;
				break;
			}
			case 2:
			{
				collider[0][1] = true;
				collider[1][0] = true;
				collider[1][1] = true;
				collider[1][2] = true;
				collider[2][1] = true;
				simpleColX = 2;
				simpleColY = 2;
				break;
			}
			case 3:
			{
				collider[0][0] = true;
				collider[0][1] = true;
				collider[0][2] = true;
				collider[1][2] = true;
				collider[2][2] = true;
				simpleColX = 2;
				simpleColY = 2;
				break;
			}
			case 4:
			{
				collider[0][0] = true;
				collider[1][0] = true;
				collider[2][0] = true;
				collider[3][0] = true;
				simpleColY = 3;
				break;
			}
			case 5:
			{
				collider[0][0] = true;
				collider[0][1] = true;
				collider[1][0] = true;
				collider[1][1] = true;
				simpleColX = 1;
				simpleColY = 1;
				break;
			}
		}
	}

	vector<pair<int, int>> myColliders()
	{
		vector<pair<int, int>> res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (collider[i][j]) res.push_back(make_pair(y+i, x+j));
			}
		}
		return res;
	}

	bool Move(char jet, vector<vector<bool>> &chamber)
	{
		if (jet == '<')
		{
			if (x == 0)
			{
				//nothing
			}
			else
			{
				vector<pair<int, int>> colliders = myColliders();
				bool bad = false;
				for (pair<int, int> a : colliders)
				{
					if (chamber[a.first][a.second - 1]) bad = true;
				}
				if (!bad)
				{
					x -= 1;
				}
			}
		}
		if (jet == '>')
		{
			if (x + simpleColX == 6)
			{
				//nothing
			}
			else
			{
				vector<pair<int, int>> colliders = myColliders();
				bool bad = false;
				for (pair<int, int> a : colliders)
				{
					if (chamber[a.first][a.second + 1])
					{
						bad = true;
					}
				}
				if (!bad)
				{
					x += 1;
				}
			}
		}
		if (y == 0)
		{
			return false;
		}
		else
		{
			vector<pair<int, int>> colliders = myColliders();
			bool bad = false;
			for (pair<int, int> a : colliders)
			{
				if (chamber[a.first - 1][a.second])
				{
					bad = true;
				}
			}
			if (!bad)
			{
				y -= 1;
				return true;
			}
			return false;
		}
	}
};


void Day17()
{
	myFile in = myFile();
	in.Open("Days/Day17/in.txt");
	in.ReadFile();


	int sum = 0;
	vector<vector<bool>> chamber;
	int chamberTop = 0;
	string airJests;
	int airSize;

	airJests = in.inputLines[0];
	airSize = airJests.size();
	
	string moves = "";

	
	long long big = 1000000000000;
	long long first = 0;
	long long cycle = 0;
	long long cycletimes = 0;
	long long rest = 0;

	int currentJet = 0;

	for (int i = 0; i < 2000; i++)
	{
		Rock a(ClampS(i+1, 5), 2, chamberTop + 3);

		//expand chamber if needed
		for (int j = chamber.size(); j < chamberTop + 4 + a.simpleColY; j++)
		{
			vector<bool> row;
			row.push_back(false);
			row.push_back(false);
			row.push_back(false);
			row.push_back(false);
			row.push_back(false);
			row.push_back(false);
			row.push_back(false);
			chamber.push_back(row);
		}
		while (a.Move(airJests[ClampS(currentJet+1,airSize)-1], chamber))
		{
			currentJet += 1;
		}
		currentJet += 1;
		
		
		chamberTop = a.y + a.simpleColY + 1>chamberTop? a.y + a.simpleColY + 1:chamberTop;
		moves += char (a.x+48);
		vector<pair<int, int>> toPlace = a.myColliders();

		for (pair<int, int> a : toPlace)
		{
			chamber[a.first][a.second] = true;
		}
	}
	//25 repeating blocks positions should be sufficient for finding pattern, without clear pattern chance is +- 7^25 
	for (int i = 0; i < 2000-25; i++)
	{
		for (int j = i + 1; j < 2000 - 25; j++)
		{
			if (moves.substr(i, 25) == moves.substr(j, 25))
			{
				cycle = j - i;
				first = i;
				break;
			}
		}
	}

	rest = (big - first) % cycle;
	cycletimes = (big - first) / cycle;
	std::cout << cycle << " " << first<<" "<<rest<<"\n";
	chamber.clear();
	chamberTop = 0;

	for (int i = 0; i < first; i++)
	{
		Rock a(ClampS(i + 1, 5), 2, chamberTop + 3);

		//expand chamber if needed
		for (int j = chamber.size(); j < chamberTop + 4 + a.simpleColY; j++)
		{
			vector<bool> row;
			for (int k = 0; k < 7; k++)row.push_back(false);
			chamber.push_back(row);
		}

		while (a.Move(airJests[ClampS(currentJet + 1, airSize) - 1], chamber))
		{
			currentJet += 1;
		}
		currentJet += 1;


		chamberTop = a.y + a.simpleColY + 1 > chamberTop ? a.y + a.simpleColY + 1 : chamberTop;
		moves += char(a.x + 48);
		vector<pair<int, int>> toPlace = a.myColliders();

		for (pair<int, int> a : toPlace)
		{
			chamber[a.first][a.second] = true;
		}

		//visuals
		//for (int j = chamber.size()-1; j >= 0; j--)
		//{
		//	cout << "|";
		//	for (int k = 0; k < 7; k++)
		//	{
		//		cout << (chamber[j][k] ? '#' : '.');
		//	}
		//	cout << "|\n";
		//}
		//cout << "---------\n\n";
	}
	int firstHeight = chamberTop;
	for (int i = 0; i < cycle; i++)
	{
		Rock a(ClampS(i + 1, 5), 2, chamberTop + 3);

		//expand chamber if needed
		for (int j = chamber.size(); j < chamberTop + 4 + a.simpleColY; j++)
		{
			vector<bool> row;
			for (int k = 0; k < 7; k++)row.push_back(false);
			chamber.push_back(row);
		}

		while (a.Move(airJests[ClampS(currentJet + 1, airSize) - 1], chamber))
		{
			currentJet += 1;
		}
		currentJet += 1;


		chamberTop = a.y + a.simpleColY + 1 > chamberTop ? a.y + a.simpleColY + 1 : chamberTop;
		moves += char(a.x + 48);
		vector<pair<int, int>> toPlace = a.myColliders();

		for (pair<int, int> a : toPlace)
		{
			chamber[a.first][a.second] = true;
		}

		//visuals
		//for (int j = chamber.size()-1; j >= 0; j--)
		//{
		//	cout << "|";
		//	for (int k = 0; k < 7; k++)
		//	{
		//		cout << (chamber[j][k] ? '#' : '.');
		//	}
		//	cout << "|\n";
		//}
		//cout << "---------\n\n";
	}
	int cycleHeight = chamberTop - firstHeight;
	for (int i = 0; i < rest; i++)
	{
		Rock a(ClampS(i + 1, 5), 2, chamberTop + 3);

		//expand chamber if needed
		for (int j = chamber.size(); j < chamberTop + 4 + a.simpleColY; j++)
		{
			vector<bool> row;
			for (int k = 0; k < 7; k++)row.push_back(false);
			chamber.push_back(row);
		}

		while (a.Move(airJests[ClampS(currentJet + 1, airSize) - 1], chamber))
		{
			currentJet += 1;
		}
		currentJet += 1;


		chamberTop = a.y + a.simpleColY + 1 > chamberTop ? a.y + a.simpleColY + 1 : chamberTop;
		moves += char(a.x + 48);
		vector<pair<int, int>> toPlace = a.myColliders();

		for (pair<int, int> a : toPlace)
		{
			chamber[a.first][a.second] = true;
		}

		//visuals
		//for (int j = chamber.size()-1; j >= 0; j--)
		//{
		//	cout << "|";
		//	for (int k = 0; k < 7; k++)
		//	{
		//		cout << (chamber[j][k] ? '#' : '.');
		//	}
		//	cout << "|\n";
		//}
		//cout << "---------\n\n";
	}
	int restHeight = chamberTop - cycleHeight - firstHeight;

	std::cout << firstHeight+cycletimes * cycleHeight+restHeight;

	
}