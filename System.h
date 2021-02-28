#include <iostream>
#include <vector>
#include "Vec2D.h"
#ifndef SYSTEM_H // include guard
#define SYSTEM_H

class System
{
    public:
        int L;
        double h;
        double radius;
        int GridWidth;
        int Np;
        std::vector<std::vector<int>> GridArrayIJ;
        std::vector<Vec2D> GridArrayP;
        System();
        System(int L, double radius, int GridWidth = 1);
        Vec2D GetVec2D(int i, int j);
        bool IsVecWithinDomain(Vec2D vec);
    private:
        void SetupGridArrays();
};  

#endif