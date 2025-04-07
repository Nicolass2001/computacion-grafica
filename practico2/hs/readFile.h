#ifndef READ_FILE_H
#define READ_FILE_H

#include <vector>

struct DataPoint
{
    char id;
    float x;
    float y;
    float z;
};

std::vector<DataPoint> readFile(std::string fileName);

#endif // READ_FILE_H