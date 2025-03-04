#include "../Utility/SupportFunc.h"
#include "Day13.h"


struct claw
{
	long long ax, ay;
	long long bx, by;

	long long px, py;

	claw(long long aX, long long aY, long long bX, long long bY, long long pX, long long pY)
	{
		ax = aX;
		ay = aY;
		bx = bX;
		by = bY;
		px = pX;
		py = pY;
	}

	long long TryCatch()
	{
		long long msc = LLONG_MAX;
		//hoping a and b are not colinear
		long long b = (long long)by * (long long)ax - (long long)ay * (long long)bx;
		long long c = (long long)py * (long long)ax - (long long)ay * (long long)px;
		if (c % b == 0)
		{
			if (c / b > 0&& ((px - bx * (c / b)) / ax) >0)
			{
				return c / b + ((px - bx * (c / b)) / ax) * 3;
			}

			return msc;
		}
		return msc;
	}
};


void Day13()
{
	myFile in = myFile();
	in.Open("Day13/in.txt");
	in.ReadFile();

	long long sum = 0;
	
	for (int i = 0; i < in.nol; i += 4)
	{
		int ax = stoi(in.inputWords[i][2].substr(2,2));
		int ay = stoi(in.inputWords[i][3].substr(2, 2));
		int bx = stoi(in.inputWords[i+1][2].substr(2, 2));
		int by = stoi(in.inputWords[i+1][3].substr(2, 2));
		int px = 0;
		for (int j = 2; j < in.inputWords[i + 2][1].size(); j++)
		{
			if(in.inputWords[i+2][1][j]==',')
				px = stoi(in.inputWords[i + 2][1].substr(2, j-2));
		}
		int py = stoi(in.inputWords[i + 2][2].substr(2));
		claw c = claw(ax, ay, bx, by, 10000000000000+ (long long)px, 10000000000000+ (long long)py);

		long long t = c.TryCatch();
		if (t != LLONG_MAX)
		{
			sum += t;
		}
	}

	cout << sum;

}