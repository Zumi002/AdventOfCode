#include "../Utility/SupportFunc.h"
#include "Day9.h"
#include <set>
#include <utility>



struct block
{
	static int _id;
	int len = 0;
	int id = 0;
	int start = 0;

	block(int iD,int Len, int s)
	{
		len = Len;
		id = iD;
		start = s;
	}
};


void Day9()
{
	myFile in = myFile();
	in.Open("Day9/in.txt");
	in.ReadFile();
    
	long long len = 0, blen = 0, sum = 0;
	vector<block> blocks, spaces;
	for (int i = 0; i < in.inputLines[0].size(); i++)
	{
		
		if (i % 2 == 0)
		{
			blocks.push_back(block(blocks.size(), in.inputLines[0][i] - '0',len));
			blen += in.inputLines[0][i] - '0';
		}
		else
		{
			spaces.push_back(block(-1, in.inputLines[0][i] - '0',len));
		}
		len += in.inputLines[0][i] - '0';
	}

	vector<int> ids(len);
	int k = 0;
	for (int i = 0;i<blocks.size();i++)
	{
		for (int j = 0; j < blocks[i].len; j++)
		{
			ids[k++] = blocks[i].id;
		}
		if (i < spaces.size())
		{
			for (int j = 0; j < spaces[i].len; j++)
			{
				ids[k++] = -1;
			}
		}
	}
	/*
	int end = ids.size()-1;
	for (int i = 0; i < blen; i++)
	{
		if (ids[i] != -1)
		{
			sum += (long long)i * ids[i];
		}
		else
		{
			while (ids[end] == -1)
			{
				end--;
			}
			sum += (long long)i * ids[end];
			end--;
		}
	}*/

	for (int j = blocks.size() - 1; j >= 0; j--)
	{
		int s = blocks[j].len;
		int st = 0;
		for (int k = 0; k < blocks[j].start; k++)
		{
			if (ids[k] == -1)
			{
				st++;
				if (st == s)
				{
					for (int w = k - st+1; w <= k; w++)
					{
						ids[w] = blocks[j].id;
					}
					for (int w = blocks[j].start; w < blocks[j].start + s; w++)
					{
						ids[w] = -1;
					}
					break;
				}
			}
			else
			{
				st = 0;
			}
		}
	}

	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] != -1)
		{
			sum += ids[i] * i;
		}
	}

	cout << sum;
}