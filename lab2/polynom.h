#pragma once

#include <iostream>
#include <unordered_map>

template<class T>
class Polynom;

template<class T>
std::istream &operator>>(std::istream &istream, Polynom<T>&p);

template<class T>
std::ostream &operator<<(std::ostream &ostream,const Polynom<T> &p);

template<class T>
class Polynom {
private:
    using index = std::unordered_map<int, T>;
    index ind;

    static void print(std::ostream &ostream, std::pair<int, T> coefficient);

public:
    explicit Polynom(index ind) : ind(std::move(ind)) {}

    Polynom() = default;

    Polynom(const Polynom<T> &other) = default;

    ~Polynom() = default;


    bool operator==(const Polynom<T> &y);

    bool operator!=(const Polynom<T> &y);

    Polynom<T> operator-() const;

    Polynom<T> &operator=(const Polynom<T> &other);

    Polynom<T> operator+(const Polynom<T> &other);

    Polynom<T> operator-(const Polynom<T> &other);

    Polynom<T> operator*(T number);

    Polynom<T> operator*(const Polynom<T> &other);

    Polynom<T> operator/(T number);

    void operator*=(T number);

    void operator*=(const Polynom<T> &other);

    void operator/=(T number);

    void operator+=(const Polynom<T> &other);

    void operator-=(const Polynom<T> &other);

    T &operator[](int index);

    friend std::istream &operator>>(std::istream &istream, Polynom<T> &p) {
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

    friend std::ostream &operator<<(std::ostream &ostream, const Polynom<T> &p) {
        auto counter = p.ind.begin();  ////проверка на пустую мапу
        if (p.ind.empty()) {
            throw std::runtime_error("Empty Map");
        }
        std::pair<int, double> ind_first = *counter;
        ostream << ind_first.second << " * x^" << ind_first.first << ' ';
        for (++counter; counter != p.ind.end(); ++counter)
            Polynom < T > ::print(ostream, *counter);
        return ostream;
    }
};

template<class T>
T operator-(Polynom < T > &p);

template<class T>
Polynom<T> &Polynom<T>::operator=(const Polynom<T> &other) {
    if (this != &other)
        ind = other.ind;
    return *this;
}

template<class T>
bool Polynom<T>::operator==(const Polynom<T> &y) {
    return ind == y.ind;
}

template<class T>
bool Polynom<T>::operator!=(const Polynom<T> &y) {
    return ind != y;
}

template<class T>
Polynom<T> Polynom<T>::operator-() const {
    Polynom<T> n(*this);
    for (auto coef : n.ind) {
        coef.second = -coef.second;
    }
    return n;
}

template<class T>
void Polynom<T>::operator+=(const Polynom<T> &other) {
    for (auto other_coefficient: other.ind)
        ind[other_coefficient.first] += other_coefficient.second;
}

template<class T>
void Polynom<T>::operator-=(const Polynom<T> &other) {
    *this += (-other);
}

template<class T>
Polynom<T> Polynom<T>::operator+(const Polynom<T> &other) {
    Polynom<T> result(ind);
    result += other;
    return result;
}

template<class T>
Polynom<T> Polynom<T>::operator-(const Polynom<T> &other) {
    return *this + (-other);
}

template<class T>
T &Polynom<T>::operator[](int index) {
    return ind[index];
}

template<class T>
void Polynom<T>::operator*=(T number) {
    for (auto &coefficient : ind)
        coefficient.second *= number;
}

template<class T>
void Polynom<T>::operator*=(const Polynom<T> &other) {
    int key;
    Polynom<T> result = Polynom();
    for (auto &coefficient: ind)
        for (auto &other_coefficient: other.ind) {
            key = coefficient.first + other_coefficient.first;
            result.ind[key] = coefficient.second * other_coefficient.second;
        }
    *this = result;
}

template<class T>
Polynom<T> Polynom<T>::operator*(T num) {
    Polynom<T> p(ind);
    p *= num;
    return p;
}

template<class T>
Polynom<T> Polynom<T>::operator*(const Polynom<T> &other) {
    Polynom<T> p(ind);
    p *= other;
    return p;
}

template<class T>
void Polynom<T>::operator/=(T number) {
    if (number == 0)
        throw std::runtime_error("Error");
    for (auto &coefficient: ind)
        coefficient.second /= number;
}

template<class T>
Polynom<T> Polynom<T>::operator/(T num) {
    Polynom<T> p(ind);
    p /= num;
    return p;
}

template<class T>
void Polynom<T>::print(std::ostream &ostream, std::pair<int, T> coefficient) {
    if (coefficient.second < 0) {
        ostream << '-';
        coefficient.second = -coefficient.second;
    } else {
        ostream << '+';
    }
    ostream << ' ' << coefficient.second << " * x^" << coefficient.first << ' ';
}


