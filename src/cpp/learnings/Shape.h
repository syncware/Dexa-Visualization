#pragma once

#ifndef SHAPE_H
#define SHAPE_H
#endif

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Base class (Parent class)
class Shape
{
protected:
    string name;

public:
    Shape(string n);

    void setName(string n);

    string getName() const;

    virtual double area() const;
};

Shape::Shape(string n)
{
    name = n;
}

void Shape::setName(string n)
{
    name = n;
}

string Shape::getName() const
{
    return name;
}

double Shape::area() const
{
    return 0.0;
}