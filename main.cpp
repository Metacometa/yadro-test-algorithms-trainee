#include <iostream>
#include <fstream>

#include "BinarySymmetricChannel.h"

double getTotalErrorProbabilityOnBit(const size_t &length, const double &error_probability) {
    return BinarySymmetricChannel::getErrorProbabilityPerBit(BinarySymmetricChannel::generateMessage(length), error_probability);
}

void writeStatisticInFile(const std::string& file_name) {
    std::ofstream file(file_name);

    double totalErrorProbabilityOnBit;
    for (double error_probability = 0; error_probability < Variables::endProbability; error_probability += Variables::probabilityStep) {
        totalErrorProbabilityOnBit = 0;

        for (size_t repeat = 0; repeat < Variables::repeatsOfMeasurement; ++repeat) {
            totalErrorProbabilityOnBit += getTotalErrorProbabilityOnBit(Variables::lengthOfMessage, error_probability);
        }

        totalErrorProbabilityOnBit /= Variables::repeatsOfMeasurement;

        file << error_probability << " " << totalErrorProbabilityOnBit << std::endl;
    }

    totalErrorProbabilityOnBit = 0;
    for (size_t repeat = 0; repeat < Variables::repeatsOfMeasurement; ++repeat) {
        totalErrorProbabilityOnBit += getTotalErrorProbabilityOnBit(Variables::lengthOfMessage, Variables::endProbability);
    }

    totalErrorProbabilityOnBit /= Variables::repeatsOfMeasurement;

    file << Variables::endProbability << " " << totalErrorProbabilityOnBit << std::endl;

    file.close();
}

int main()
{
    writeStatisticInFile("test1.txt");
}

