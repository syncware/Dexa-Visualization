#include <iostream>
#include <string>
#include <cmath>
#include "Shape.h"

using namespace std;

class Circle : public Shape
{

private:
    double radius;

public:
    Circle(string n, double r);

    double area() const override;
};

Circle::Circle(string n, double r) : Shape(n)
{
    radius = r;
}

double Circle::area() const
{
    return (22.0 / 7.0) * radius * radius;
}