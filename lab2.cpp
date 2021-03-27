#include <iostream>
#include <unordered_map>

using cof = std::unordered_map<int, double>;

class Polynom{
private:
    cof coeff;
public:
    explicit  Polynom(cof coeff);
    Polynom();
    Polynom(const Polynom& other);
    ~Polynom();

    Polynom& operator = (const Polynom& other);
    friend bool operator ==(const Polynom& x, const Polynom& y);
    friend bool operator !=(const Polynom& x, const Polynom& y);
    friend Polynom operator -(Polynom& z);
    Polynom& operator +(const Polynom& other);
    Polynom& operator -(const Polynom& other);
    Polynom& operator *(double number);
    Polynom& operator *(const Polynom& other);
    Polynom& operator /(double number);
    friend std::istream& operator >>(std::istream& istream, Polynom& z);
    friend std::ostream& operator <<(std::ostream& ostream, const Polynom& z);
    void operator*=(double number);
    void operator*=(const Polynom& other);
    void operator/=(double number);
    void operator+=(const Polynom& other);
    void operator-=(const Polynom& other);
    double operator[](int index);
};

bool operator ==(const Polynom& x, const Polynom& y);
bool operator !=(const Polynom& x, const Polynom& y);
Polynom operator -(Polynom& z);
std::istream& operator>>(std::istream& istream, Polynom& z);
std::ostream& operator<<(std::ostream& ostream, const Polynom& z);



Polynom::Polynom(cof coeff): coeff(std::move(coeff))
{};

Polynom::Polynom() = default;

bool operator ==(const Polynom& x, const Polynom& y){
    return x.coeff == y.coeff;
}

bool operator !=(const Polynom& x, const Polynom& y){
    return !(x == y);
}

Polynom operator -(Polynom z){
    for(auto &coeff: z.coeff){
        coeff.second = -coeff.second;
    }
    return z;
}

double Polynom::operator [](int index){
    return coeff[index];
}

void Polynom::operator/=(double number){
    if (number == 0){
        throw std::runtime_error("Cannot");
    }
    for (auto& coeff: coeff){
        coeff.second /= number;
    }
}

Polynom Polynom::operator/(double number){
    Polynom z(coeff);
    z /= number;
    return z;
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
    std::cout << y << "\n";    return 0;
}