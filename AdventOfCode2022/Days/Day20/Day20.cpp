#include "../../Utility/SupportFunc.h"
#include "Day20.h"


struct Number
{
	long long val;
	int id;

};

int FindById(int toFind,vector<Number*> &nums)
{
	for(int i = 0;i<nums.size();i++)
	{
		if (nums[i]->id == toFind)
		{
			return i;
		}
	}
	return -1;
}

void moveLeft(long long moveSteps,int index, vector<Number*>& nums)
{
	moveSteps %= nums.size()-1;
	bool around = false;
	for(int j = 0;j<moveSteps;j++)
	{
		
		if (index - j == 0)
		{
			Number* tmp = nums[index - j];
			nums[index - j] = nums[index + nums.size() - j - 1];
			nums[index - j - 1 + nums.size()] = tmp;
			index += nums.size();
			around = true;
		}
		else
		{
			Number* tmp = nums[index - j];
			nums[index - j] = nums[index - j - 1];
			nums[index - j - 1] = tmp;
			//cout << "change " << nums[index - j - 1]->val << " <-> " << nums[index - j]->val<<"\n";
		}
	}
	if (around)
	{
		Number* first = nums[0];
		for (int i = 0; i < nums.size()-1; i++)
		{
			nums[i] = nums[i + 1];
		}
		nums[nums.size() - 1] = first;
	}
}

void moveRight(long long moveSteps, int index, vector<Number*>& nums)
{
	moveSteps %= nums.size()-1;
	bool around = false;
	for (int j = 0; j < moveSteps; j++)
	{

		if (index + j == nums.size()-1)
		{
			Number* tmp = nums[index + j];
			nums[index + j] = nums[index - nums.size() + j + 1];
			nums[index + j + 1 - nums.size()] = tmp;
			index -= nums.size();
		}
		else
		{
			Number* tmp = nums[index + j];
			nums[index + j] = nums[index + j + 1];
			nums[index + j + 1] = tmp;
			//cout << "change " << nums[index + j + 1]->val << " <-> " << nums[index + j]->val << "\n";
		}

	}
	if (around)
	{
		Number* last = nums[nums.size()-1];
		for (int i = nums.size() - 1; i>0 ;i--)
		{
			nums[i] = nums[i - 1];
		}
		nums[nums.size() - 1] = last;
	}
}

void printVals(vector<Number*>& nums)
{
	for (Number* a : nums)
	{
		cout << a->val << " ";
	}
	cout << "\n";
}

void Day20()
{
	myFile in = myFile();
	in.Open("Days/Day20/in.txt");
	in.ReadFile();


	vector<Number*> nums;
	int zeroId = 0;

	for (int i = 0; i < in.nol; i++)
	{
		Number* num = new Number();
		num->val = (long long) stoi(in.inputLines[i])* 811589153;
		if (stoi(in.inputLines[i]) == 0)zeroId = i;
		num->id = i;
		nums.push_back(num);
	}
	//printVals(nums);
	for(int j =0;j<10;j++)
	{
		for (int i = 0; i < nums.size(); i++)
		{
			int index = FindById(i, nums);
			if (nums[index]->val < 0)
			{
				moveLeft(-nums[index]->val, index, nums);
			}
			else
			{
				moveRight(nums[index]->val, index, nums);
			}	
		
		}
		//printVals(nums);
	}
	//printVals(nums);
	int zeroIndex = FindById(zeroId, nums);
	int firstIndex = zeroIndex + (1000 % nums.size()) < nums.size() ? zeroIndex + (1000 % nums.size()) : zeroIndex + (1000 % nums.size()) - nums.size();
	int secondIndex = zeroIndex + (2000 % nums.size()) < nums.size() ? zeroIndex + (2000 % nums.size()) : zeroIndex + (2000 % nums.size()) - nums.size();
	int thirdIndex = zeroIndex + (3000 % nums.size()) < nums.size() ? zeroIndex + (3000 % nums.size()) : zeroIndex + (3000 % nums.size()) - nums.size();
	long long sum = nums[firstIndex]->val + nums[secondIndex]->val + nums[thirdIndex]->val;
	cout << nums[firstIndex]->val<<" "<< nums[secondIndex]->val<<" "<< sum;
}