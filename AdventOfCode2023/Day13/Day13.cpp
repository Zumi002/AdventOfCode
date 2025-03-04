#include "../Utility/SupportFunc.h"
#include "Day13.h"


vector<vector<int>> PointsOfIntrest(vector<string> &pat,int skipX,int skipY)
{
	vector<vector<int>> points(2);
	for (int j = 0; j < pat[0].size() - 1; j++)
	{
		if (pat[0][j] == pat[0][j + 1]&&j!=skipX)points[0].push_back(j);
	}
	for (int i = 1; i < pat.size(); i++)
	{
		vector<int> left;
		for (int a : points[0])
		{
			if (pat[i][a] == pat[i][a + 1])left.push_back(a);
		}
		points[0] = left;
	}
	for (int j = 0; j < pat.size() - 1; j++)
	{
		if (pat[j][0] == pat[j+1][0]&&j!=skipY)points[1].push_back(j);
	}
	for (int i = 1; i < pat[0].size(); i++)
	{
		vector<int> left;
		for (int a : points[1])
		{
			if (pat[a][i] == pat[a+1][i])left.push_back(a);
		}
		points[1] = left;
	}
	return points;
}

pair<int, int> decide(vector<vector<int>> &points, vector<string>& pat)
{
	pair<int, int> res = {-1,-1};
	int x = pat[0].size(), y = pat.size();
	for (int i = 0; i < points[0].size(); i++)
	{
		int point = points[0][i];
		int far = 0;
		bool ok = true;
		while (ok)
		{
			far++;
			if (far + point + 1 >= x||point-far<0)return { point,-1 };
			for (int j = 0; j < pat.size(); j++)
			{
				if (pat[j][point - far] != pat[j][point + far + 1])
				{
					ok = false;
					break;
				}
			}
		}
	}
	for (int i = 0; i < points[1].size(); i++)
	{
		int point = points[1][i];
		int far = 0;
		bool ok = true;
		while (ok)
		{
			far++;
			if (far + point + 1 >= y || point - far < 0)return { -1,point };
			for (int j = 0; j < pat[0].size(); j++)
			{
				if (pat[point-far][j] != pat[point+far+1][j])
				{
					ok = false;
					break;
				}
			}
		}
	}
	return res;
}

int analyze(vector<string>& pat,int skipX=-1,int skipY=-1)
{
	vector<vector<int>>points = PointsOfIntrest(pat,skipX,skipY);
	pair<int, int> w = decide(points,pat);
	if (w.first != -1)
	{
		return w.first + 1;
	}
	return (w.second + 1) * 100;
}

int analyzeP2(vector<string>& pat)
{
	vector<vector<int>>points = PointsOfIntrest(pat, -1, -1);
	pair<int, int> w = decide(points, pat);
	int skipX = -1, skipY = -1;
	if (w.first!=-1)skipX = w.first;
	else skipY = w.second;
	for (int i = 0; i < pat.size(); i++)
	{
		for (int j = 0; j < pat[0].size(); j++)
		{
			pat[i][j] = (pat[i][j] == '#' ? '.' : '#');
			int k = analyze(pat, skipX, skipY);
			if (k> 0)
			{
				//cout << i << " " << j << "\n";
				pat[i][j] = (pat[i][j] == '#' ? '.' : '#');
				return k;
			}
			pat[i][j] = (pat[i][j] == '#' ? '.' : '#');
		}
	}
	return -1;
}


void Day13()
{
	myFile in = myFile();
	in.Open("Day13/in.txt");
	in.ReadFile();

	vector<vector<string>> patterns;
	vector<string>tmp;
	for (int i = 0; i < in.nol; i++)
	{
		if (in.inputLines[i].size() > 0)
		{
			tmp.push_back(in.inputLines[i]);
		}
		else if (tmp.size()>0)
		{
			patterns.push_back(tmp);
			tmp.clear();
		}
	}
	patterns.push_back(tmp);
	int sum = 0,sum2 = 0;
	for (int i =0;i<patterns.size();i++)
	{
		sum +=  analyze(patterns[i]);
		sum2 += analyzeP2(patterns[i]);
	}
	cout << sum<<" "<<sum2;

}