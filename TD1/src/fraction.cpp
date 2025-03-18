#include "fraction.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>

std::ostream& operator<<(std::ostream& os, Fraction const& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}


Fraction& Fraction::operator+=(Fraction const& f) {
    numerator = numerator * f.denominator + f.numerator * denominator;
    denominator = denominator * f.denominator;

    *this = simplify(*this);

    return *this;
}

Fraction& Fraction::operator-=(Fraction const& f) {
    numerator = numerator * f.denominator - f.numerator * denominator;
    denominator = denominator * f.denominator;

    *this = simplify(*this);
    return *this;
}

Fraction& Fraction::operator*=(Fraction const& f) {
    numerator = numerator * f.numerator;
    denominator = denominator * f.denominator;

    *this = simplify(*this);

    return *this;
}

Fraction& Fraction::operator/=(Fraction const& f) {
    numerator = numerator * f.denominator;
    denominator = denominator * f.numerator;

    *this = simplify(*this); 

    return *this;
}

Fraction operator+(Fraction f1, Fraction const& f2)
{
    return (f1 += f2);
}

Fraction operator-(Fraction f1, Fraction const& f2)
{
    return (f1 -= f2);
}

Fraction operator*(Fraction f1, Fraction const& f2)
{
    return (f1 *= f2);
}

Fraction operator/(Fraction f1, Fraction const& f2)
{
    return (f1 /= f2);
}

//Ancien opérateur +
// Fraction operator+(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }

// Fraction add(Fraction const& f1, Fraction const& f2) {
//     Fraction result {
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator
//         f1.denominator * f2.denominator
//     };

//     return simplify(result);
// }

//Ancien opérateur -
// Fraction operator-(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator - f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }


//Ancien opérateur *
// Fraction operator*(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.numerator,
//         f1.denominator * f2.denominator
//     });
// }


//Ancien opérateur /
// Fraction operator/(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator,
//         f1.denominator * f2.numerator
//     });
// }


bool operator==(Fraction const& f1, Fraction const& f2)  {
    return f1.numerator * f2.denominator == f1.denominator * f2.numerator;

}


bool operator!=(Fraction const& f1, Fraction const& f2)  {
    return !(f1 == f2);

}

bool operator<(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator < f1.denominator * f2.numerator;
}

bool operator<=(Fraction const& f1, Fraction const& f2) {
    return f1 < f2 || f1 == f2;  
}

bool operator>(Fraction const& f1, Fraction const& f2) {
    return !(f1 < f2 || f1 == f2);  
}

bool operator>=(Fraction const& f1, Fraction const& f2) {
    return !(f1 < f2);  
}

//convertir en float :

float Fraction::to_float() const {
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

Fraction::operator float() const {
    return to_float();

}





//operation fraction/int : 

//Première étape :: gérer les signes : 

Fraction::Fraction(int num, int den) {
    if (den == 0) {
        throw std::invalid_argument("Division par 0");
    }
    // mettre le signe au numérateur
    if (den < 0) {
        num = -num;
        den = -den;
    }
    numerator = num;
    denominator = den;
}


// Opérateurs avec int
Fraction operator+(Fraction const& f, int i) { return f + Fraction(i); }
Fraction operator+(int i, Fraction const& f) { return f + i; }
Fraction operator-(Fraction const& f, int i) { return f - Fraction(i); }
Fraction operator-(int i, Fraction const& f) { return Fraction(i) - f; }
Fraction operator*(Fraction const& f, int i) { return Fraction(f.numerator * i, f.denominator); }
Fraction operator*(int i, Fraction const& f) { return f * i; }
Fraction operator/(Fraction const& f, int i) {
    if (i == 0) throw std::invalid_argument("Division par 0 !");
    return Fraction(f.numerator, f.denominator * i);
}
Fraction operator/(int i, Fraction const& f) {
    if (f.numerator == 0) throw std::invalid_argument("Division par 0 !");
    return Fraction(i * f.denominator, f.numerator);
}


Fraction abs(Fraction const& f) { return Fraction(std::abs(f.numerator), f.denominator); }
int ceil(Fraction const& f) { return std::ceil(f.to_float()); }
int floor(Fraction const& f) { return std::floor(f.to_float()); }
int round(Fraction const& f) { return std::round(f.to_float()); }
