#pragma once
#include <string>
#include <cmath>

class Vec3 {
    public:
        float x;
        float y;
        float z;
    
    Vec3(float,float,float);
    Vec3();
    ~Vec3();

    static Vec3 zero;
    static Vec3 globalMinimum;
    static Vec3 globalMaximum;

    static float distance(const Vec3 &a, const Vec3 &b){
    return std::sqrt( (a.x - b.x) * (a.x - b.x)
                    + (a.y - b.y) * (a.y - b.y)
                    + (a.z - b.z) * (a.z - b.z));
    }

    static float dot(const Vec3 &a, const Vec3 &b){
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    static Vec3 cross(const Vec3 &a, const Vec3 &b){
        return Vec3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x); 
    }

    static bool AABBCheck(const Vec3& point, const Vec3& lowerBounds, const Vec3& upperBounds) {
        
        return  lowerBounds.x <= point.x  && point.x <= upperBounds.x &&
                lowerBounds.y <= point.y  && point.y <= upperBounds.y &&
                lowerBounds.z <= point.z  && point.z <= upperBounds.z;
    }

    Vec3 operator+(const Vec3&) const;
    Vec3 operator-(Vec3 const&) const;
    Vec3 operator*(const float& mult) const;
    Vec3 operator/(const float& div) const;
    float length() const;
    Vec3 normalize() const;
    
    std::string to_string() const;
};