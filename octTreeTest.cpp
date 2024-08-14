#include <cstdlib>
#include <iostream>
#include "Space/space.h"
#include "Space/octTree.h"
using namespace std;

int main(int argc,char** argsv)
{
    Vec3 a(1.0,2.0,3.0);
    Vec3 b(4.0,2.0,5.0);
    
    string hello_txt = "hello";
    string* hello = &hello_txt;

    string hi_txt = "hi";
    string* hi = &hello_txt;

    OctTree<string*> world = OctTree<string*>(
        Vec3::globalMinimum, Vec3::globalMaximum,1,2);

    cout << a.to_string();
    world.AddChild(a,hello);
    world.AddChild(b,hi);
    world.RemoveChild(a,hello);

    

    cout << a.to_string() << "\n";
    cout << b.to_string() << "\n";
    
}