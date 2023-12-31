#pragma once

namespace Variables {
	static const int TRELLIS_ROWS = 4;

	static const int INCORRECT_CODE_SIZE_CODE = 0;
	static const int INCORRECT_HAMMING_INPUT_CODE = 1;
	static const int INCORRECT_RULE = 2;
	static const int INCORRECT_MIN_STATE = 3;
	static const int INCORRECT_PROBABILITY = 4;
	static const int INCORRECT_MESSAGES_LENGTHS = 5;

	static const int SHIFT_FROM_INT_TO_SYMBOL = 48;
	static const int CONSTRAINT = 3;

	static const size_t INF = 100000;

	//for measurement
	static const size_t repeatsOfMeasurement = 10;
	static const size_t lengthOfMessage = 100;
	static const double probabilityStep = 0.02;
	static const double startProbability = 0.0;
	static const double endProbability = 1.0;
}


