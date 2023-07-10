#include "ConvolutionalCoding.h"
#include "ViterbiDecoding.h"
#include <iostream>
#include <string>

void custom_assert(const std::string &a, const std::string &b) {
    if (a.length() != b.length()) {
        throw 0;
    }

    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) {
            throw 0;
        }
    }
}

int main() {
    ConvolutionalCoding coder;
    std::string input_1 = "100111011";
    std::string correct_output_1 = "11-10-11-11-01-10-01-00-01-01-11-00" ;

    try {
        custom_assert(correct_output_1, coder.encode(input_1));
    }
    catch (int i) {
        std::cerr << correct_output_1 << " != " << coder.encode(input_1) << std::endl;
        abort();
    }  

    ViterbiDecoding decoder;
    std::string input_2 = "11-01-10-01-00-01-01-11";
    std::string correct_output_2 = "11101";

    try {
        custom_assert(correct_output_2, decoder.decode(input_2));
    }
    catch (int i) {
        std::cerr << correct_output_2 << " != " << decoder.decode(input_2) << std::endl;
        abort();
    }

    try {
        custom_assert("111", decoder.decode(input_2));
    }
    catch (int i) {
        std::cerr << correct_output_2 << " != " << decoder.decode(input_2) << std::endl;
        abort();
    }
    
    std::cout << "No mistakes in test" << std::endl;
}