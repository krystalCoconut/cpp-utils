#include "space.h"
#include <limits>
#include <cassert>
#include <string>

// Member initialization list for construction
Vector3::Vector3(float _x,float _y,float _z) : x(_x), y(_y), z(_z) {}
Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::~Vector3() {}

Vector3 Vector3::zero = Vector3(0,0,0);

using std::numeric_limits;
// Careful using these

const float max = 1000;//FLT_MIN;
const float min = -1000;//FLT_MAX;

const Vector3 Vector3::globalMinimum = Vector3(min, min, min);
const Vector3 Vector3::globalMaximum = Vector3(max, max, max);

// fixme: function call overhead
Vector3 Vector3::normalize() const{
    assert(length() != 0,"Length of Vector cannot be zero! Could not normalise");
    return *this / length();
}

Vector3 Vector3::operator+(const Vector3 &b) const{
    return Vector3(b.x + x, b.y + y,b.z + z);
}

Vector3 Vector3::operator-(const Vector3 &b) const{
    return Vector3(x - b.x, y - b.y,z - b.z);
}

Vector3 Vector3::operator*(const float &mult) const{
    return Vector3(mult * x, mult * y,mult * z);
}

Vector3 Vector3::operator/(const float &div) const{
    return Vector3(x / div, y / div, z / div);
}

// fixme: function call overhead?
float Vector3::length() const{
    return Vector3::distance(zero, *this);
}


std::string Vector3::toString() const{
    return "[" +
            std::to_string(x) + "," + 
            std::to_string(y) + "," + 
            std::to_string(z) + "]";
}