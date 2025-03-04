#pragma once

#include "FileReading.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// simple clamp x=<1,a> 
int ClampS(int x, int a);
vector<string> split(string str, char delimiter);
int FirstUniqeCharsIndex(string str, int span, int step);
bool IsSubstrUniqe(string str);

