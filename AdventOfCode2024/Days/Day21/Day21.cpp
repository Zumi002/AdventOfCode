#include "../../Utility/SupportFunc.h"
#include "Day21.h"
#include <map>
#include <unordered_map>
#include <stack>

class robot
{
public:

	vector<pair<int, int>> positions = { {3,1},{2,0},{2,1},{2,2},{1,0},{1,1},{1,2},{0,0},{0,1},{0,2},{3,2} };
	unordered_map<char, int> dirToNum = { pair<char,int>{'<',0},{'>',1},{'^',2},{'v',3},{'A',4}};
	vector<pair<int, int>> positionsDir = { {1,0},{1,2},{0,1},{1,1},{0,2} };
	vector<string> typeOnNumerical(string& code, int offsetCode, int x, int y, vector<string>& add, string& codeNow, int lastmoveHV, int changes)
	{
		if ((x == 0 && y == 3)||changes>2||add.size())//panic
			return add;
		int wh = code[offsetCode] - '0' < 10 ? code[offsetCode] -'0' : 10;
		pair<int, int> posToGo = positions[wh];

		
		
		if (x > posToGo.second)
		{
			codeNow += '<';
			typeOnNumerical(code, offsetCode, x - 1, y, add, codeNow, 0, changes + (lastmoveHV != 0));
			codeNow.pop_back();
		}
		if (y > posToGo.first)
		{
			codeNow += '^';
			typeOnNumerical(code, offsetCode, x, y - 1, add, codeNow, 1, changes + (lastmoveHV != 1));
			codeNow.pop_back();
		}
		if (y < posToGo.first)
		{
			codeNow += 'v';
			typeOnNumerical(code, offsetCode, x, y + 1, add, codeNow, 1, changes + (lastmoveHV != 1));
			codeNow.pop_back();
		}
		if (x < posToGo.second)
		{
			codeNow += '>';
			typeOnNumerical(code, offsetCode, x + 1, y, add, codeNow, 0, changes + (lastmoveHV != 0));
			codeNow.pop_back();
		}
		if (x == posToGo.second && y == posToGo.first)
		{
			codeNow += 'A';
			offsetCode++;
			if (offsetCode >= code.size())
			{
				add.push_back(string(codeNow));
				codeNow.pop_back();
				return add;
			}
			else
			{
				typeOnNumerical(code, offsetCode, x, y, add, codeNow,-1,0);
				codeNow.pop_back();
			}
		}
		return add;
	}

	vector<string> typeOnDirectional(string& code, int offsetCode, int x, int y, vector<string>& add, string& codeNow, int lastmoveHV, int changes)
	{
		if ((x == 0 && y == 0)||changes>2||add.size())//panic
			return add;
		int wh = dirToNum[code[offsetCode]];
		pair<int, int> posToGo = positionsDir[wh];

		
		
		if (x > posToGo.second)
		{
			codeNow += '<';
			typeOnDirectional(code, offsetCode, x - 1, y, add, codeNow, 0, changes + (lastmoveHV != 0));
			codeNow.pop_back();
		}
		
		if (y > posToGo.first)
		{
			codeNow += '^';
			typeOnDirectional(code, offsetCode, x, y - 1, add, codeNow, 1, changes + (lastmoveHV != 1));
			codeNow.pop_back();
		}
		if (y < posToGo.first)
		{
			codeNow += 'v';
			typeOnDirectional(code, offsetCode, x, y + 1, add, codeNow, 1, changes + (lastmoveHV != 1));
			codeNow.pop_back();
		}
		if (x < posToGo.second)
		{
			codeNow += '>';
			typeOnDirectional(code, offsetCode, x + 1, y, add, codeNow, 0, changes + (lastmoveHV != 0));
			codeNow.pop_back();
		}
		if (x == posToGo.second && y == posToGo.first)
		{
			codeNow += 'A';
			offsetCode++;
			if (offsetCode >= code.size())
			{
				add.push_back(string(codeNow));
				codeNow.pop_back();
				return add;
			}
			else
			{
				typeOnDirectional(code, offsetCode, x, y, add, codeNow,-1,0);
				codeNow.pop_back();
			}
		}
		return add;
	}
};



void Day21()
{
	myFile in = myFile();
	in.Open("Days/Day21/in.txt");
	in.ReadFile();

	long long  sum = 0, sum2 = 0;
	vector<unordered_map<string, long long>> fastCalc(27);
	unordered_map<string, string> fastDir;
	for (int i = 0; i < in.nol; i++)
	{
		robot r = robot();
		vector<string> strs, strs2, strs3;
		string codenow = "", cdn2 = "", cdn3 = "";
		string code = in.inputLines[i];
		long long shortest = 0;
		r.typeOnNumerical(code, 0, 2, 3, strs, codenow, -1, 0);
		stack<pair<string, pair<long long, pair<long long,long long>>>> st;
		st.push({ strs[0],{0,{0,0}} });
		
		while(st.size())
		{
			auto p = st.top();
			st.pop();
			string s = p.first;
			strs.clear();
			codenow = "";
			long long first = p.second.first;
			if (first != 0)
			{
				if (shortest - p.second.second.first<=0)
					cout << "";
				fastCalc[st.size()][s.substr(p.second.second.second, first - p.second.second.second)] = shortest - p.second.second.first;
			}
			if (first == s.size())
			{

				if (shortest - p.second.second.first <= 0)
					cout << "";
				fastCalc[st.size()][s.substr(p.second.second.second, first - p.second.second.second)] = shortest - p.second.second.first;
				continue;
			}
			if (st.size() == 25)
			{
				shortest += s.size();
				continue;
			}
			for (long long j = first; j < s.size(); j++)
			{
				if (s[j] == 'A')
				{
					string s2 = s.substr(first, j - first + 1);
					if (fastCalc[st.size()].count(s2))
					{
						//if(st.size()<5)
						//	cout << "Cache lvl" << st.size() << "\n";

						st.push({ s,{j + 1,{shortest,first}} });
						shortest += fastCalc[st.size()-1][s2];
						
						break;
					}
					else
					{
						st.push({ s,{j + 1,{shortest,first}} });
						if (fastDir.count(s2))
						{
							st.push({ fastDir[s2],{0,{shortest,0}} });
						}
						else
						{
							r.typeOnDirectional(s2, 0, 2, 0, strs, codenow, -1, 0);
							fastDir[s2] = strs[0];
							st.push({ strs[0],{0,{shortest,0}} });
						}
						
						
						
						break;
					}
				}
			}

			
		}
		
		cout << shortest << " " << stoi(in.inputLines[i].substr(0, in.inputLines[i].size() - 1))<<"\n";
		sum += shortest * stoi(in.inputLines[i].substr(0,in.inputLines[i].size()-1));
	}


	

	cout << sum;
}