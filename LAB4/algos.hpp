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
        while (first != last - 1)
            if (!bin_pred(*first, *++first))
                return false;
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
    std::pair<bool, ITERATOR> find_not(ITERATOR first, ITERATOR last, ELEMENT elem) {
        std::pair<bool, ITERATOR> result;
        while (first != last) {
            if (*first != elem) {
                result.first = true;
                result.second = first;
                return result;
            }
            ++first;
        }
        result.first = false;
        return result;
    }

    template<class ITERATOR, class ELEMENT>
    std::pair<bool, ITERATOR> find_backward(ITERATOR first, ITERATOR last, ELEMENT elem) {
        std::pair<bool, ITERATOR> result;
        --last;
        while (first - 1 != last) {
            if (*last == elem) {
                result.first = true;
                result.second = last;
                return result;
            }
            --last;
        }
        result.first = false;
        return result;
    }

    template<class ITERATOR, class BINARY_PRED>
    bool is_palindrome(ITERATOR first, ITERATOR last, BINARY_PRED bin_pred) {
        last--;
        while (true) {
            if (!bin_pred(*first, *last))
                return false;
            ++first;
            if (first == last)
                break;
            --last;
            if (first == last)
                break;
        }
        return true;
    }
}