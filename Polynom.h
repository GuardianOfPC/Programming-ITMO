#pragma once
#include <iostream>
#include <unordered_map>

class Polynom{
public:
    using index = std::unordered_map<int, double>;
    index ind;

    explicit  Polynom(index ind);
    Polynom();
    Polynom(const Polynom& other);
    ~Polynom();

    Polynom& operator = (const Polynom& other);
    Polynom& operator +(const Polynom& other) const;
    Polynom& operator -(const Polynom& other);
    Polynom& operator *(double number) const;
    Polynom& operator *(const Polynom& other) const;
    Polynom& operator /(double number) const;
    void operator*=(double number);
    void operator*=(const Polynom& other);
    void operator/=(double number);
    void operator+=(const Polynom& other);
    void operator-=(const Polynom& other);
    double operator[](int index);
    friend bool operator ==(const Polynom& x, const Polynom& y);
    friend bool operator !=(const Polynom& x, const Polynom& y);
    friend Polynom operator -(Polynom& z);
    friend std::istream& operator >>(std::istream& istream, Polynom& z);
    friend std::ostream& operator <<(std::ostream& ostream, const Polynom& z);


    static void print(std::ostream &ostream, std::pair<int, double> ind1);
};