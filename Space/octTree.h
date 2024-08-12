#pragma once
#include <cstdlib>
#include <iostream>
#include "space.h"
#include "../Collections/linkedlist.h"

template <class T>
class OctTree {
    // Data    
    public:
        OctTree<T>* nodes;
        OctTree<T>();
        OctTree<T>(Vec3, Vec3, int);
        ~OctTree<T>();
    private:
        int numChildren;
        LinkedList<T>* children;
        Vec3 lowerBounds,upperBounds;
    
    // Functions
    public:
        void AddChild(const Vec3&, T);
        void RemoveChild(T);
        void FindChild(const Vec3&, T);
        void UpdateChild(Vec3&, T);
        void UpdateNodes();
    private:
        int CalcChildren();
        bool isNodeEmpty();
        bool CheckInBounds(Vec3);
    
};

// Constructors

template<class T>
inline OctTree<T>::OctTree() : OctTree(Vec3::globalMinimum, Vec3::globalMaximum, 0){
}

template<class T>
inline OctTree<T>::OctTree(Vec3 _lowerBounds, Vec3 _upperBounds, int numDivisions)
{
    // Define the Boundaries of the OctTree Sector
    lowerBounds = _lowerBounds;
    upperBounds = _upperBounds;

    nodes = NULL;

    if (numDivisions > 0)
    {
        nodes = new OctTree<T>[8];

        numDivisions--;
    
        printf("\nCreating Oct Tree\n");
        for(int z = 0; z < 2; z++)
            for (int y = 0; y < 2; y++)
                for (int x = 0; x < 2; x++) {

                    // Converts from index 0,1 to -1,+1
                    auto convertIndexToAxis = [&](float _axis) {
                        return (_axis - .5f) * 2.0f;
                        };

                    // Calculate Midpoint
                    auto calcMidPoint = [&](const Vec3& _a, const Vec3& _b) /* -> Vec3 */ {
                        return (_lowerBounds + _upperBounds) / 2.0f;
                        };

                    // Indexes go from x:0 -> 1 y:0 -> 1 z:0 -> 1

                    /*
                            ______
                     1     /__/__/|
                          /__/__/||
                     y    |__|__||/    1
                          |__|__|/    z
                     0    0  x  1   0
                    */

                    /*
                           ______
                    1     /__/__/|
                         /__/__/||
                    y    |__|__||/     1
                         |__|__|/     z
                    -1   -1  x  1   -1
                   */

                    Vec3 _childMidPoint = calcMidPoint(lowerBounds, upperBounds);

                    Vec3 _childLowerBounds = Vec3(
                        x == 0 ? lowerBounds.x : _childMidPoint.x,
                        y == 0 ? lowerBounds.y : _childMidPoint.y,
                        z == 0 ? lowerBounds.z : _childMidPoint.z);

                    Vec3 _childUpperBounds = Vec3(
                        x == 0 ? _childMidPoint.x : upperBounds.x,
                        y == 0 ? _childMidPoint.y : upperBounds.y,
                        z == 0 ? _childMidPoint.z : upperBounds.z);

                    printf("\nNodes: \n \t lower: %s \t upper: %s \n",
                        _childLowerBounds.to_string().c_str(),
                        _childUpperBounds.to_string().c_str());

                    nodes[x + y * 2 + z * 4] = OctTree(_childLowerBounds, _childUpperBounds, numDivisions);
                }
    }
}

template<class T>
inline OctTree<T>::~OctTree()
{
    delete[] nodes;
}


template <class T>
void OctTree<T>::AddChild(const Vec3& position, T object)
{

}


template<class T>
inline void OctTree<T>::RemoveChild(T)
{
}

template<class T>
inline void OctTree<T>::FindChild(const Vec3&, T)
{
}

template<class T>
inline void OctTree<T>::UpdateChild(Vec3&, T)
{
}

template<class T>
inline void OctTree<T>::UpdateNodes()
{
}

template<class T>
inline int OctTree<T>::CalcChildren()
{
    return 0;
}

template<class T>
inline bool OctTree<T>::isNodeEmpty()
{
    return false;
}

template<class T>
inline bool OctTree<T>::CheckInBounds(Vec3 position)
{
    return position.AABBCheck(position, lowerBounds, upperBounds);
}

