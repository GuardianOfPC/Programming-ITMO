#pragma once

namespace lab {
    template<class InputIterator, class UnaryPredicate>
    bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (!pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (pred(*first)) return true;
            ++first;
        }
        return false;
    }

    template<class InputIterator, class UnaryPredicate>
    bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last) {
            if (pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool one_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
        bool one_found = false;
        while (first != last) {
            if (pred(*first)) {
                if (one_found)
                    return false;
                one_found = true;
            }
            ++first;
        }
        return one_found;
    }

    template<class ForwardIterator>
    bool is_sorted(ForwardIterator first, ForwardIterator last) {
        if (first == last) return true;
        ForwardIterator next = first;
        while (++next != last) {
            if (*next < *first)   // or, if (comp(*next,*first)) for version (2)
                return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class UnaryPredicate>
    bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate pred) {
        while (first != last && pred(*first)) {
            ++first;
        }
        while (first != last) {
            if (pred(*first)) return false;
            ++first;
        }
        return true;
    }

    template<class InputIterator, class T>
    InputIterator find_not(InputIterator first, InputIterator last, const T &val) {
        while (first != last) {
            if (*first != val) return first;
            ++first;
        }
        return last;
    }

    template<class InputIterator, class T>
    InputIterator find_backward(InputIterator first, InputIterator last, const T &val) {
        while (last != first) {
            if (*(--last) == val) return last;
        }
        return first;
    }
}