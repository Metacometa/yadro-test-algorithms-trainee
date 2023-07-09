#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Coder.h"

#include "Variables.h"

class ConvolutionalCoding
{
public:
	static void printEncoded(const std::string& encoded);

	std::string encode(const std::vector<bool>& message);

	std::string encode(const std::string& message);
};

