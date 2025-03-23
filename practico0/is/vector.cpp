#include "vector.h"

Vector::Vector(float x, float y, float z)
{
    this->x_index = x;
    this->y_index = y;
    this->z_index = z;
    this->saved_module = sqrt(x * x + y * y + z * z);
}

Vector::Vector()
{
    this->x_index = 0;
    this->y_index = 0;
    this->z_index = 0;
    this->saved_module = 0;
}

float Vector::getX() const
{
    return this->x_index;
}

float Vector::getY() const
{
    return this->y_index;
}

float Vector::getZ() const
{
    return this->z_index;
}

void Vector::setX(float x)
{
    this->x_index = x;
}

void Vector::setY(float y)
{
    this->y_index = y;
}

void Vector::setZ(float z)
{
    this->z_index = z;
}

std::ostream &operator<<(std::ostream &os, const Vector &v)
{
    os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
    return os;
}

Vector Vector::operator+(const Vector &v) const
{
    float newX = this->getX() + v.getX();
    float newY = this->getY() + v.getY();
    float newZ = this->getZ() + v.getZ();
    return Vector(newX, newY, newZ);
}

Vector Vector::operator-(const Vector &v) const
{
    float newX = this->getX() - v.getX();
    float newY = this->getY() - v.getY();
    float newZ = this->getZ() - v.getZ();
    return Vector(newX, newY, newZ);
}

Vector Vector::operator*(float scalar) const
{
    float newX = this->getX() * scalar;
    float newY = this->getY() * scalar;
    float newZ = this->getZ() * scalar;
    return Vector(newX, newY, newZ);
}

Vector Vector::cross(const Vector &v) const
{
    float newX = this->getY() * v.getZ() - this->getZ() * v.getY();
    float newY = this->getZ() * v.getX() - this->getX() * v.getZ();
    float newZ = this->getX() * v.getY() - this->getY() * v.getX();
    return Vector(newX, newY, newZ);
}

float Vector::dot(const Vector &v) const
{
    float newX = this->getX() * v.getX();
    float newY = this->getY() * v.getY();
    float newZ = this->getZ() * v.getZ();
    return newX + newY + newZ;
}

float Vector::angle(const Vector &v) const
{
    float dotProduct = this->dot(v);
    float moduleProduct = this->module() * v.module();
    return acos(dotProduct / moduleProduct);
}

Vector Vector::operator/(float scalar) const
{
    float newX = this->getX() / scalar;
    float newY = this->getY() / scalar;
    float newZ = this->getZ() / scalar;
    return Vector(newX, newY, newZ);
}

Vector Vector::operator-() const
{
    float newX = -this->getX();
    float newY = -this->getY();
    float newZ = -this->getZ();
    return Vector(newX, newY, newZ);
}

float Vector::module() const
{
    return this->saved_module;
}

float Vector::squareModule() const
{
    return this->module() * this->module();
}

Vector Vector::normalize() const
{
    return *this / this->module();
}

Vector Vector::symmetrical(const Vector &v) const
{
    Vector normalized = v.normalize();
    return normalized * this->dot(normalized) * 2 - *this;
}
