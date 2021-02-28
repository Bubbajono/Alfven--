#include "Laplace.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FileOutput.h"
#include "../packages/eigen/Eigen/Dense"

//http://gnuplot.sourceforge.net/demo_5.2/heatmaps.html

Laplace::Laplace(int L)
{
    this->L = L;

    Laplace::InstantiateVector();
    std::cout << "Instantiated Vector" << std::endl;
    Laplace::SetInitialConditions();
    std::cout << "Initial conditions set" << std::endl;
    Laplace::SimpleSolve();
    std::cout << "Simple solved" << std::endl;

    // FileOutput out;
    // FileOutput::OutputToFile_3DGridFormat(this->U, "Laplace3DGrid.dat");
    // std::cout << "3D Grid format file generated" << std::endl;
    // FileOutput::OutputToFile_Heatmap(this->U, "LaplaceHeatmap.dat");
    // std::cout << "Heatmap generated" << std::endl;

}

void Laplace::InstantiateVector()
{
    std::vector<std::vector<int>> M;
    for (int i = 0; i < L; i++)
    {
        std::vector<int> v;
        for (int j = 0; j < L; j++)
        {
            v.push_back(0);
        }
        M.push_back(v);
    }
    this->U = M;
}

void Laplace::SetInitialConditions()
{
    //Edges
    for (int i = 0; i < L; i++)
    {
        U[i][0] = 100;
        U[0][i] = 100;
        U[i][L-1] = 100;
        U[L-1][i] = 100;
    }

    
}

void Laplace::SimpleSolve(int nInterations)
{
    //Simple solve with a 0 fixed boundary on outer edge of system
    for (int iterations = 0; iterations < nInterations; iterations++)
    {
        for (int i = 1; i < L - 1; i++)
        {
            for (int j = 1; j < L - 1; j++)
            {
                U[i][j] = 0.25 * (U[i + 1][j] + U[i - 1][j] + U[i][j - 1] + U[i][j + 1]);
            }
        }

    }
}