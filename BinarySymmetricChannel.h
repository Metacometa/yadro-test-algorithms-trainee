#pragma once
#include "ConvolutionalCoding.h"
#include "ViterbiDecoding.h"
#include <vector>
#include <random>

#include "Variables.h"

class BinarySymmetricChannel
{	
	static std::string transmit_message(const std::string& encoded_message, const double& error_probability);

	static char inversedBit(const char& bit);

	static std::string passMessageByChannel(const std::string& message, const double& error_probability);

	static int countErrors(const std::string& input_message, const std::string& output_message);

public:

	static double getErrorProbabilityPerBit(const std::string& message, const double& error_probability);

	static double getErrorProbabilityPerBit(const std::vector<bool>& message, const double& error_probability);

	static std::string generateMessage(const size_t& length);
};

