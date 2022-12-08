#include "../Utility/SupportFunc.h"
#include "Day8.h"
#include <utility>
#include <set>


void Day8()
{
	myFile in = myFile();
	in.Open("Day8/in.txt");
	in.ReadFile();

	//part1
	set<pair<int, int>> visible;

	
	int maxX = in.inputLines[0].size(),
		maxY = in.nol;
	//horizontal
	for (int row = 1; row <maxY-1; row++)
	{
		int maxLeftTree = -1,maxRightTree = -1;
		for (int collumn = 0; collumn < maxX; collumn++)
		{
			int leftTreeSize  = in.inputLines[row][collumn] % '0',
			    rightTreeSize = in.inputLines[row][maxX-collumn-1] % '0';
			if (leftTreeSize > maxLeftTree)
			{
				visible.insert(make_pair(row, collumn));
				maxLeftTree = leftTreeSize;
			}
			if (rightTreeSize > maxRightTree)
			{
				visible.insert(make_pair(row, maxX - collumn - 1));
				maxRightTree = rightTreeSize;
			}
		}
	}
	//vertical, but without
	for (int collumn = 1; collumn < maxX-1; collumn++)
	{
		int maxUpTree = -1, maxDownTree = -1;
		for (int row = 0; row < maxY; row++)
		{
			int upTreeSize = in.inputLines[row][collumn] % '0',
				downTreeSize = in.inputLines[maxY-row-1][collumn] % '0';
			if (upTreeSize > maxUpTree)
			{
				visible.insert(make_pair(row, collumn));
				maxUpTree = upTreeSize;
			}
			if (downTreeSize > maxDownTree)
			{
				visible.insert(make_pair(maxY - row - 1, collumn));
				maxDownTree = downTreeSize;
			}
		}
	}

	//part2
	int maxScore = 0;
	for (int row = 1; row < maxY - 1; row++)
	{
		for (int collumn = 1; collumn < maxX - 1; collumn++)
		{
			int score[4] = {};
			int myTreeSize = in.inputLines[row][collumn]%'0';
			//check every direction
			for (int left = collumn - 1; left >= 0; left--)
			{
				score[0] += 1;
				if (in.inputLines[row][left] % '0' >= myTreeSize)
				{
					break;
				}
			}
			for (int right = collumn + 1; right < maxX; right++)
			{
				score[1] += 1;
				if (in.inputLines[row][right] % '0' >= myTreeSize)
				{
					break;
				}
			}
			for (int up = row - 1; up >= 0; up--)
			{
				score[2] += 1;
				if (in.inputLines[up][collumn] % '0' >= myTreeSize)
				{
					break;
				}
			}
			for (int down = row + 1; down < maxY; down++)
			{
				score[3] += 1;
				if(in.inputLines[down][collumn] % '0' >= myTreeSize)
				{
					break;
				}
			}
			if (score[0] * score[1] * score[2] * score[3] >= maxScore) maxScore = score[0] * score[1] * score[2] * score[3];
		}
	}

	cout << visible.size() +4 << " "<<maxScore;
}