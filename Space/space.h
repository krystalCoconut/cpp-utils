#pragma once
#include <string>
#include <cmath>
#include <array>
#include <cstdlib>
#include <limits>
#include <cassert>
#include <iterator>

class Vector3;
class Quaternion;
class Matrix4x4;

class Vector3 {
    public:
        float x;
        float y;
        float z;
    
    Vector3(float,float,float);
    Vector3();
    ~Vector3();

    static Vector3 zero;
    const static Vector3 globalMinimum;
    const static Vector3 globalMaximum;

    static float distance(const Vector3 &a, const Vector3 &b){
        float x_diff = std::abs(a.x - b.x);
        float y_diff = std::abs(a.y - b.y);
        float z_diff = std::abs(a.z - b.z);
        return std::sqrt(x_diff * x_diff
            + y_diff * y_diff
            + z_diff * z_diff);
    }

    static float dot(const Vector3 &a, const Vector3 &b){
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    static Vector3 cross(const Vector3 &a, const Vector3 &b){
        return Vector3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x); 
    }

    static bool checkAABB(const Vector3& point, const Vector3& lowerBounds, const Vector3& upperBounds) {
        
        return  lowerBounds.x <= point.x  && point.x <= upperBounds.x &&
                lowerBounds.y <= point.y  && point.y <= upperBounds.y &&
                lowerBounds.z <= point.z  && point.z <= upperBounds.z;
    }

    Vector3 operator+(const Vector3&) const;
    Vector3 operator-(Vector3 const&) const;
    Vector3 operator*(const float& mult) const;
    Vector3 operator/(const float& div) const;
    Vector3 operator*(const Quaternion* rotation) const;

    float length() const;
    Vector3 normalize() const;
    
    std::string toString() const;
};

class Quaternion {
public:
    float x;
    float y;
    float z;
    float w;

    // Constructors
    Quaternion(float, float, float, float);
    Quaternion(Vector3, float);
    Quaternion();
    ~Quaternion();

    static Quaternion identity;

    Quaternion operator*(const Quaternion* multiplier) const;
    Quaternion angleAxis(Vector3 axis, float angle);

    std::string toString() const;
};

class Matrix4x4 {
public:
    std::array<float, 16> indices;

    Matrix4x4();
    Matrix4x4(Quaternion);
    Matrix4x4(Vector3);
    ~Matrix4x4();

    static Matrix4x4 identity;

    Matrix4x4 operator*(const Matrix4x4& rhs) const;
    std::string toString();
};
