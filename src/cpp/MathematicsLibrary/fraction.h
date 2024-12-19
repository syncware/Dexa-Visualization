/*
Copyright(c) 2015 - 2021 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

This software is provided 'as-is', without any express or implied
warranty.In no event will the author be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter itand redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation must be
specified.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice must not be removed or altered from any source distribution.
*/

// #ifndef FRACTION_H
// #define FRACTION_H

#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class fraction
{
    friend ostream &operator<<(ostream &, const fraction &);

public:
    fraction(const int x = 0, const int y = 1);

    // functions performed by class object
    fraction pow(int val) const
    {
        int Num = 1;   // this->num;
        int Denum = 1; // this->denum;

        for (int i = 0; i < val; i++)
        {
            Num *= this->num;
            Denum *= this->denum;
        } // end for

        return fraction(Num, Denum);
    } // end func pow
    int getNumerator() const // get numerator value
    {
        return num;
    } // end func getNumerator
    int getDenominator() const // get numerator value
    {
        return denum;
    } // end func getDenominator
    fraction inverse() const
    {
        return fraction(this->denum, this->num);
    } // end func inverse
    double toDecimal() const
    {
        return double(num) / denum;
    } // end func toDecimal
    string printFraction()
    {
        ostringstream ss;
        if (denum == 1)
        {
            ss << num;
            return ss.str();
        } // end if

        ss << num;
        ss << "/";
        ss << denum;

        return ss.str();
    } // end func printFraction

    // relational operators
    bool operator==(const fraction &) const;     // operator==
    bool operator!=(const fraction &right) const // operator!=
    {
        return !(*this == right);
    } // end func operator!=
    bool operator<(const fraction &) const;     // operator<
    bool operator>(const fraction &right) const // operator>
    {
        return !(*this <= right); // invokes operator <=
    } // end func operator>
    bool operator<=(const fraction &right) const // operator<=
    {
        return !(right < *this); // invokes operator <
    } // end func operator<=
    bool operator>=(const fraction &right) const // operator>=
    {
        return !(*this < right); // invokes operator <
    } // end func operator>=

    bool operator==(const int right) const { return *this == fraction(right); }
    bool operator!=(const int right) const { return *this != fraction(right); }
    bool operator<(const int right) const { return *this < fraction(right); }
    bool operator>(const int right) const { return *this > fraction(right); }
    bool operator<=(const int right) const { return *this <= fraction(right); }
    bool operator>=(const int right) const { return *this >= fraction(right); }

    // calculational operators
    fraction operator+(const fraction &) const; // operator+, f1 + f2
    fraction operator+(int) const;              // operator+, f1 + f2
    fraction operator-(const fraction &) const; // operator-, f1 - f2
    fraction operator-(int) const;              // operator-, f1 - f2
    fraction operator*(const fraction &) const; // operator*, f1 * f2
    fraction operator*(int) const;              // operator*, f1 * f2
    fraction operator/(const fraction &) const; // operator/, f1 / f2
    fraction operator/(int) const;              // operator/, f1 / f2

    const fraction &operator=(const fraction &f) // assignment operator
    {
        this->num = f.getNumerator();
        this->denum = f.getDenominator();
        return *this;
    } // end func operator=
    const fraction &operator*=(const fraction &f) // f1*=f2
    {
        *this = *this * f;
        return *this;
    } // end operator*=
    const fraction &operator*=(int val) // s1*=2
    {
        *this = *this * val;
        return *this;
    } // end operator*=
    const fraction &operator/=(const fraction &f) // f1/=f2
    {
        *this = *this / f;
        return *this;
    } // end operator/=
    const fraction &operator/=(int val) // s1/=2
    {
        *this = *this / val;
        return *this;
    } // end operator/=
    const fraction &operator+=(const fraction &f) // s1+=s2
    {
        *this = *this + f;
        return *this;
    } // end operator+=
    const fraction &operator+=(int val) // s1+=2
    {
        *this = *this + val;
        return *this;
    } // end operator+=
    const fraction &operator-=(const fraction &f) // s1-=s2
    {
        *this = *this - f;
        return *this;
    } // end operator-=
    const fraction &operator-=(int val) // s1-=2
    {
        *this = *this - val;
        return *this;
    } // end operator

    // prefix operator
    fraction &operator++()
    {
        *this = *this + 1;
        return *this;
    } // end func operator++
    fraction &operator--()
    {
        *this = *this - 1;
        return *this;
    } // end func operator--

    // postfix operator
    fraction operator++(int)
    {
        *this = *this + 1;
        return *this;
    } // end func operator++
    fraction operator--(int)
    {
        *this = *this - 1;
        return *this;
    } // end func operator--

public:
    int num;   // holds the numerator
    int denum; // holds the denuminator

    unsigned int GCD(unsigned int x, unsigned int y)
    {
        // simple cases (termination)
        if (x == y)
            return x;
        if (x == 0)
            return y;
        if (y == 0)
            return x;

        // look for factors of 2
        if (~x & 1) // x is even
        {
            if (y & 1) // y is odd
                return GCD(x >> 1, y);
            else // both x and y are even
                return GCD(x >> 1, y >> 1) << 1;
        } // end if

        if (~y & 1) // x is odd, y is even
            return GCD(x, y >> 1);

        // reduce larger argument
        if (x > y)
            return GCD((x - y) >> 1, y);

        return GCD((y - x) >> 1, x);
    } // end func GCD

}; // end class fraction

// #endif // FRACTION_H

fraction::fraction(int x, int y)
    : num(x), denum(y)
{
    if (denum == 0)
        throw std::invalid_argument("zero division");

    bool isNegative = false;
    register unsigned int chk;

    // Check if numerator is negative and strip it off for now
    if (num < 0)
    {
        isNegative = true;
        num = ~num + 1;
        // num *= -1;
    } // end if
    if (denum < 0)
    {
        if (isNegative)
            isNegative = false;
        else
            isNegative = true;
        denum = ~denum + 1;
        // denum *= -1;
    } // end if

    chk = GCD(num, denum);
    do
    {
        num = num / chk;
        denum = denum / chk;
        chk = GCD(num, denum);
    } while (chk != 1 && chk != num && chk != denum);

    // if numerator was originally negative put it back
    if (isNegative)
        num = ~num + 1;
    // num *= -1;
} // end constructor

// operator functions declarations
//
bool fraction::operator==(const fraction &f) const
{
    if (f.getNumerator() != this->num || f.getDenominator() != this->denum)
        return false;
    return true;
} // end func operator==

bool fraction::operator<(const fraction &f) const
{
    double temp = double(num) / denum;
    double temp2 = double(f.getNumerator()) / f.getDenominator();
    if (temp < temp2)
        return true;
    return false;
} // end func operator<

fraction fraction::operator+(const fraction &f) const // operator+, f1 + f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction((this->num * fDenum) + (fNum * this->denum), this->denum * fDenum);
} // end func operator+

fraction fraction::operator+(int i) const // operator+, f1 + f2
{
    fraction temp_frac(i);
    return *this + temp_frac;
} // end func operator+

fraction fraction::operator-(const fraction &f) const // operator-, f1 - f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction((this->num * fDenum) - (fNum * this->denum), this->denum * fDenum);
} // end func operator-

fraction fraction::operator-(int i) const // operator-, f1 - f2
{
    fraction temp_frac(i);
    return *this - temp_frac;
} // end func operator-

fraction fraction::operator*(const fraction &f) const // operator*, f1 * f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction(this->num * fNum, this->denum * fDenum);
} // end operator*

fraction fraction::operator*(int i) const // operator*, f1 * f2
{
    fraction temp_frac(i);
    return *this * temp_frac;
} // end operator*

fraction fraction::operator/(const fraction &f) const // operator/, f1 / f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction(this->num * fDenum, fNum * this->denum);
} // end operator /

fraction fraction::operator/(int i) const // operator/, f1 / f2
{
    fraction temp_frac(i);
    return *this / temp_frac;
} // end operator /

ostream &operator<<(ostream &output, const fraction &f)
{
    int num = f.getNumerator();
    int denum = f.getDenominator();

    if (denum == 1)
        output << num;
    else
        output << num << "/" << denum;

    return output; // enables cout << a << b << c;
} // end function operator<<