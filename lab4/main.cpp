#include <vector>
#include <iostream>

#include "algo.h"

bool is_even(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> test = {5};

    std::cout << "all_of = " << lab::all_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "any_of = " << lab::any_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "none_of = " << lab::none_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "one_of = " << lab::one_of(test.begin(), test.end(), is_even) << '\n';
    std::cout << "is_sorted = " << lab::is_sorted(test.begin(), test.end()) << '\n';
    std::cout << "is partitioned = " << lab::is_partitioned(test.begin(), test.end(), is_even) << '\n';
    if ((lab::find_not(test.begin(), test.end(), 2)) == test.end()) {
        std::cout << "find_not = no elements" << '\n';
    } else std::cout << "find_not = " << *(lab::find_not(test.begin(), test.end(), 2)) << '\n';

    if (((lab::find_backward(test.begin(), test.end(), 2)) == test.begin())) {
        std::cout << "find_backward = no elements" << '\n';
    } else std::cout << "find_backward = " << *(lab::find_backward(test.begin(), test.end(), 2)) << '\n';

    return 0;
}
