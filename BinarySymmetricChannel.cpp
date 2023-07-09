#include "BinarySymmetricChannel.h"

std::string BinarySymmetricChannel::transmit_message(const std::string& encoded_message, const double& error_probability) {
	if (error_probability < 0.0 or error_probability > 1.00) {
		throw Variables::INCORRECT_PROBABILITY;
	}

	std::string noised_message;

	std::random_device device;
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	for (auto& bit : encoded_message) {
		if (bit == '-') {
			noised_message += bit;
			continue;
		}

		if (dist(device) > error_probability) {
			noised_message += bit;
		}
		else {
			noised_message += inversedBit(bit);
		}
	}
	return noised_message;
}

char BinarySymmetricChannel::inversedBit(const char& bit) {
	if (bit == '1') {
		return '0';
	}
	else {
		return '1';
	}
}

std::string BinarySymmetricChannel::passMessageByChannel(const std::string& message, const double& error_probability) {
	ConvolutionalCoding coder;
	ViterbiDecoding decoder;

	std::string encoded_message = coder.encode(message);
	std::string transmitted_message;
	try {
		transmitted_message = transmit_message(encoded_message, error_probability);
	}
	catch (int i) {
		if (i == Variables::INCORRECT_PROBABILITY) {
			std::cout << "Incorrect probability" << std::endl;
		}
		return "";
	}

	return decoder.decode(transmitted_message);
}

int BinarySymmetricChannel::countErrors(const std::string& input_message, const std::string& output_message)
{
	if (input_message.length() != output_message.length()) {
		throw Variables::INCORRECT_MESSAGES_LENGTHS;
	}

	size_t errors = 0;
	for (size_t i = 0; i < input_message.length(); ++i) {
		if (input_message[i] != output_message[i]) {
			errors++;
		}
	}

	return errors;
}

std::string BinarySymmetricChannel::generateMessage(const size_t& length)
{
	std::random_device device;
	std::uniform_int_distribution<int> dist(0, 1);
	
	std::string message;

	for (size_t i = 0; i < length; ++i) {
		if (dist(device)) {
			message += '1';
		}
		else {
			message += '0';
		}
	}

	return message;
}

double BinarySymmetricChannel::getErrorProbabilityPerBit(const std::vector<bool>& message, const double& error_probability)
{
	std::string messageInString;

	for (const auto& bit : message) {
		if (bit == false) {
			messageInString += '0';
		}
		else {
			messageInString += '1';
		}
	}

	return getErrorProbabilityPerBit(message, error_probability);
}

double BinarySymmetricChannel::getErrorProbabilityPerBit(const std::string& message, const double& error_probability)
{
	std::string passedMessage = passMessageByChannel(message, error_probability);

	double errors = 0;
	try {
		errors = countErrors(message, passedMessage);
	}
	catch (int i) {
		if (i == Variables::INCORRECT_MESSAGES_LENGTHS) {
			std::cout << "Incorrect messages lengths" << std::endl;
		}
		return 0.0;
	}

	if (message.length() == 0) {
		return 0.0;
	}

	return errors / static_cast<double>(message.length());
}
