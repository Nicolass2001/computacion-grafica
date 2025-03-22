#include <ostream>

class Vector
{
private:
    float x_index;
    float y_index;
    float z_index;
    float saved_module;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

public:
    Vector(float x, float y, float z);
    Vector();

    float getX() const;
    float getY() const;
    float getZ() const;

    // overload cout operator
    friend std::ostream &operator<<(std::ostream &os, const Vector &v);

    // vector addition
    Vector operator+(const Vector &v) const;

    // vector subtraction
    Vector operator-(const Vector &v) const;

    // vector by scalar multiplication
    Vector operator*(float scalar) const;

    // vector cross product
    Vector cross(const Vector &v) const;

    // vector dot product
    float dot(const Vector &v) const;

    // angle between two vectors
    float angle(const Vector &v) const;

    // vector by scalar division
    Vector operator/(float scalar) const;

    // vector negation
    Vector operator-() const;

    // vector module
    float module() const;

    // vector square module
    float squareModule() const;

    // vector normalization
    Vector normalize() const;

    // symmetrical vector to other vector
    Vector symmetrical(const Vector &v) const;
};