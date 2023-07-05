#include <iostream>
#include "ViterbiDecoding.h"

int main()
{
    ViterbiDecoding vd({1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1});

    ViterbiDecoding vd1({ 1, 1, 1, 0,  1, 1, 1, 1, 0, 1, 1, 0,  0,1, 0,0, 0,1, 0,1, 1,1 });

    ViterbiDecoding vd2({ 1,1, 1,0, 1,1, 1,1, 0,1, 1,0 ,0,1 ,0,0, 0,1, 0,1, 1,1, });

}

