#include <cstdlib>
#include <iostream>
#include "space/space.h"
#include "tests.h"
using namespace std;
#define PI 3.14159265

void Tests::testMatrix()
{
    Vector3 a(0.0f, 0.0f, 1.0f);
    Quaternion rotation(Vector3(0.0f,1.0f,0.0f), PI / 2.0f);
    //cout << a.toString();
    Matrix4x4 aMatrix = Matrix4x4();
    
    cout << aMatrix.toString();
    
    Matrix4x4 bMatrix = aMatrix * rotation;

    cout << bMatrix.toString();

}