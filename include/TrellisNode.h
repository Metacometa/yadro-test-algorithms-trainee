#pragma once
#include <vector>
#include <string>
#include "Variables.h"

struct TrellisNode
{
	int errors = Variables::INF;
	int parent = -1;
	std::string rule;
	int bit = -1;
};

