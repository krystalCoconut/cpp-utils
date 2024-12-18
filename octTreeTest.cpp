#include <cstdlib>
#include <iostream>
#include "space/space.h"
#include "space/octTree.h"
using namespace std;

int main(int argc,char** argsv)
{
    Vector3 a(1.0,2.0,3.0);
    Vector3 b(4.0,2.0,5.0);
    Vector3 c(-6.0, 7.0, -8.0);
    
    string hello_txt = "hello";
    string* hello = &hello_txt;

    string hi_txt = "hi";
    string* hi = &hi_txt;

    string howdy_txt = "howdy";
    string* howdy = &howdy_txt;

    OctTree<string*> world = OctTree<string*>(
        Vector3::globalMinimum, Vector3::globalMaximum,2,1);

    cout << a.toString();
    world.addChild(a,hello);
    world.addChild(b,hi);
    world.removeChild(a,hello);
    //world.addChild(c,howdy);
    

    cout << a.toString() << "\n";
    cout << b.toString() << "\n";
    
}