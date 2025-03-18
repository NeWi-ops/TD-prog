#pragma once
#include <iostream>

struct Fraction {
    // unsigned int numerator;
    // unsigned int denominator;

    int numerator;
    int denominator;

    Fraction(int num, int den);
    Fraction(int num) : numerator(num), denominator(1) {} // Nouveau constructeur pour int


    Fraction& operator+=(Fraction const& f);
    Fraction& operator-=(Fraction const& f);
    Fraction& operator*=(Fraction const& f);
    Fraction& operator/=(Fraction const& f);

    float to_float() const;
    operator float() const;
};

std::ostream& operator<<(std::ostream& os, Fraction const& f);

Fraction operator+(Fraction f1, Fraction const& f2);
Fraction operator-(Fraction f1, Fraction const& f2);
Fraction operator*(Fraction f1, Fraction const& f2);
Fraction operator/(Fraction f1, Fraction const& f2);

// Fraction operator+(Fraction const& f1, Fraction const& f2);
// Fraction operator-(Fraction const& f1, Fraction const& f2);
// Fraction operator*(Fraction const& f1, Fraction const& f2);
// Fraction operator/(Fraction const& f1, Fraction const& f2);


bool operator==(Fraction const& f1, Fraction const& f2);
bool operator!=(Fraction const& f1, Fraction const& f2);

bool operator<(Fraction const& f1, Fraction const& f2);
bool operator<=(Fraction const& f1, Fraction const& f2); 
bool operator>(Fraction const& f1, Fraction const& f2); 
bool operator>=(Fraction const& f1, Fraction const& f2); 

// opérateurs entre fraction et int
Fraction operator+(Fraction const& f, int i);
Fraction operator+(int i, Fraction const& f);

Fraction operator-(Fraction const& f, int i);
Fraction operator-(int i, Fraction const& f);

Fraction operator*(Fraction const& f, int i);
Fraction operator*(int i, Fraction const& f);

Fraction operator/(Fraction const& f, int i);
Fraction operator/(int i, Fraction const& f);

Fraction abs(Fraction const& f);
int ceil(Fraction const& f);
int floor(Fraction const& f);
int round(Fraction const& f);
