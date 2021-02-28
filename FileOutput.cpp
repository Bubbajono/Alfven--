#include "FileOutput.h"
#include "Vec2D.h"
#include <iostream>
#include <fstream>

void FileOutput::OutputToFile_3DGridFormat(std::vector<std::vector<int>> U, std::string filename)
{
    std::ofstream file(filename);

    for (int i=0; i<U.size();i++)
    {
        for (int j=0; j<U[i].size();j++)
        {
            file << U[i][j] << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

void FileOutput::OutputToFile_Heatmap(std::vector<std::vector<int>> U, std::string filename)
{
    std::ofstream file(filename);

    for (int i=0; i<U.size();i++)
    {
        for (int j=0; j<U[i].size();j++)
        {
            file << i << " " << j << " " << U[i][j] << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

void FileOutput::OutputToFile_Heatmap_GridArrayConversion(std::vector<std::vector<int>> U, std::string filename)
{
    std::ofstream file(filename);

    for (int i=0; i<U.size();i++)
    {
        for (int j=0; j<U[i].size();j++)
        {
            Vec2D vec(i, j);
            file << vec.a << " " << vec.b << " " << U[i][j] << std::endl;
        }
        file << std::endl;
    }

    file.close();
}
