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

    static float distance(const Vec3 &a, const Vec3 &b){
    return sqrt( pow((a.x - b.x),2) 
        + pow((a.y - b.y),2) 
        + pow((a.z - b.z),2) );
    }

    static float dot(const Vec3 &a, const Vec3 &b){
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    static Vec3 cross(const Vec3 &a, const Vec3 &b){
        return Vec3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x); 
    }

    Vec3 operator+(const Vec3&) const;
    Vec3 operator-(Vec3 const&) const;
    Vec3 operator*(const float& mult) const;
    Vec3 operator/(const float& div) const;
    float length();
    Vec3 normalize();
    
    std::string to_string();
};