#include <iostream>
#include <vector>

#include "algos.h"

bool is_even(int num) {
    return num % 2 == 0;
}

template<typename T>
bool comparator(const T& first, const T& second){
    return first == second;
}

int main() {
    std::vector<int> test = {1, 2, 3, 2, 1};

    std::cout << "all_of = " << lab::all_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "any_of = " << lab::any_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "none_of = " << lab::none_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "one_of = " << lab::one_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "is_sorted = " << lab::is_sorted(test.begin(), test.end(), comparator<int>) << '\n';
    std::cout << "is partitioned = " << lab::is_partitioned(test.begin(), test.end(), is_even) << '\n';
    std::cout << "find_not = " << *(lab::find_not(test.begin(), test.end(), 2)) << '\n';
    std::cout << "find_backward = " << *(lab::find_backward(test.begin(), test.end(), 2)) << '\n';
    std::cout << "is_palindrome = " << lab::is_palindrome(test.begin(), test.end(), comparator<char>) << '\n';

    return 0;
}
