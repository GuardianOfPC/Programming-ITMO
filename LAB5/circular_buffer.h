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
            traits::destroy(allocator_, c_buffer + tail);
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
            traits::destroy(allocator_, c_buffer + head);
            head = (head - 1) % capacity;
        }

        if (empty()) {
            tail = (tail + 1) % capacity;
            head = (head + 1) % capacity;
        } else tail = (tail - 1) % capacity;
        traits::construct(allocator_, c_buffer + tail, element);
    }

    T &operator[](int index) {
        if (index > capacity) {
            throw std::runtime_error("No such index");
        }
        return *(c_buffer + (tail + index) % capacity);
    }

    const T &operator[](int index) const {
        if (index > capacity) {
            throw std::runtime_error("No such index");
        }
        return *(c_buffer + (tail + index) % capacity);
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

    int size() {
        if (full()) {
            return capacity - 1;
        }

        if (empty()) {
            return 0;
        }

        if (tail <= head) {
            return head - tail + 1;
        } else return capacity - head + tail + 1;
    }

    class CIterator
            : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;
        unsigned capacity;
        int position;
        int begin_point;
    public:
        explicit CIterator(T *current_iterator, unsigned capacity, int position, int begin_p) : ptr(current_iterator),
                                                                                                capacity(capacity),
                                                                                                position(position),
                                                                                                begin_point(begin_p) {}

        CIterator(const CIterator &other) : ptr(other.ptr), capacity(other.capacity), position(other.position),
                                            begin_point(other.begin_point) {}

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

        T &operator*() const {
            return *(ptr + (begin_point + position) % capacity);
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
        return CIterator(c_buffer, capacity, 0, tail);
    }

    CIterator end() {
        return CIterator(c_buffer, capacity, size(), tail);
    }

    class Const_CIterator
            : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;
        unsigned capacity;
        int position;
        int begin_point;
    public:
        explicit Const_CIterator(T *current_iterator, unsigned capacity, int position, int begin_p) : ptr(current_iterator),
                                                                                                      capacity(capacity),
                                                                                                      position(position),
                                                                                                      begin_point(begin_p) {}

        Const_CIterator(const Const_CIterator &other) : ptr(other.ptr), capacity(other.capacity),
                                                        position(other.position),
                                                        begin_point(other.begin_point) {}

        Const_CIterator &operator+=(int pos) {
            position = (position + pos) % capacity;
            return *this;
        }

        Const_CIterator &operator-=(int pos) {
            position = (position - pos) % capacity;
            return *this;
        }

        Const_CIterator &operator++() {
            position = (position + 1) % capacity;
            return *this;
        }

        Const_CIterator &operator--() {
            position = (position - 1) % capacity;
            return *this;
        }

        const T &operator*() const {
            return *(ptr + (begin_point + position) % capacity);
        }

        T *operator->() const {
            return ptr + position;
        }

        T &operator[](int i) const {
            return ptr[i];
        }

        bool operator>(const Const_CIterator &other) const {
            return position > other.position;
        }

        bool operator<(const Const_CIterator &other) const {
            return position < other.position;
        }

        bool operator>=(const Const_CIterator &other) const {
            return position >= other.position;
        }

        bool operator<=(const Const_CIterator &other) const {
            return position <= other.position;
        }

        bool operator!=(const Const_CIterator &other) const {
            return position != other.position;
        }

        bool operator==(const Const_CIterator &other) const {
            return position == other.position;
        }
    };

    Const_CIterator begin() const {
        return Const_CIterator(c_buffer, capacity, 0, tail);
    }

    Const_CIterator end() const {
        return Const_CIterator(c_buffer, capacity, size(), tail);
    }
};