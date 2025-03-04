#include "../../Utility/SupportFunc.h"
#include "Day15.h"
#include <set>
#include <math.h>

void Day15()
{
	myFile in = myFile();
	in.Open("Days/Day15/in.txt");
	in.ReadFile();


	int sum = 0, sum2 = 0;

	set<pair<int, int>> Bekons;
	vector<pair<int, int>> Sensors;
	vector<int> Radius;

	for (int i = 0; i < in.nol; i++)
	{
		int sensorX = stoi(split(split(in.inputWords[i][2], '=')[1], ',')[0]);
		int sensorY = stoi(split(split(in.inputWords[i][3], '=')[1], ':')[0]);
		int BX = stoi(split(split(in.inputWords[i][8], '=')[1], ',')[0]);
		int BY = stoi(split(in.inputWords[i][9], '=')[1]);
		Radius.push_back(abs(sensorX - BX) + abs(sensorY - BY));
		cout << Radius[i] << "\n";
		Sensors.push_back(make_pair(sensorX, sensorY));
		Bekons.insert(make_pair(BX, BY));
	}
	
	int x, y;
	int dist;
	int rad;
	int lastsum = 0;
	for (int i = 0; i <= 4000000; i++)
	{
		vector<pair<int, int>> Ranges;
		for (int j = 0; j < Sensors.size(); j++)
		{
			x = Sensors[j].first;
			y = Sensors[j].second;
			dist = abs(Sensors[j].second - i);
			rad = Radius[j] - dist;
			if (rad >= 0)
			{
				Ranges.push_back(make_pair(x - rad > 0 ? x - rad : 0, x + rad + 1 < 4000000 ? x + rad + 1 : 4000000));
			}
		}
		sort(Ranges.begin(), Ranges.end());
		pair<int, int> trueRanges[2];
		trueRanges[0]= Ranges[0];
		int j = 0;
		for (int k = 1; k < Ranges.size(); k++)
		{
			if (Ranges[k].first <= trueRanges[j].second)
			{
				trueRanges[j].second = trueRanges[j].second > Ranges[k].second ? trueRanges[j].second : Ranges[k].second;
			}
			else 
			{
				j++;
				trueRanges[1]=Ranges[k];
			}

		}
		
		sum = 0;
		for (pair<int, int> a : trueRanges)
		{
			sum += a.second - a.first;
		}
		if(lastsum==0)lastsum = sum;
		if (sum != lastsum)
		{
			cout << i<< " wtf " << sum<<"\n";
			for (pair<int, int> a : trueRanges)
			{
				cout<< a.first<<" " << a.second<<"\n";
			}
			cin >> sum;
		}
	}


	

	cout << sum;
}