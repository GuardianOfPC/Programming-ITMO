#include <iostream>
#include <vector>

#include "algos.h"

bool is_even(int num) {
    return num % 2 == 0;
}


int main() {
    std::vector<int> test = {1, 2, 3, 2, 1};

    lab::all_of(test.begin(), test.end(), is_even);

    return 0;
}
