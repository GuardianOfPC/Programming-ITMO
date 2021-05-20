namespace lab {
    template<class ITERATOR, class UNARY_PRED>
    bool all_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred) {
        while (first != last) {
            if (!un_pred(*first))
                return false;
            ++first;
        }
        return true;
    }

    template<class ITERATOR, class UNARY_PRED>
    bool any_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred) {
        while (first != last) {
            if (un_pred(*first))
                return true;
            ++first;
        }
        return false;
    }

    template<class ITERATOR, class UNARY_PRED>
    bool none_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred) {
        while (first != last) {
            if (un_pred(*first))
                return false;
            ++first;
        }
        return true;
    }

    template<class ITERATOR, class UNARY_PRED>
    bool one_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred) {
        bool one_found = false;
        while (first != last) {
            if (un_pred(*first)) {
                if (one_found)
                    return false;
                one_found = true;
            }
            ++first;
        }
        return one_found;
    }

    template<class ITERATOR, class BINARY_PRED>
    bool is_sorted(ITERATOR first, ITERATOR last, BINARY_PRED bin_pred) {
        if (first == last)
            return true;
        last--;
        ITERATOR previous;
        while (first != last) {
            previous = first;
            ++first;
            if (!bin_pred(*previous, *first))
                return false;
        }
        return true;
    }

    template<class ITERATOR, class UNARY_PRED>
    bool is_partitioned(ITERATOR first, ITERATOR last, UNARY_PRED un_pred) {
        for (; first != last; ++first)
            if (!un_pred(*first))
                break;
        for (; first != last; ++first)
            if (un_pred(*first))
                return false;
        return true;
    }

    template<class ITERATOR, class ELEMENT>
    ITERATOR find_not(ITERATOR first, ITERATOR last, ELEMENT elem) {
        while (first != last) {
            if (*first != elem)
                return first;
            ++first;
        }
        return last;
    }

    template<class ITERATOR, class ELEMENT>
    ITERATOR find_backward(ITERATOR first, ITERATOR last, ELEMENT elem) {
        ITERATOR not_found(last);
        while (first != last) {
            --last;
            if (*last == elem)
                return last;
        }
        return not_found;
    }

    template<class ITERATOR, class BINARY_PRED>
    bool is_palindrome(ITERATOR first, ITERATOR last, BINARY_PRED bin_pred) {
        while (first != last) {
            --last;
            if (last == first)
                break;
            if (!bin_pred(*first, *last))
                return false;
            first++;
        }
        return true;
    }
}