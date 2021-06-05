#include <iostream>
#include <algorithm>

#include "circular_buffer.h"


int main() {
    CCircular_Buffer<int> rbuf(3);

    rbuf.push_back(5);
    rbuf.push_back(10);
    rbuf.push_back(15);
    for(const auto i : rbuf)
        std::cout << i << " ";

    rbuf.push_back(20);
    rbuf.push_back(666);
    rbuf.push_back(30);
    for(auto i : rbuf)
        std::cout << i << " ";

    rbuf.push_front(55);
    rbuf.push_front(56);
    rbuf.push_front(57);
    rbuf.pop_back();
    rbuf.pop_back();
    for(auto i : rbuf)
        std::cout << i << " ";

    rbuf.push_back(555);
    rbuf.push_back(666);
    for(auto i : rbuf)
        std::cout << i << " ";
        std::cout << "\n";
    std::cout << "Begin " << *(rbuf.begin()) << "\n";
    std::cout << "Index " << rbuf[1] << "\n";
    std::cout << "End " << *(--rbuf.end()) << "\n";
    return 0;
}