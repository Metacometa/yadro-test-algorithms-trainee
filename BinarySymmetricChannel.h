#pragma once
#include "ConvolutionalCoding.h"
#include "ViterbiDecoding.h"
#include <random>

class BinarySymmetricChannel
{
	static void activate(const std::string &message, const double &error_probability) {
		ConvolutionalCoding coder;
		ViterbiDecoding decoder;

		std::string encoded = coder.encode(message);

	}
};

