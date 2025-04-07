#include "readFile.h" // Include the header file
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<DataPoint> readFile(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Failed to open file.\n";
        return {};
    }

    std::vector<DataPoint> data;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        DataPoint dp;
        if (iss >> dp.id >> dp.x >> dp.y >> dp.z)
        {
            data.push_back(dp);
        }
        else
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }
    }

    // Example output
    for (const auto &dp : data)
    {
        std::cout << dp.id << ": (" << dp.x << ", " << dp.y << ", " << dp.z << ")\n";
    }

    return data;
}
