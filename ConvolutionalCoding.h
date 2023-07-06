#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Coder.h"

class ConvolutionalCoding
{
public:
	static void printEncoded(const std::string& encoded) {
		for (auto& bit : encoded) {
			std::cout << bit;
		}
		std::cout << std::endl;
	}

	std::string coding(const std::vector<bool>& message) {
		std::string encoded;
		Coder coder;

		for (const auto& bit : message) {
			coder.push(bit);
			encoded += coder.getX() + 48;
			encoded += coder.getY() + 48;
			encoded += '-';
		}

		coder.push(false);
		while (!coder.isEmpty()) {
			encoded += coder.getX() + 48;
			encoded += coder.getY() + 48;
			encoded += '-';
			coder.push(false);
		}

		if (encoded[encoded.length() - 1] == '-') {
			encoded.erase(encoded.end() - 1);
		}

		return encoded;
	}

	std::string coding(const std::string& message) {
		std::vector<bool> messageInBool;

		for (auto& symbol : message) {
			if (symbol == '0') {
				messageInBool.emplace_back(false);
			}
			else if (symbol == '1') {
				messageInBool.emplace_back(true);
			}
		}

		return coding(messageInBool);
	}
};

