#include "SupportFunc.h"

int ClampS(int x, int a)
{

	return x % a ? x % a : a;
}
