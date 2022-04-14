#include <cstdlib>
#include <iostream>
#include "space.h"
using namespace std;

int main(int argc,char** argsv)
{
    Vec3 a(1.0,2.0,3.0);
    Vec3 b(4.0,2.0,5.0);
    float c = Vec3::distance(a,b);


    cout << a.toString() << "\n";
    cout << b.toString() << "\n";
    cout << c << "\n";
}