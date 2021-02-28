#include <iostream>
#include "Laplace.h"
#include "System.h"

int main(void)
{

    //Laplace sample(10);
    System Sys(100, 1.0);

    Stencil sten(StencilType::Laplacian, Sys);
    return 0;
    
}