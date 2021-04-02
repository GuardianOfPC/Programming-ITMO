#include "polynom.h"
#include <algorithm>


Polynom::Polynom(index ind): ind(std::move(ind))
{};
Polynom::Polynom() = default;
Polynom::Polynom(const Polynom &other) = default;
Polynom::~Polynom() = default;

Polynom& Polynom::operator= (const Polynom& other){
    if (this != &other){
        ind = other.ind;
    }
    return *this;
}
bool operator ==(const Polynom& x, const Polynom& y){
    return x.ind == y.ind;
}

bool operator !=(const Polynom& x, const Polynom& y){
    return !(x == y);
}

Polynom& operator -(Polynom z){
    for(auto& ind: z.ind){
        ind.second = -ind.second;
    }
    return z;
}

Polynom& Polynom::operator -(const Polynom& other){
    return *this + (-other);
}

void Polynom::operator+=(const Polynom& other){
    for (auto other_ind: other.ind){
        ind[other_ind.first] += other_ind.second;
    }
}

void Polynom::operator-=(const Polynom& other){
    *this += (-other);
}

Polynom& Polynom::operator +(const Polynom& other) const{
    Polynom result(ind);
    result += other;
    return result;
}

void Polynom::operator *=(double number){
    for (auto& ind1 : ind){
        ind1.second *= number;
    }
}

void Polynom::operator *= (const Polynom& other){
    for (auto& ind1: ind){
        for (auto other_ind: other.ind){
            ind1.second *= other_ind.second;
        }
    }
}

Polynom& Polynom::operator *(double number) const{
    Polynom z(ind);
    z *= number;
    return z;
}

Polynom& Polynom::operator *(const Polynom& other) const{
    Polynom z(ind);
    z *= other;
    return z;
}

double Polynom::operator [](int index_p){
    return ind[index_p];
}

void Polynom::operator/=(double number){
    if (number == 0){
        throw std::runtime_error("Cannot");
    }
    for (auto& ind1: ind){
        ind1.second /= number;
    }
}

Polynom& Polynom::operator /(double number) const{
    Polynom z(ind);
    z /= number;
    return z;
}

void Polynom::print(std::ostream &ostream, std::pair<int, double> ind1){
    if(ind1.second < 0){
        ostream << '-';
        ind1.second = - ind1.second;
    } else {
        ostream << '+';
    }
    ostream << " " << ind1.second << " * x^" << ind1.first << " ";
}

std::istream &operator >>(std::istream &istream, Polynom &z){
    int ind_count;
    istream >> ind_count;
    std::pair<int, double> ind1;
    while(ind_count--){
        istream >> ind1.first;
        istream >> ind1.second;
        z.ind.emplace(ind1);
    }
    return istream;
}

std::ostream &operator <<(std::ostream &ostream, const Polynom &z){
    auto counter = z.ind.begin();
    std::pair<int, double> first_ind = *counter;
    ostream << first_ind.second << " * x^" << first_ind.first << " ";
    for (++counter; counter != z.ind.end(); ++counter){
        Polynom::print(ostream, *counter);
    }
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
    std::cout << x / 3.4 << "\n";
    std::cout << x << "\n";
    std::cout << y << "\n";
    return 0;
}