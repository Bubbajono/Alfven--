#include "System.h"
#include <math.h>
#include "FileOutput.h"

System::System()
{
    
}

System::System(int L, double radius, int GridWidth)
{
    this->L = L;
    this->GridWidth = GridWidth;
    this->h = (2.0*GridWidth) / (L - 1.0);
    this->radius = radius;
    this->SetupGridArrays();
    //FileOutput::OutputToFile_Heatmap_GridArrayConversion(this->GridArrayIJ, "GridArrayIJ_Output.dat");
}

Vec2D System::GetVec2D(int i, int j)
{
    double x = -this->GridWidth + i * h;
    double y = -this->GridWidth + j * h; 
    return Vec2D(x, y);
}

bool System::IsVecWithinDomain(Vec2D vec)
{
    return (vec.Normalise() <= radius);
}

void System::SetupGridArrays()
{
    //Initialise GridArrayIJ
    GridArrayIJ.clear();
    for (int i = 0; i < L; i++)
    {
        std::vector<int> v;
        for (int j = 0; j < L; j++)
        {
            v.push_back(0);
        }
        GridArrayIJ.push_back(v);
    }

    int Np = 0;
    GridArrayP.clear();
    for (int j = 0; j < L; j++)
    {
        for (int i = 0; i < L; i++)
        {
            Vec2D vec = this->GetVec2D(i, j);

            if (this->IsVecWithinDomain(vec))
            {
                GridArrayIJ[j][i] = Np;
                GridArrayP.push_back(Vec2D(i, j));

                Np++;
            }
            else
            {
                GridArrayIJ[j][i] = -1;
            }

        }
    }

    //Set
    this->GridArrayIJ = GridArrayIJ;
    this->GridArrayP = GridArrayP;
    this->Np = Np;
}

