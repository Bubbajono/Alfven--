#include <iostream>
#include <vector>
#include "StencilType.cpp"
#include "System.h"
#include "../packages/eigen/Eigen/SparseCore"
#ifndef STENCIL_H // include guard
#define STENCIL_H

class Stencil
{
    Eigen::SparseMatrix<double> M;
    StencilType Type;
    System Sys;
    public:
        Stencil(StencilType Type, System sys);
    private:
        void MatrixAllocationReserving();
        void Generate();
    
};  

#endif