#include "../Utility/SupportFunc.h"
#include "Day13.h"





void analyzeStruck(string list,string *order,vector<string> *strs,vector<string> *brcs)
{
	vector<string> str;
	vector<string> brc;
	if (list.size() == 2)
	{
		*order += "E";
	}
	int LBcount = 0;
	string element = "";
	string nBrac;
	for (int i = 1; i < list.size() - 1; i++)
	{
		if (list[i] == '[')
		{
			*order += "B";
			string inside = "";
			inside += list[i];
			LBcount = 1;
			while (LBcount)
			{
				i++;
				if (list[i] == '[')LBcount += 1;
				if (list[i] == ']')LBcount -= 1;
				inside += list[i];

			}
			i++;
			nBrac = inside;
			brc.push_back(nBrac);
		}
		else if (list[i] == ',')
		{
			if (element != "")
			{
				*order += "S";
				str.push_back(element);
				element = "";
			}
		}
		else
		{
			element += list[i];
		}
	}
	if (element != "")
	{
		*order += "S";
		str.push_back(element);
		element = "";
	}
	*brcs = brc;
	*strs = str;

}
//0-left 1 -same 2-right

int ComparePackets(string list1, string list2)
{
	string order1 = "", order2 = "";
	vector<string> strs1, strs2;
	vector<string> brcs1, brcs2;
	analyzeStruck(list1, &order1, &strs1, &brcs1);
	analyzeStruck(list2, &order2, &strs2, &brcs2);

	int shortest = -1;
	int minOrder = order1.size();

	if (minOrder > order2.size())
	{
		minOrder = order2.size();
		shortest = 1;
	}


	int strpoint1 = 0, brcspoint1 = 0,
		strpoint2 = 0, brcspoint2 = 0;

	for (int j = 0; j < minOrder; j++)
	{
		if (order1[j] == 'S'&&order2[j] == 'S')
		{
			int diff = stoi(strs1[strpoint1]) - stoi(strs2[strpoint2]);
			if (diff != 0)
			{
				if (diff < 0)return -1;
				return 1;
			}
			strpoint1++;
			strpoint2++;
		}
		else if (order1[j] == 'B' && order2[j] == 'S')
		{
			string asList = "[";
			asList += strs2[strpoint2];
			asList += "]";
			int diff = ComparePackets(brcs1[brcspoint1], asList);
			if (diff != 0)
			{
				if (diff < 0)return -1;
				return 1;
			}
			brcspoint1++;
			strpoint2++;
		}
		else if (order1[j] == 'S' && order2[j] == 'B')
		{
			string asList = "[";
			asList += strs1[strpoint1];
			asList += "]";
			int diff = ComparePackets(asList, brcs2[brcspoint2]);
			if (diff != 0)
			{
				if (diff < 0)return -1;
				return 1;
			}
			brcspoint2++;
			strpoint1++;
		}
		else if (order1[j] == 'B' && order2[j] == 'B')
		{
			int diff = ComparePackets(brcs1[brcspoint1], brcs2[brcspoint2]);
			if (diff != 0)
			{
				if (diff < 0)return -1;
				return 1;
			}
			brcspoint1++;
			brcspoint2++;
		}
		else if (order1[j] == 'E'&& order2[j]!='E')
		{
			return -1;
		}
		else if (order1[j] != 'E' && order2[j] == 'E')
		{
			return 1;
		}
	}

	return order1.size()!=order2.size()?shortest:0;
}

bool compare(string list1, string list2)
{
	return ComparePackets(list1, list2) == -1;
}

void Day13()
{
	myFile in = myFile();
	in.Open("Day13/in.txt");
	in.ReadFile();

	vector<string> Packets;

	int sum = 0, sum2 = 1;
	int pairIndex = 1;
	for (int i = 0; i < in.nol; i+=3)
	{
		Packets.push_back(in.inputLines[i]);
		Packets.push_back(in.inputLines[i+1]);
		if (ComparePackets(in.inputLines[i], in.inputLines[i + 1]) == -1)
		{
			sum += pairIndex;
		}
		pairIndex++;
	}
	Packets.push_back("[[2]]");
	Packets.push_back("[[6]]");

	sort(Packets.begin(),Packets.end(), compare);
	for (int i = 0; i < Packets.size(); i++)
	{
		if (Packets[i] == "[[2]]" || Packets[i] == "[[6]]")
		{
			sum2 *= i + 1;
		}
	}
	cout << sum<<" "<<sum2;

}