#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "TrellisNode.h"
#include <set>

class ViterbiDecoding
{
	static const int TRELLIS_ROWS = 4;
	static const int INCORRECT_CODE_SIZE_CODE = 0;
	static const int INCORRECT_HAMMING_INPUT_CODE = 1;
	std::unordered_map<int, std::vector<int>> branches{ {0, {0, 2}}, {1, {0, 2}}, {2, {1, 3}}, {3, {1, 3}} };
	std::unordered_map<std::string, int> trellisBijectionToInt{ {"00", 0}, {"01", 1}, {"10", 2}, {"11", 3} };
	std::unordered_map<int, std::string> trellisBijectionToSymbol{ {0, "00"}, {1, "01"}, {2, "10"}, {3, "11"}};

	std::vector<std::vector<TrellisNode>> states;

	std::set<int> includedStates{ 0 };
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

	void buildTrellisDiagram(const std::vector<bool>& encoded) {
		if (encoded.size() == 0 or encoded.size() % 2 == 1) {
			throw INCORRECT_CODE_SIZE_CODE;
		}

		states.resize(encoded.size() / 2 + 1, std::vector<TrellisNode>(TRELLIS_ROWS));
		states[0][0].errors = 0;
		calculateErrorsForPaths(encoded);

		for (auto& i : states) {
			for (auto& j : i) {
				std::cout << j.errors << " ";
			}
			std::cout << std::endl;
		}

	}

	void calculateErrorsForPaths(const std::vector<bool>& encoded) {
		std::string code = "";
		for (int i = 0; i < encoded.size(); ++i) {
			code += encoded[i] + 48;

			if (i % 2 == 1) {
				for (auto& state : includedStates) {
					for (auto& connected : branches[state]) {
						int errors = hammingDistance(code, trellisBijectionToSymbol[connected]);

						if (states[i / 2][state].errors + errors < states[i / 2 + 1][connected].errors) {
							states[i / 2 + 1][connected].errors = states[i / 2][state].errors + errors;
							states[i / 2 + 1][connected].parent = trellisBijectionToSymbol[state];
						}
						includedStates.insert(connected);
					}
				}
				code = "";
			}

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

