#include "Stencil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../packages/eigen/Eigen/SparseCore"

Stencil::Stencil(StencilType Type, System Sys)
{
    this->Type = Type;
    this->Sys = Sys;
    M.resize(Sys.L, Sys.L);
    this->MatrixAllocationReserving();
    this->Generate();
}

void Stencil::MatrixAllocationReserving()
{
    switch (Type)
    {
        case Laplacian:
            //Reserve with expectation for 1-1-4-1-1 stencil for each point. (Overestimation)
            M.reserve(5 * Sys.L * Sys.L);
            break;
        default:
            std::cout<<"No stencil type selected";
            break;
    }
}

void Stencil::Generate()
{
    for (int i = 0; i < Sys.Np; i++)
    {
        Vec2D VecIJ = Sys.GridArrayP[i];
        double mid = Sys.GridArrayIJ[VecIJ.a][VecIJ.b];

        M.coeffRef(i,i) = -4;

        //Upper hand of stencil
        double up = Sys.GridArrayIJ[VecIJ.a + 1][VecIJ.b];
        if (up >= 0)
        {
            M.coeffRef(i + 1, i) = 1;
        }
        //bottom hand of stencil
        double bottom = Sys.GridArrayIJ[VecIJ.a - 1][VecIJ.b];
        if (bottom >= 0)
        {
            M.coeffRef(i - 1, i) = 1;
        }
        //Left hand of stencil
        double left = Sys.GridArrayIJ[VecIJ.a][VecIJ.b - 1];
        if (left >= 0)
        {
            M.coeffRef(i, i - 1) = 1;
        }
        //right hand of stencil
        double right = Sys.GridArrayIJ[VecIJ.a][VecIJ.b + 1];
        if (right >= 0)
        {
            M.coeffRef(i, i + 1) = 1;           
        }

        
    }
    M.makeCompressed();
}
