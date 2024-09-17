#include <iostream>
#include <string>
#include "Shape.h"

using namespace std;

class Rectangle : public Shape {
    private:
        double lenght, width;
    
    public:
        Rectangle(string n, double l, double w);

        double area() const override;

        double getLength() const; 

        double getWidth() const;

        // Setter methods to modify private data
        void setLength(double l);

        void setWidth(double w);
};

Rectangle::Rectangle(string n, double l, double w): Shape(n) {
    lenght = l;
    width = w;
}

double Rectangle::area() const {
    return lenght * width;
}

double Rectangle::getLength() const {
    return lenght;
}

void Rectangle::setLength(double l) {
    if(l > 0)
        lenght = l;
}

void Rectangle::setWidth(double w){
    if(w > 0)
        width = w;
}