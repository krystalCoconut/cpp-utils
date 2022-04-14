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


    static float distance(const Vec3 &a, const Vec3 &b){
    return sqrt( pow((a.x - b.x),2) 
        + pow((a.y - b.y),2) 
        + pow((a.z - b.z),2) );
    }

    Vec3 operator+(const Vec3&) const;
    Vec3 operator-(Vec3 const&) const;
    Vec3 operator*(const float& mult) const;
    std::string toString();
};