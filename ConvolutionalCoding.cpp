#include "ConvolutionalCoding.h"

void ConvolutionalCoding::printEncoded(const std::string& encoded) {
	for (auto& bit : encoded) {
		std::cout << bit;
	}
	std::cout << std::endl;
}

std::string ConvolutionalCoding::encode(const std::vector<bool>& message) {
	std::string encoded;
	Coder encode;

	for (const auto& bit : message) {
		encode.push(bit);
		encoded += encode.getX() + Variables::SHIFT_FROM_INT_TO_SYMBOL;
		encoded += encode.getY() + Variables::SHIFT_FROM_INT_TO_SYMBOL;
		encoded += '-';
	}

	for (int i = 0; i < Variables::CONSTRAINT; ++i) {
		encode.push(false);
		encoded += encode.getX() + Variables::SHIFT_FROM_INT_TO_SYMBOL;
		encoded += encode.getY() + Variables::SHIFT_FROM_INT_TO_SYMBOL;
		encoded += '-';
	}

	if (encoded[encoded.length() - 1] == '-') {
		encoded.erase(encoded.end() - 1);
	}

	return encoded;
}

std::string ConvolutionalCoding::encode(const std::string& message) {
	std::vector<bool> messageInBool;

	for (auto& symbol : message) {
		if (symbol == '0') {
			messageInBool.emplace_back(false);
		}
		else if (symbol == '1') {
			messageInBool.emplace_back(true);
		}
	}

	return encode(messageInBool);
}