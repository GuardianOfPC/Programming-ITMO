#ifndef LAB5_BUFFER_H
#define LAB5_BUFFER_H

template<class T>
class CBuffer {
public:
    explicit Buffer(size_t capacity);

    ~Buffer();

    void push_back(const T& element);
    void push_front(const T& element);

    T pop_back();
    T pop_front();

private:

#endif //LAB5_BUFFER_H
