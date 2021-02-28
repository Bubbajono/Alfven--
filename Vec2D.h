#include <iostream>
#include <vector>
#ifndef VEC2D_H // include guard
#define VEC2D_H

class Vec2D
{
    public:
        double a, b;
        Vec2D(double a, double b);
        double Normalise();
        void Print();
};

#endif