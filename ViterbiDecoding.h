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
	static const int INCORRECT_RULE = 2;
	static const int INCORRECT_MIN_STATE = 3;
	static const int SHIFT_FROM_INT_TO_SYMBOL = 48;
	std::unordered_map<int, std::vector<int>> branches{ {0, {0, 2}}, {1, {0, 2}}, {2, {1, 3}}, {3, {1, 3}} };
	std::unordered_map<int, std::string> trellisBijectionToSymbol{ {0, "00"}, {1, "01"}, {2, "10"}, {3, "11"}};

	std::unordered_map<int, std::vector<std::string>> rules{ {0, {"00", "11"}}, {1, {"11", "00"}}, {2, {"10", "01"}}, {3, {"01", "10"}} };

	std::vector<std::vector<TrellisNode>> states;

	std::set<int> includedStates{ 0 };

	int findMinState(const std::vector<TrellisNode>& trellisColumn) {
		int minErrors = 10000;
		int minState = -1;

		for (int i = 0; i < trellisColumn.size(); ++i) {
			if (trellisColumn[i].errors < minErrors) {
				minErrors = trellisColumn[i].errors;
				minState = i;
			}
		}

		if (minState == -1) {
			throw INCORRECT_MIN_STATE;
		}

		return minState;
	}

	std::string traceBackPath(const int& state) {
		int currentState = state;
		std::string path;
		for (int i = states.size() - 1; i > 0; --i) {
			path += states[i][currentState].bit + SHIFT_FROM_INT_TO_SYMBOL;
			currentState = states[i][currentState].parent;
		}

		reverse(path.begin(), path.end());
		return path;
	}

	std::string traceBackLowestErrorPath() {
		int minState = findMinState(states[states.size() - 1]);
		return traceBackPath(minState);
	}

	void buildTrellisDiagram(const std::vector<bool>& encoded) {
		if (encoded.size() == 0 or encoded.size() % 2 == 1) {
			throw INCORRECT_CODE_SIZE_CODE;
		}

		states.resize(encoded.size() / 2 + 1, std::vector<TrellisNode>(TRELLIS_ROWS));
		states[0][0].errors = 0;
		calculateErrorsForPaths(encoded);
	}

	void calculateErrorsForPaths(const std::vector<bool>& encoded) {
		std::string code = "";
		for (int i = 0; i < encoded.size(); ++i) {
			code += encoded[i] + SHIFT_FROM_INT_TO_SYMBOL;
			std::vector<int> newStates;
			if (i % 2 == 1) {
				for (auto& state : includedStates) {
					for (int numberOfRule = 0; numberOfRule < rules[state].size(); ++numberOfRule) {
						int errors = hammingDistance(code, rules[state][numberOfRule]);
						int next = nextNodeByRule(trellisBijectionToSymbol[state], rules[state][numberOfRule]);

						if (states[i / 2][state].errors + errors < states[i / 2 + 1][next].errors) {
							states[i / 2 + 1][next].errors = states[i / 2][state].errors + errors;
							states[i / 2 + 1][next].parent = state;
							states[i / 2 + 1][next].rule = rules[state][numberOfRule];
							states[i / 2 + 1][next].bit = numberOfRule;
						}

						newStates.push_back(next);
					}
				}

				for (auto& j : newStates) {
					includedStates.insert(j);
				}
				code = "";
			}

		}
	}

	int nextNodeByRule(const std::string& node, const std::string& rule) {
		if (node == "00" and rule == "00") {
			return 0;
		}
		else if (node == "00" and rule == "11") {
			return 2;
		}

		if (node == "01" and rule == "00") {
			return 2;
		}
		else if (node == "01" and rule == "11") {
			return 0;
		}

		if (node == "10" and rule == "10") {
			return 1;
		}
		else if (node == "10" and rule == "01") {
			return 3;
		}

		if (node == "11" and rule == "10") {
			return 3;
		}
		else if (node == "11" and rule == "01") {
			return 1;
		}

		std::cout << "THROW " << node << " " << rule << std::endl;
		throw INCORRECT_RULE;
	}

	int hammingDistance(const std::string& a, const std::string& b) {
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

public:
	ViterbiDecoding() {}

	std::string decode(const std::string& encoded) {
		std::vector<bool> encodedInBool;

		for (auto& symbol : encoded) {
			if (symbol == '0') {
				encodedInBool.emplace_back(false);
			}
			else if (symbol == '1') {
				encodedInBool.emplace_back(true);
			}
		}

		return decode(encodedInBool);
	}


	std::string decode(const std::vector<bool>& encoded) {
		try {
			buildTrellisDiagram(encoded);

			return traceBackLowestErrorPath();
		}
		catch (int i) {
			switch (i) {
			case INCORRECT_CODE_SIZE_CODE:
				std::cout << "Incorrect code size" << std::endl;
				break;
			case INCORRECT_HAMMING_INPUT_CODE:
				std::cout << "Words have different lengths in hamming distance" << std::endl;
				break;
			case INCORRECT_RULE:
				std::cout << "Incorrect rule" << std::endl;
				break;
			case INCORRECT_MIN_STATE:
				std::cout << "Incorrect min state" << std::endl;
				break;
			}
		}
	}

	//utils
	static void printPath(const std::string& path) {
		for (auto& i : path) {
			std::cout << i;
		}
		std::cout << std::endl;
	}
};

