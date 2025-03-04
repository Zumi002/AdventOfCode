#include "../../Utility/SupportFunc.h"
#include "Day9.h"
#include <set>
#include <utility>
#include <Stack>


void Day9()
{
	myFile in = myFile();
	in.Open("Days/Day9/in.txt");
	in.ReadFile();
	vector<int> nextValue;
	vector<int> prevValue;
	for (int i = 0; i < in.nol; i++)
	{
		vector<int> sequence(in.now[i]);
		for (int j = 0; j < in.now[i]; j++)
		{
			sequence[j] =(atoi(in.inputWords[i][j].c_str()));
		}
		stack<int> onFirst;
		bool zeros = false;
		int l = in.now[i];
		while (!zeros)
		{
			zeros = true;
			onFirst.push(sequence[0]);
			for (int j = 0; j <l-1; j++)
			{
				sequence[j] = sequence[j + 1] - sequence[j];
				if (zeros&&sequence[j] != 0)zeros = false;
			}
			l--;
		}
		int hist = 0;
		for (int j = l;j<in.now[i];j++)
		{
			hist += sequence[j];
		}
		int hist2 = 0;
		while (onFirst.size())
		{
			hist2 = onFirst.top() - hist2;
			onFirst.pop();
		}
		nextValue.push_back(hist);
		prevValue.push_back(hist2);
	}

	int sum = 0;
	int sum2 = 0;
	for (int a : nextValue)
	{
		sum += a;
	}
	for (int a : prevValue)
	{
		sum2 += a;
	}
	cout << sum<<"\n"<<sum2;
}