#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "TrellisNode.h"

class ViterbiDecoding
{
	static const int TRELLIS_ROWS = 4;
	static const int INCORRECT_CODE_SIZE_CODE = 0;
	static const int INCORRECT_HAMMING_INPUT_CODE = 1;
	std::unordered_map<int, std::vector<int>> Trellis{ {0, {0, 2}}, {1, {0, 2}}, {2, {1, 3}}, {3, {1, 3}} };
	std::unordered_map<std::string, int> trellisBijection{ {"00", 0}, {"01", 1}, {"10", 2}, {"11", 3} };

	std::vector<std::vector<TrellisNode>> trellisDiagram;
public:
	ViterbiDecoding(const std::vector<bool>&code) {
		try {
			buildTrellisDiagram(code);
		}
		catch(int i) { 
			switch (i) {
			case INCORRECT_CODE_SIZE_CODE:
				std::cout << "Incorrect code size" << std::endl;
				break;
			case INCORRECT_HAMMING_INPUT_CODE:
				std::cout << "Words have different lengths in hamming distance" << std::endl;
				break;
			}
		}
	}

	void buildTrellisDiagram(const std::vector<bool>& code) {
		if (code.size() == 0 or code.size() % 2 == 1) {
			throw INCORRECT_CODE_SIZE_CODE;
		}

		trellisDiagram.resize(code.size(), std::vector<TrellisNode>(TRELLIS_ROWS));

		hammingDistance("aa", "aa");


		for (int i = 0; i < trellisDiagram.size(); ++i) {
			for (int j = 0; j < trellisDiagram[i].size(); ++j) {
				std::cout << trellisDiagram[i][j].error << " ";
			}
			std::cout << std::endl;
		}	
	}

	int hammingDistance(const std::string &a, const std::string&b) {
		if (a.length() != b.length()) {
			throw INCORRECT_HAMMING_INPUT_CODE;
		}

		int errors = 0;
		for (int i = 0; i < a.length(); ++i) {
			if (a[i] != b[i]) {
				errors++;
			}
		}

		return errors;
	}
};

