#include <iostream>

template<class Input, class Predicate>
bool all_of(Input first, Input last, Predicate upred) {
    while (first != last) {
        if (!upred(*first))
            return false;
        ++first;
    }
    return true;
}

template<class Input, class Predicate>
bool any_of(Input first, Input last, Predicate upred) {
    while (first != last) {
        if (upred(*first))
            return true;
        ++first;
    }
    return false;
}


int main() {
}
