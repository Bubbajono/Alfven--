#include "Vec2D.h"
#include <math.h>

Vec2D::Vec2D(double a, double b)
{
    this->a = a;
    this->b = b;
}

double Vec2D::Normalise()
{
    return sqrt(a*a+b*b);
}

void Vec2D::Print()
{
    std::cout<< "a = " << a << ", b = " << b <<std::endl;
}