#include <iostream>
#include <vector>
#include "Stencil.h"
#ifndef LAPLACE_H // include guard
#define LAPLACE_H

class Laplace
{
    std::vector<std::vector<int>> U;
    int L;
    public:
        Laplace(int L = 50);
        Laplace(Stencil stencil);
    private:
        void InstantiateVector();
        void SetInitialConditions();
        void SimpleSolve(int nIterations = 1);
};  

#endif