#include "../../Utility/SupportFunc.h"
#include "Day17.h"


class computer
{
public:
	vector<long long> program;
	long long a;
	long long b;
	long long c;
	int ip;
	string out;
	string targOut;
	int targ;

	computer(long long A, long long B, long long C, vector<long long>& Program)
	{
		a = A;
		b = B;
		c = C;
		out = "";
		ip = 0;
		program = Program;
	}
	computer(long long A, long long B, long long C, vector<long long>& Program, string& targ)
	{
		a = A;
		b = B;
		c = C;
		out = "";
		ip = 0;
		program = Program;
		targOut = targ;
	}

	void Run()
	{
		while (ip + 1 < program.size())
		{
			switch (program[ip])
			{
			case 0:
				adv();
				break;
			case 1:
				bxl();
				break;
			case 2:
				bst();
				break;
			case 3:
				jnz();
				break;
			case 4:
				bxc();
				break;
			case 5:
				outy();
				break;
			case 6:
				bdv();
				break;
			case 7:
				cdv();
				break;
			}
		}
	}
	bool CheckRun()
	{
		while (ip + 1 < program.size())
		{
			switch (program[ip])
			{
			case 0:
				adv();
				break;
			case 1:
				bxl();
				break;
			case 2:
				bst();
				break;
			case 3:
				jnz();
				break;
			case 4:
				bxc();
				break;
			case 5:
				if (!outch())
					return false;
				break;
			case 6:
				bdv();
				break;
			case 7:
				cdv();
				break;
			}
		}
		return targ == (targOut.size() + 1);
	}

	long long combo(int op)
	{
		if (op <= 3)
			return op;
		if (op == 4)
			return a;
		if (op == 5)
			return b;
		return c;
	}

	void adv()
	{
		a = a >> combo(program[ip + 1]);
		ip += 2;
	}

	void bxl()
	{
		b ^= program[ip + 1];
		ip += 2;
	}

	void bst()
	{
		b = 7 & combo(program[ip + 1]);
		ip += 2;
	}

	void jnz()
	{
		if (a == 0)
		{
			ip += 2;
			return;
		}
		ip = program[ip + 1];
	}

	void bxc()
	{
		b ^= c;
		ip += 2;
	}

	void outy()
	{
		if (out.size() != 0)
		{
			out += ',';
		}
		out += to_string(combo(program[ip + 1]) & 7);
		ip += 2;
	}

	bool outch()
	{
		if (targ >= targOut.size())
			return false;
		if (targOut[targ] != ('0' + (combo(program[ip + 1]) & 7)))
			return false;
		ip += 2;
		targ += 2;

		return true;
	}

	void bdv()
	{

		b = a >> combo(program[ip + 1]);
		ip += 2;
	}

	void cdv()
	{

		c = a >> combo(program[ip + 1]);
		ip += 2;
	}

};


void Day17()
{
	myFile in = myFile();
	in.Open("Days/Day17/in.txt");
	in.ReadFile();


	int sum = 0;

	long long a, b, c;

	a = stoll(in.inputWords[0][2]);
	b = stoll(in.inputWords[1][2]);
	c = stoll(in.inputWords[2][2]);

	vector<long long> program;

	for (auto s : split(in.inputWords[4][1], ','))
	{
		program.push_back(stoll(s));
	}

	computer comp = computer(a, b, c, program);

	long long last = 0b001000011101101001111100011010101011110111110100;
	long long A, B, C;
	for (long long i = 0; i < 1 << 3; i++)
	{
		A = i + (last << 3);
		B = 0;
		C = 0;

		B = 7 & A;
		B ^= 2;
		C = A >> B;
		B ^= 3;
		B ^= C;
		if ((B&7) == 2)
			cout << i << " ";

	}
	cout <<"\n"<< last<<"\n";
	A = last;

	while (A != 0)
	{
		B = 7 & A;
		B ^= 2;
		C = A >> B;
		B ^= 3;
		B ^= C;
		cout << (B & 7) << ',';
		A >>= 3;
	}

	cout << comp.out;
}