#pragma once

namespace lab {
    template<typename ITERATOR, typename UNARY_PRED>
    bool all_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred);

    template<typename ITERATOR, typename UNARY_PRED>
    bool any_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred);

    template<typename ITERATOR, typename UNARY_PRED>
    bool none_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred);

    template<typename ITERATOR, typename UNARY_PRED>
    bool one_of(ITERATOR first, ITERATOR last, UNARY_PRED un_pred);

    template<typename ITERATOR, typename BINARY_PRED>
    bool is_sorted(ITERATOR first, ITERATOR last, BINARY_PRED bin_pred);

    template<typename ITERATOR, typename UNARY_PRED>
    bool is_partitioned(ITERATOR first, ITERATOR last, UNARY_PRED un_pred);

    template<typename ITERATOR, typename ELEMENT>
    std::pair<bool, ITERATOR> find_not(ITERATOR first, ITERATOR last, ELEMENT elem);

    template<typename ITERATOR, typename ELEMENT>
    std::pair<bool, ITERATOR> find_backward(ITERATOR first, ITERATOR last, ELEMENT elem);

    template<typename ITERATOR, typename BINARY_PRED>
    bool is_palindrome(ITERATOR first, ITERATOR last, BINARY_PRED bin_pred);
}

#include "algos.hpp"

