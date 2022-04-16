#include <cstdlib>
#include <iostream>
#include "space.h"
using namespace std;

int main(int argc,char** argsv)
{
    Vec3 a(1.0,2.0,3.0);
    Vec3 b(4.0,2.0,5.0);
    Vec3 c = Vec3::cross(a,b);
    

    cout << a.to_string() << "\n";
    cout << b.to_string() << "\n";
    cout << c.to_string() << "\n";
}