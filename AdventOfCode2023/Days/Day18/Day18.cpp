#include "../../Utility/SupportFunc.h"
#include "Day18.h"
#include <tuple>
#include <set>
#include <queue>

vector<vector<int>> dir = { {-1,0},{0,1},{1,0},{0,-1} };

void Day18()
{
	myFile in = myFile();
	in.Open("Days/Day18/in.txt");
	in.ReadFile();
	long long maxX=0, minX=0, maxY=0, minY=0;
	long long x = 0, y = 0;
	for (int i = 0; i < in.nol; i++)
	{
		if (in.inputWords[i][2][7] == '0')
		{
			x += strtoll(in.inputWords[i][2].substr(2,5).c_str(),NULL,16);
	
			maxX = max(maxX, x);
		}
		else if (in.inputWords[i][2][7] == '1')
		{
			y += strtoll(in.inputWords[i][2].substr(2,5).c_str(), NULL, 16);
			maxY = max(maxY, y);
		}
		else if (in.inputWords[i][2][7] == '2')
		{
			x -= strtoll(in.inputWords[i][2].substr(2,5).c_str(), NULL, 16);
			minX = min(minX, x);
		}
		else if (in.inputWords[i][2][7] == '3')
		{
			y -= strtoll(in.inputWords[i][2].substr(2,5).c_str(), NULL, 16);
			minY = min(minY, y);
		}
	}
	long long xoff = -minX;
	long long yoff = -minY;
	x = xoff + 1;
	y = yoff + 1;
	//cout << x << " " << y;
	long long sum = 0;
	long long perim = 0;
	for (int i = 0; i < in.nol; i++)
	{
		long long k = strtoll(in.inputWords[i][2].substr(2,5).c_str(), NULL, 16);
		if (in.inputWords[i][2][7] == '0')
		{
			sum += (x * y) - ((x + k) * (y));
			x += k;
		}
		else if (in.inputWords[i][2][7] == '1')
		{
			sum += (x * (y+k)) - ((x) * (y));
			y += k;
		}
		else if (in.inputWords[i][2][7] == '2')
		{
			sum += (x * y) - ((x - k) * (y));
			x -= k;
		}
		else if (in.inputWords[i][2][7] == '3')
		{
			sum += (x * (y - k)) - ((x) * (y));
			y -= k;
		}
		perim += k;
	}
	cout << sum / 2+perim/2+1;
}