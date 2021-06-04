#pragma once

template<class T, class Alloc = std::allocator<T>>
class CCircular_Buffer {

private:
    T *c_buffer;
    int head = -1;
    int tail = -1;
    unsigned capacity;
    Alloc allocator_;
    using traits = std::allocator_traits<decltype(allocator_)>;
public:
    friend class CIterator;

    explicit CCircular_Buffer(unsigned size) : capacity(size + 1) {
        c_buffer = traits::allocate(allocator_, capacity);
    };

    ~CCircular_Buffer() {
        for (int i = tail;
             i < head; i = (i + 1) % capacity) {
            traits::destroy(allocator_, c_buffer + i);
        }
        traits::deallocate(allocator_, c_buffer, capacity);
    };

    bool full() {
        return (head + 2) % capacity == tail;
    }

    bool empty() {
        if (tail == -1) {
            return true;
        }
        return false;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("Empty Buffer");
        }
        traits::destroy(allocator_, c_buffer + head);
        if (empty()) {
            tail = -1;
            head = -1;
        } else head = (head - 1) % capacity;

    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("Empty Buffer");
        }
        traits::destroy(allocator_, c_buffer + tail);
        if (empty()) {
            tail = -1;
            head = -1;
        } else tail = (tail + 1) % capacity;
    }

    void push_back(const T &element) {
        if (full()) {
            tail = (tail + 1) % capacity;
        }

        if (empty()) {
            tail = (tail + 1) % capacity;
        }
        head = (head + 1) % capacity;
        traits::construct(allocator_, c_buffer + head, element);
    }

    void push_front(const T &element) {
        if (full()) {
            head = (head + 1) % capacity;
        }

        if (empty()) {
            tail = (tail + 1) % capacity;
            head = (head + 1) % capacity;
        } else tail = (tail - 1) % capacity;
        traits::construct(allocator_, c_buffer + tail, element);
    }

    T &operator[](unsigned index) {
        if (index > capacity) {
            throw std::runtime_error("No such index");
        }
        return *(c_buffer + index);
    }

    void reserve(unsigned new_capacity) {
        ++new_capacity;

        if (new_capacity > capacity) {
            T *new_buffer = traits::allocate(allocator_, new_capacity);
            int i = 0;
            int j = tail;
            while (j < (head + 1) % capacity) {
                traits::construct(allocator_, new_buffer + (i++), *(c_buffer + j));
                j = (j + 1) % capacity;
            }
            ~CCircular_Buffer();
            c_buffer = new_buffer;
        }

        if (new_capacity < capacity) {
            throw std::runtime_error("Low Capacity");
        }
    }


    class CIterator
            : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;
        unsigned capacity;
        int position;
    public:
        explicit CIterator(T *current_iterator, unsigned capacity, int position) : ptr(current_iterator), capacity(capacity), position(position){}

        CIterator(const CIterator &other) : ptr(other.ptr), capacity(other.capacity), position(other.position) {}

        CIterator &operator+=(int pos) {
            position = (position + pos) % capacity;
            return *this;
        }

        CIterator &operator-=(int pos) {
            position = (position - pos) % capacity;
            return *this;
        }

        CIterator &operator++() {
            position = (position + 1) % capacity;
            return *this;
        }

        CIterator &operator--() {
            position = (position - 1) % capacity;
            return *this;
        }

        T operator*() const {
            return *(ptr + position);
        }

        T *operator->() const {
            return ptr + position;
        }

        T &operator[](int i) const {
            return ptr[i];
        }

        bool operator>(const CIterator &other) const {
            return position > other.position;
        }

        bool operator<(const CIterator &other) const {
            return position < other.position;
        }

        bool operator>=(const CIterator &other) const {
            return position >= other.position;
        }

        bool operator<=(const CIterator &other) const {
            return position <= other.position;
        }

        bool operator!=(const CIterator &other) const {
            return position != other.position;
        }

        bool operator==(const CIterator &other) const {
            return position == other.position;
        }
    };

    CIterator begin() {
        return CIterator(c_buffer, capacity, tail);
    }

    CIterator end() {
        return CIterator(c_buffer, capacity,  (head + 1) % capacity);
    }
};