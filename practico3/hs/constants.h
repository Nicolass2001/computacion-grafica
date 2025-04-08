#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window dimensions
const int WIDTH = 640;
const int HEIGHT = 480;

// Number of instances
const int INSTANCE_COUNT = 100;

struct Vec3
{
    float x, y, z;
};

struct Instance
{
    Vec3 position;
    float r, g, b;
};

#endif // CONSTANTS_H