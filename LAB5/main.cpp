#include <stdexcept>
#include <cassert>
#include <iostream>
#include "circular_buffer.h"

int main()
{
    CCircular_Buffer<int> rbuf(3);
    rbuf.push_back(2);
    rbuf.push_back(3);
    rbuf.push_back(4);
    rbuf.push_back(5);
    //std::cout << rbuf[0];
    for(auto i : rbuf)
        std::cout << i << " ";
    auto x = std::max_element(rbuf.begin(), rbuf.end());
    std::cout << *x << "\n";
    x = std::min_element(rbuf.begin(), rbuf.end());
    std::cout << *x << "\n";
    return 0;
}