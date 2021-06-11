#include <iostream>
#include <algorithm>

#include "circular_buffer.h"

int main() {
    std::cout << "<<<Push_Back test + rewrite>>>" << '\n';
    CCircular_Buffer<int> rbuf1(3);
    rbuf1.push_back(1);
    rbuf1.push_back(2);
    rbuf1.push_back(3);
    rbuf1.push_back(4);
    rbuf1.push_back(5);
    for (const auto i : rbuf1)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << '\n';

    std::cout << "<<<Push_Front test + rewrite>>>" << '\n';
    CCircular_Buffer<int> rbuf2(3);
    rbuf2.push_front(1);
    rbuf2.push_front(2);
    rbuf2.push_front(3);
    rbuf2.push_front(4);
    /*rbuf2.push_front(5);*/
    for (const auto i : rbuf2)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << '\n';

    std::cout << "<<<Pop_Back test + rewrite>>>" << '\n';
    CCircular_Buffer<int> rbuf3(3);
    rbuf3.push_back(1);
    rbuf3.push_back(2);
    rbuf3.push_back(3);
    rbuf3.pop_back();
    rbuf3.pop_back();
    for (const auto i : rbuf3)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << '\n';

    std::cout << "<<<Pop_Front test + rewrite>>>" << '\n';
    CCircular_Buffer<int> rbuf4(3);
    rbuf4.push_back(1);
    rbuf4.push_back(2);
    rbuf4.push_back(3);
    rbuf4.pop_front();
    rbuf4.pop_front();
    for (const auto i : rbuf4)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << '\n';

    std::cout << "<<<Begin, End, index test>>>" << '\n';
    std::cout << '\n';
    CCircular_Buffer<int> result_buffer(3);
    result_buffer.push_back(1);
    result_buffer.push_back(2);
    result_buffer.push_back(3);
    std::cout << "Begin is " << *(result_buffer.begin()) << "\n";
    std::cout << "Second elem is " << result_buffer[1] << "\n";
    std::cout << "End is " << *(--result_buffer.end()) << "\n";
    std::cout << '\n';

    std::cout << "<<<Reserve test>>>" << '\n';
    CCircular_Buffer<int> reserve_buffer(20);
    reserve_buffer.push_back(1);
    reserve_buffer.push_back(2);
    reserve_buffer.push_back(3);
    reserve_buffer.reserve(10);
    for (auto i : reserve_buffer)
        std::cout << i << " ";
    return 0;
}



