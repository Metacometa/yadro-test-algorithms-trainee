#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "TrellisNode.h"
#include <set>

#include "Variables.h"

class ViterbiDecoding
{
	std::unordered_map<int, std::vector<int>> branches{ {0, {0, 2}}, {1, {0, 2}}, {2, {1, 3}}, {3, {1, 3}} };
	std::unordered_map<int, std::string> trellisBijectionToSymbol{ {0, "00"}, {1, "01"}, {2, "10"}, {3, "11"}};

	std::unordered_map<int, std::vector<std::string>> rules{ {0, {"00", "11"}}, {1, {"11", "00"}}, {2, {"10", "01"}}, {3, {"01", "10"}} };

	std::vector<std::vector<TrellisNode>> states;

	std::set<int> includedStates{ 0 };


	//traceback path
	std::string traceBackPath(const int& state);

	std::string traceBackLowestErrorPath();

	//trellis
	void buildTrellisDiagram(const std::vector<bool>& encoded);

	void calculateErrorsForPaths(const std::vector<bool>& encoded);

	//utils
	int findMinState(const std::vector<TrellisNode>& trellisColumn);
	int nextNodeByRule(const std::string& node, const std::string& rule);
	size_t hammingDistance(const std::string& a, const std::string& b);

public:
	std::string decode(const std::string& encoded);

	std::string decode(const std::vector<bool>& encoded);

	static void printPath(const std::string& path);
};

