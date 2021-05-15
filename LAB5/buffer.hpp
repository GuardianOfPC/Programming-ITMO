#ifndef LAB5_BUFFER_HPP
#define LAB5_BUFFER_HPP

template<class T>
void Buffer<T>::push_back(const T& element) {
    buffer[tail] = element;
}

template<class T>
void Buffer<T>::push_front(const T& element) {
    buffer[head] = element;
}


#include "RingBuffer.hpp"
#endif //LAB5_BUFFER_HPP
