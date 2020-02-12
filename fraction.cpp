#include "fraction.h"

int pgcd(int a, int b) {
    int r;

    do {
        r = a % b;
        a = b;
        b = r;
    } while (r != 0);

    return a;
}

int ppcm(int a, int b) {
    return a * b / pgcd(a, b);
}

std::ostream& operator<<(std::ostream& os, Fraction fraction) {
    os << to_string(fraction);
    return os;
}

std::string to_string(Fraction& fraction) {
    if (fraction.denominateur() != 1)
        return std::to_string(fraction.numerateur()) + " / " + std::to_string(fraction.denominateur());
    else
        return std::to_string(fraction.numerateur());
}

Fraction::Fraction(int numerateur, int denominateur) {
    _numerateur = numerateur;
    _denominateur = denominateur;

    simplifie();
}

void Fraction::simplifie() {
    int divisePar = pgcd(_numerateur, _denominateur);
    if (divisePar != 1) {
        _numerateur /= divisePar;
        _denominateur /= divisePar;
    }
}

Fraction Fraction::operator++(int increment) {
    _numerateur += _denominateur * increment;
    return *this;
}

Fraction Fraction::operator--(int decrement) {
    _numerateur -= _denominateur * decrement;
    return *this;
}

void Fraction::operator+=(Fraction autre) {
    int ppcmDenoms = ppcm(_denominateur, autre.denominateur());

    _numerateur = _numerateur * ppcmDenoms/_denominateur + autre.numerateur() * ppcmDenoms/autre.denominateur();
    _denominateur = ppcmDenoms;

    simplifie();
}

void Fraction::operator-=(Fraction autre) {
    Fraction newAutre = Fraction(-autre.numerateur(), autre.denominateur());
    operator+=(newAutre);
}

void Fraction::operator*=(Fraction autre) {
    _numerateur *= autre.numerateur();
    _denominateur *= autre.denominateur();

    simplifie();
}

void Fraction::operator/=(Fraction autre) {
    _numerateur /= autre.numerateur();
    _denominateur /= autre.denominateur();

    simplifie();
}

Fraction Fraction::operator+(Fraction autre) {
    int ppcmDenoms = ppcm(_denominateur, autre.denominateur());

    int numNew = _numerateur * ppcmDenoms/_denominateur + autre.numerateur() * ppcmDenoms/autre.denominateur();
    int denomNew = ppcmDenoms;

    return Fraction(numNew, denomNew);
}

Fraction Fraction::operator-(Fraction autre) {
    return operator+(autre*-1);
}

Fraction Fraction::operator*(Fraction autre) {
    return Fraction(_numerateur * autre.numerateur(), _denominateur * autre.denominateur());
}

Fraction Fraction::operator/(Fraction autre) {
    return Fraction(_numerateur / autre.denominateur(), _denominateur / autre.denominateur());
}

bool Fraction::operator==(int compare) {
    if (_numerateur == 0 && compare == 0) return true;

    if (pgcd(_numerateur, _denominateur) == _denominateur) //c'est un entier
        return (_numerateur / _denominateur == compare);
    else if (_numerateur == 0)
        return (compare == 0);
    else
        return false;
}
