#include "ViterbiDecoding.h"

int ViterbiDecoding::findMinState(const std::vector<TrellisNode>& trellisColumn) {
	int minErrors = Variables::INF;
	int minState = -1;

	for (int i = 0; i < trellisColumn.size(); ++i) {
		if (trellisColumn[i].errors < minErrors) {
			minErrors = trellisColumn[i].errors;
			minState = i;
		}
	}

	if (minState == -1) {
		throw Variables::INCORRECT_MIN_STATE;
	}

	return minState;
}

std::string ViterbiDecoding::traceBackPath(const int& state) {
	int currentState = state;
	std::string path;
	for (int i = states.size() - 1; i > 0; --i) {
		path += states[i][currentState].bit + Variables::SHIFT_FROM_INT_TO_SYMBOL;
		currentState = states[i][currentState].parent;
	}

	reverse(path.begin(), path.end());
	return path.substr(0, path.size() - Variables::CONSTRAINT);
}

std::string ViterbiDecoding::traceBackLowestErrorPath() {
	int minState = findMinState(states[states.size() - 1]);
	return traceBackPath(minState);
}

void ViterbiDecoding::buildTrellisDiagram(const std::vector<bool>& encoded) {
	if (encoded.size() == 0 or encoded.size() % 2 == 1) {
		throw Variables::INCORRECT_CODE_SIZE_CODE;
	}

	states.resize(encoded.size() / 2 + 1, std::vector<TrellisNode>(Variables::TRELLIS_ROWS));
	states[0][0].errors = 0;
	calculateErrorsForPaths(encoded);
}

void ViterbiDecoding::calculateErrorsForPaths(const std::vector<bool>& encoded) {
	std::string code = "";
	for (int i = 0; i < encoded.size(); ++i) {
		code += encoded[i] + Variables::SHIFT_FROM_INT_TO_SYMBOL;
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

int ViterbiDecoding::nextNodeByRule(const std::string& node, const std::string& rule) {
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
	throw Variables::INCORRECT_RULE;
}

int ViterbiDecoding::hammingDistance(const std::string& a, const std::string& b) {
	if (a.length() != b.length()) {
		throw Variables::INCORRECT_HAMMING_INPUT_CODE;
	}

	int errors = 0;
	for (int i = 0; i < a.length(); ++i) {
		if (a[i] != b[i]) {
			errors++;
		}
	}

	return errors;
}

std::string  ViterbiDecoding::decode(const std::string& encoded) {
	std::vector<bool> encodedInBool;

	for (auto& symbol : encoded) {
		if (symbol == '0') {
			encodedInBool.emplace_back(false);			}
		else if (symbol == '1') {
			encodedInBool.emplace_back(true);
		}
	}

	return decode(encodedInBool);
}

std::string ViterbiDecoding::decode(const std::vector<bool>& encoded) {
	states.clear();
	includedStates.clear();
	includedStates.insert(0);

	try {
		buildTrellisDiagram(encoded);
		return traceBackLowestErrorPath();
	}
	catch (int i) {
		switch (i) {
		case Variables::INCORRECT_CODE_SIZE_CODE:
			std::cout << "Incorrect code size" << std::endl;
			break;
		case Variables::INCORRECT_HAMMING_INPUT_CODE:
			std::cout << "Words have different lengths in hamming distance" << std::endl;
			break;
		case Variables::INCORRECT_RULE:
			std::cout << "Incorrect rule" << std::endl;
			break;
		case Variables::INCORRECT_MIN_STATE:
			std::cout << "Incorrect min state" << std::endl;
			break;
		}
	}
}

void ViterbiDecoding::printPath(const std::string& path) {
	for (auto& i : path) {
		std::cout << i;
	}
	std::cout << std::endl;
}