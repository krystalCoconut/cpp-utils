#include "space.h"


Vec3::Vec3(float _x,float _y,float _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vec3::Vec3(){
    x = y = z = 0;
}

Vec3::~Vec3(){

}

Vec3 Vec3::zero = Vec3(0,0,0);

// fixme: function call overhead
Vec3 Vec3::normalize(){
    return *this / length();
}

Vec3 Vec3::operator+(const Vec3 &b) const{
    return Vec3(b.x + x, b.y + y,b.z + z);
}

Vec3 Vec3::operator-(const Vec3 &b) const{
    return Vec3(b.x - x, b.y - y,b.z - z);
}

Vec3 Vec3::operator*(const float &mult) const{
    return Vec3(mult * x, mult * y,mult * z);
}

Vec3 Vec3::operator/(const float &div) const{
    return Vec3(x / div, y / div, z / div);
}

// fixme: function call overhead?
float Vec3::length(){
    return Vec3::distance(zero, *this);
}


std::string Vec3::to_string(){
    return "[" + 
            std::to_string(x) + "," + 
            std::to_string(y) + "," + 
            std::to_string(z) + "]";
}