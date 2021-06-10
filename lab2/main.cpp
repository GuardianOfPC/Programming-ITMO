#include "polynom.h"

int main() {
    Polynom<int> x, y;
    std::cin >> x;
    std::cout << x << "\n";
    std::cin >> y;
    std::cout << y << "\n" << "\n";
    std::cout << x + y << "\n";
    std::cout << x - y << "\n";
    std::cout << x * y << "\n";
    std::cout << x / 5 << "\n";
    std::cout << x << "\n";
    std::cout << y << "\n";
    return 0;
}