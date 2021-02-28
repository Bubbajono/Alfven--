#include "Stencil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../packages/eigen/Eigen/SparseCore"
#include "../packages/eigen/Eigen/SparseCholesky"
#include "../packages/eigen/Eigen/Dense"



Stencil::Stencil(StencilType Type, System Sys)
{
    this->Type = Type;
    this->Sys = Sys;
    M.resize(Sys.Np, Sys.Np);
    this->MatrixAllocationReserving();
    this->Generate();
    this->Solve();
}

void Stencil::MatrixAllocationReserving()
{
    switch (Type)
    {
        case Laplacian:
            //Reserve with expectation for 1-1-4-1-1 stencil for each point. (Overestimation)
            M.reserve(5 * Sys.Np * Sys.Np);
            break;
        default:
            std::cout<<"No stencil type selected";
            break;
    }
}

void Stencil::Generate()
{
    try
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
    catch (const std::exception& e)
    {
        std::cout<<"ERROR"<<std::endl;

    }

}

void Stencil::Solve()
{
    //Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> chol(this->M);
    //Eigen::VectorXd solved = chol.solve();
    //Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> s(this->M);
    // Eigen::VectorXd xe = Eigen::VectorXd::Constant(M.rows(), 1);
	// Eigen::VectorXd b = M*xe;
    // Eigen::VectorXd x = s.solve(b);
    //Eigen::Solve(this->M);

    // Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> s;
    // Eigen::VectorXd xe = Eigen::VectorXd::Constant(M.rows(), 1);
	// Eigen::VectorXd b = M*xe;
    // Eigen::VectorXd x = s.compute(this->M).solve();


    Eigen::VectorXd b = Eigen::VectorXd(Sys.Np);
    Eigen::VectorXd x;
    for (int i = 0; i < Sys.Np; i++)
    {
        b[i] = 0;
    }
    // fill b
    // solve Ax = b
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > solver;
    solver.compute(M);
    if(solver.info()!=Eigen::Success) 
    {
        // decomposition failed
        std::cout<< "Decomposition failed";
        return;
    }
    x = solver.solve(b);
    if(solver.info()!=Eigen::Success) 
    {
        // solving failed
        std::cout<< "Solving failed";
        return;
    }

    std::cout<< x << std::endl;
}