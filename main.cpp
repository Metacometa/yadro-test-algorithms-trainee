#include <iostream>
#include "BinarySymmetricChannel.h"

int main()
{
    double probability = 0.2;
    std::cout << BinarySymmetricChannel::getErrorProbabilityPerBit("1001010101010010101010101010010101010010101001010101", probability) << " " << probability;

    int length = 100;
    std::string message = BinarySymmetricChannel::generateMessage(length);
    std::cout << message << std::endl;
    for (double i = 0; i <= 1; i += 0.05) {
        std::cout << i << ": " << BinarySymmetricChannel::getErrorProbabilityPerBit(message, i) << std::endl;
    }


    std::cout << std::endl;
    std::cout << BinarySymmetricChannel::getErrorProbabilityPerBit("10000100101010110001001111010101001011010101", 0.0);


    
    ConvolutionalCoding cc;
    std::string encoded = cc.encode("010111001010001");
    ConvolutionalCoding::printEncoded(encoded);

    ViterbiDecoding vd;
    std::string vd_path = vd.decode("11-01-01-11");
    ViterbiDecoding::printPath(vd_path);
   
    std::vector<bool> test_bool_1{ 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1 };

    vd_path = vd.decode(test_bool_1);
    ViterbiDecoding::printPath(vd_path);

    std::string test_string_1 = "11-01-10-01-00-01-01-11";

    vd_path = vd.decode(test_string_1);
    ViterbiDecoding::printPath(vd_path);
    

    
    std::string test_string_2 = "11-00-00-11-10";
    vd_path = vd.decode(test_string_2);
    ViterbiDecoding::printPath(vd_path);

    std::string test_string_3 = "11-10-11-11-01-10-01-00-01-01-11";
    vd_path = vd.decode(test_string_3);
    ViterbiDecoding::printPath(vd_path);
    


}

