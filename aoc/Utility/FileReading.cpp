#include "FileReading.h"


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
		vector<string> words;
		now.push_back(0);
		if (tmp == "")
		{
			now[nol - 1]++;
			words.push_back("");
		}
		string word = "";
		for(char a : tmp)
		{
			if (a == ' ')
			{
				words.push_back(word);
				now[nol - 1]++;
				word = "";
			}
			else
			{
				word += a;
			}
		}
		now[nol - 1]++;
		words.push_back(word);
		inputWords.push_back(words);
	}


}


void myFile::ReadFile()
{
	nol = 0;
	GetInputLinesAndWords();
}




