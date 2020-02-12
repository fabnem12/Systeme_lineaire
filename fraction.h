#ifndef DEF_FRACTION
#define DEF_FRACTION

#include <iostream>

class Fraction {
private:
    int _numerateur;
    int _denominateur;
public:
    Fraction(int num = 0, int denom = 1);

    void simplifie();
    Fraction operator++(int increment = 1);
    Fraction operator--(int decrement = 1);
    void operator+=(Fraction autre);
    void operator-=(Fraction autre);
    void operator*=(Fraction autre);
    void operator/=(Fraction autre);
    Fraction operator*(Fraction autre);
    Fraction operator+(Fraction autre);
    Fraction operator-(Fraction autre);
    Fraction operator/(Fraction autre);

    bool operator==(int compare);
    bool operator!=(int compare) { return !operator==(compare); }

    int numerateur() { return _numerateur; }
    int denominateur() { return _denominateur; }

    Fraction& operator= (const int& x) { return *this; }
};

std::ostream& operator<<(std::ostream& os, Fraction fraction);

std::string to_string(Fraction& fraction);

#endif
