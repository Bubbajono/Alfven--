#include <iostream>
#include <vector>
#include <string>
#ifndef FILEOUTPUT_H // include guard
#define FILEOUTPUT_H

//Static class equivalent
class FileOutput
{
    public:
        static void OutputToFile_3DGridFormat(std::vector<std::vector<int>> U, std::string filename);
        static void OutputToFile_Heatmap(std::vector<std::vector<int>> U, std::string filename);
        static void OutputToFile_Heatmap_GridArrayConversion(std::vector<std::vector<int>> U, std::string filename);
};  

#endif