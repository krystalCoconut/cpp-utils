#include "space.h"
#define PI 3.14159265
// Vector3

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

// Quaternion

Quaternion::Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
Quaternion::Quaternion(Vector3 axis, float angle) : Quaternion(angleAxis(axis, angle)) {}
Quaternion::~Quaternion() {}

Quaternion Quaternion::identity = Quaternion();

Quaternion Quaternion::operator*(const Quaternion* b) const
{
    return Quaternion(w * b->w + y * b->z - z * b->y,
        w * b->y + y * b->w + z * b->x - x * b->z,
        w * b->z + z * b->w + x * b->y - y * b->x,
        w * b->w - x * b->x - y * b->y - z * b->z
    );
}

Quaternion Quaternion::angleAxis(Vector3 _axis, float angle)
{
    Vector3 axis = _axis.normalize();
    return Quaternion(
        axis.x * std::sinf(angle / 2.0f),
        axis.y * std::sinf(angle / 2.0f),
        axis.z * std::sinf(angle / 2.0f),
        std::cosf(angle / 2.0f)
    );
}

std::string Quaternion::toString() const
{
    return "Quaternion : [" +
        std::to_string(x) + "," +
        std::to_string(y) + "," +
        std::to_string(z) + ",";
}

// Matrix4x4
Matrix4x4::Matrix4x4() { 
    indices.fill(0.0f);
    indices[0] = 1.0f;
    indices[5] = 1.0f;
    indices[10] = 1.0f;
    indices[15] = 1.0f;
};

Matrix4x4::Matrix4x4(Quaternion r) 
{
    // Create the Matrix in column-major format
    // Row 1
    indices[0 + 0 * 4] = 1 - 2.0f * r.y * r.y - 2.0f * r.z * r.z;
    indices[1 + 0 * 4] = 2.0f * r.x * r.y - 2.0f * r.w * r.z;
    indices[2 + 0 * 4] = 2.0f * r.x * r.z + 2.0f * r.w * r.y;
    indices[3 + 0 * 4] = 0.0f;
    // Row 2
    indices[0 + 1 * 4] = 2.0f * r.x * r.y + 2.0f * r.w * r.z;
    indices[1 + 1 * 4] = 1.0f - 2.0f * r.x * r.x - 2.0f * r.z * r.z;
    indices[2 + 1 * 4] = 2.0f * r.y * r.z - 2.0f * r.w * r.x;
    indices[3 + 1 * 4] = 0.0f;
    // Row 3
    indices[0 + 2 * 4] = 2.0f * r.x * r.z - 2.0f * r.w * r.y;
    indices[1 + 2 * 4] = 2.0f * r.y * r.z + 2.0f * r.w * r.x;
    indices[2 + 2 * 4] = 1.0f - 2.0f * r.x * r.x - 2.0f * r.y * r.y;
    indices[3 + 2 * 4] = 0.0f;
    // Row 4
    indices[0 + 3 * 4] = 0.0f;
    indices[1 + 3 * 4] = 0.0f;
    indices[2 + 3 * 4] = 0.0f;
    indices[3 + 3 * 4] = 1.0f;
}

Matrix4x4::Matrix4x4(Vector3 v)
{
    indices.fill(0.0f);
    indices[3] = v.x;
    indices[7] = v.y;
    indices[11] = v.z;

}

Matrix4x4::~Matrix4x4() {}

Matrix4x4 Matrix4x4::identity = Matrix4x4();

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
{
    Matrix4x4 result;

    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            result.indices[row + col * 4] =
                indices[row + 0 * 4] * rhs.indices[0 + col * 4] +
                indices[row + 1 * 4] * rhs.indices[1 + col * 4] +
                indices[row + 2 * 4] * rhs.indices[2 + col * 4] +
                indices[row + 3 * 4] * rhs.indices[3 + col * 4];
        }
    }

    return result;
}

std::string Matrix4x4::toString()
{
    std::string result = "";
    result = "[\n";
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            result += std::to_string(indices[i + j * 4]);
            result += ",";
        }
        result += "\n";
    }
    result += "]";
    return result;
}