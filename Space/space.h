#pragma once
#include <string>
#include <cmath>

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
    float length() const;
    Vector3 normalize() const;
    
    std::string toString() const;
};