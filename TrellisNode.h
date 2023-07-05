#pragma once
#include <vector>
#include <string>

struct TrellisNode
{
	int INF = 10000;
	int errors = INF;
	int parent = -1;
	std::string rule;
	int bit = -1;

};

