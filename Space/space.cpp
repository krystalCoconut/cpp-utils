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


Vec3 Vec3::operator+(const Vec3 &b) const{
    return Vec3(b.x + x, b.y + y,b.z + z);
}

Vec3 Vec3::operator-(const Vec3 &b) const{
    return Vec3(b.x - x, b.y - y,b.z - z);
}

Vec3 Vec3::operator*(const float &mult) const{
    return Vec3(mult * x, mult * y,mult * z);
}



std::string Vec3::toString(){
    return "[" + 
            std::to_string(x) + "," + 
            std::to_string(y) + "," + 
            std::to_string(z) + "]";
}