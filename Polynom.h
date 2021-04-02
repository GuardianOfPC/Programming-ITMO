#pragma once

#include <iostream>
#include <unordered_map>
using index = std::unordered_map<int, double>;

class Polynom {
private:
    index ind;
    static void print(std::ostream &ostream, std::pair<int, double> coefficient);
public:
    explicit Polynom(index ind);
    Polynom();
    Polynom(const Polynom& other);
    ~Polynom();


    friend bool operator==(const Polynom& x, const Polynom& y);
    friend bool operator!=(const Polynom& x, const Polynom& y);
    friend Polynom operator-(Polynom p);
    friend std::istream& operator>>(std::istream& istream, Polynom& p);
    friend std::ostream& operator<<(std::ostream& ostream, const Polynom& p);
    Polynom& operator=(const Polynom& other);
    Polynom operator+(const Polynom& other);
    Polynom operator-(const Polynom& other);
    Polynom operator*(double number);
    Polynom operator*(const Polynom& other);
    Polynom operator/(double number);
    void operator*=(double number);
    void operator*=(const Polynom& other);
    void operator/=(double number);
    void operator+=(const Polynom& other);
    void operator-=(const Polynom& other);
    double operator[](int index);
};

bool operator==(const Polynom& x, const Polynom& y);
bool operator!=(const Polynom& x, const Polynom& y);
Polynom operator-(Polynom& p);
std::istream& operator>>(std::istream& istream, Polynom& p);
std::ostream& operator<<(std::ostream& ostream, const Polynom& p);