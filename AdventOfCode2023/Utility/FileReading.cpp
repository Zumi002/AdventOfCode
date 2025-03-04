#include "FileReading.h"
#include "SupportFunc.h"

int myFile::Open(string path)
{
	in.open(path);
	opened = true;
	return in.is_open();
}


string myFile::NextLine()
{
	string Res = "";
	char tmp;
	while (in.get(tmp))
	{
		if (tmp != '\n')
		{
			Res += tmp;
		}
		else
		{
			break;
		}
	}
	return Res;
}

void myFile::GetInputLinesAndWords()
{
	//lines vector ends with empty line (""), words vector ends with empty word ("")
	while (!in.eof())
	{
		string tmp = NextLine();
		nol++;
		inputLines.push_back(tmp);
		vector<string> w;
		for (auto s : split(tmp, ' '))
		{
			if(s!="")w.push_back(s);
		}
		inputWords.push_back(w);
		now.push_back(inputWords[nol-1].size());
	}


}


void myFile::ReadFile()
{
	nol = 0;
	GetInputLinesAndWords();
}




