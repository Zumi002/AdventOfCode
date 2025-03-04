#pragma once

#include "SupportFunc.h"

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class myFile
{
	public:
	
		ifstream in;

		string tmp;
		bool opened;

		vector<string> inputLines;
		int nol =0 ;
		vector<int> now;
		vector<vector<string>> inputWords;

		int Open(std::string asdf);

		string NextLine();

		void GetInputLinesAndWords();

		void ReadFile();

};


