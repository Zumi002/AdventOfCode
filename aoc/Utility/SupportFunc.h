#pragma once

#include "FileReading.h"
#include <string>
#include <algorithm>
// simple clamp x=<1,a> 
int ClampS(int x, int a);
vector<string> split(string str, char delimiter);