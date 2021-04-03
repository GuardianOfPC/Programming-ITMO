#include "Polynom.h"

Polynom::Polynom(index ind): ind(std::move(ind))
{}
Polynom::Polynom() = default;
Polynom::Polynom(const Polynom &other) = default;
Polynom::~Polynom() = default;

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other)
        ind = other.ind;
    return *this;
}

bool operator==(const Polynom& x, const Polynom& y) {
    return x.ind == y.ind;
}

bool operator!=(const Polynom& x, const Polynom& y) {
    return !(x == y);
}

Polynom operator-(Polynom p) {
    for (auto& coefficient: p.ind)
        coefficient.second = -coefficient.second;
    return p;
}

void Polynom::operator+=(const Polynom& other) {
    for (auto other_coefficient: other.ind)
        ind[other_coefficient.first] += other_coefficient.second;
}

void Polynom::operator-=(const Polynom& other) {
    *this += (-other);
}

Polynom Polynom::operator+(const Polynom& other) {
    Polynom result(ind);
    result += other;
    return result;
}

Polynom Polynom::operator-(const Polynom& other) {
    return *this + (-other);
}

double Polynom::operator[](int index) {
    return ind[index];
}

void Polynom::operator*=(double number) {
    for (auto& coefficient : ind)
        coefficient.second *= number;
}

void Polynom::operator*=(const Polynom &other) {
    int key = 0;
    auto result = Polynom();
    for (auto& coefficient: ind)
        for (auto &other_coefficient: other.ind){
            key = coefficient.first + other_coefficient.first;
            result.ind[key] = coefficient.second * other_coefficient.second;
        }
    *this = result;
}

Polynom Polynom::operator*(double num) {
    Polynom p(ind);
    p *= num;
    return p;
}

Polynom Polynom::operator*(const Polynom &other) {
    Polynom p(ind);
    p *= other;
    return p;
}

void Polynom::operator/=(double number) {
    if (number == 0)
        throw std::runtime_error("Error");
    for (auto& coefficient: ind)
        coefficient.second /= number;
}

Polynom Polynom::operator/(double num) {
    Polynom p(ind);
    p /= num;
    return p;
}

void Polynom::print(std::ostream& ostream, std::pair<int, double> coefficient) {
    if (coefficient.second < 0) {
        ostream << '-';
        coefficient.second = -coefficient.second;
    } else {
        ostream << '+';
    }
    ostream << ' ' << coefficient.second << " * x^" << coefficient.first << ' ';
}

std::istream &operator>>(std::istream &istream, Polynom &p) {
    unsigned n_of_coefficients;
    istream >> n_of_coefficients;
    std::pair<int, double> coefficient;
    while (n_of_coefficients--) {
        istream >> coefficient.first;
        istream >> coefficient.second;
        p.ind.emplace(coefficient);
    }
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Polynom &p) {
    auto counter = p.ind.begin();  ////проверка на пустую мапу
    if (p.ind.empty()){
        throw std::runtime_error ("Empty Map");
    }
    std::pair<int, double> ind_first = *counter;
    ostream << ind_first.second << " * x^" << ind_first.first << ' ';
    for (++counter; counter != p.ind.end(); ++counter)
        Polynom::print(ostream, *counter);
    return ostream;
}

int main(){
    Polynom x, y;
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