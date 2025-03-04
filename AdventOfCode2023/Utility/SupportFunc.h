#pragma once

#include "FileReading.h"
#include <string>
#include <algorithm>
// simple clamp x=<1,a> 
int ClampS(int x, int a);
vector<string> split(string str, char delimiter);
int FirstUniqeCharsIndex(string str, int span, int step);
bool IsSubstrUniqe(string str);

bool IsLetter(char c);
bool IsDigit(char c);

const string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string digits = "0123456789";
