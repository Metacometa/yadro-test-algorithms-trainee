#include <iostream>
#include "ViterbiDecoding.h"
#include "ConvolutionalCoding.h"

int main()
{
    ConvolutionalCoding cc;
    std::string encoded = cc.coding("11");
    ConvolutionalCoding::printEncoded(encoded);



    ViterbiDecoding vd;
    std::string vd_path = vd.decoding("11-01-01-11");
    ViterbiDecoding::printPath(vd_path);



    /*
    std::vector<bool> test_bool_1{ 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1 };

    vd_path = vd.decoding(test_bool_1);
    ViterbiDecoding::printPath(vd_path);

    std::string test_string_1 = "11-01-10-01-00-01-01-11";

    vd_path = vd.decoding(test_string_1);
    ViterbiDecoding::printPath(vd_path);
    */

    /*
    std::string test_string_2 = "11-00-00-11-10";
    vd_path = vd.decoding(test_string_2);
    ViterbiDecoding::printPath(vd_path);

    std::string test_string_3 = "11-10-11-11-01-10-01-00-01-01-11";
    vd_path = vd.decoding(test_string_3);
    ViterbiDecoding::printPath(vd_path);
    */

}

