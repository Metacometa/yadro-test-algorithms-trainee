#include <iostream>
#include <fstream>
#include <cstring>

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

bool isCode(char *cstring) {
    for (int i = 0; cstring[i] != '\0'; ++i) {
        if (cstring[i] != '0' and cstring[i] != '1') {
            return false;
        }
    }

    return true;
}

bool isEncoded(char *cstring) {
    for (int i = 0; cstring[i] != '\0'; ++i) {
        if (cstring[i] != '0' and cstring[i] != '1' and cstring[i] != '-') {
            return false;
        }
    }

    return true;
}

void print_help() {
    std::cout << std::endl;
    std::cout << "viterbi.exe [--option]" << std::endl;
    std::cout << "    Options:" << std::endl;
    std::cout << "      [--encode] <code>   convolutionaly codes message" << std::endl;
    std::cout << "      [--decode] <code>   decodes message using viterbi algorithm" << std::endl;
    std::cout << "      [--channel] <file_name>   writting results of binary symmetric channel testing system in file" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{   
    if (argc == 2 and std::strcmp("--help", argv[1]) == 0) {
        print_help();
    }
    else if (argc == 3) {
        if (std::strcmp("--encode", argv[1]) == 0 and isCode(argv[2])) {
            ConvolutionalCoding coder;
            ConvolutionalCoding::printEncoded(coder.encode(argv[2]));
        }
        else if (std::strcmp("--decode", argv[1]) == 0 and isEncoded(argv[2])) {
            ViterbiDecoding decoder;
            ViterbiDecoding::printDecoded(decoder.decode(argv[2]));
        }
        else if (std::strcmp("--channel", argv[1]) == 0) {
            writeStatisticInFile(argv[2]);
        }
    }
    else { 
        print_help();
    }
}

