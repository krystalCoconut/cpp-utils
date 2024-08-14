#pragma once
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "space.h"
#include <unordered_set>
#include <stdexcept>
#include "../Collections/linkedlist.h"

#define DEBUG 1

using namespace std;

template <class T>
struct OctTreeNode {
    public:
        T data;
        Vec3 position;
};

template <class T>
class OctTree {
    // Data    
    public:
        OctTree<T>* nodes;
        OctTree<T>();
        OctTree<T>(Vec3, Vec3, int, int);

    ~OctTree<T>();
    private:
        int numChildren = 0;
        int capacity;
        vector<OctTreeNode<T>> children;
        Vec3 lowerBounds,upperBounds;
    
    // Functions
    public:
        void AddChild(const Vec3&, T);
        void RemoveChild(const Vec3&, T);
        void UpdateChild(Vec3&, T);

    private:
        void UpdateChildren();

    std::string to_string() const;

    void Subdivide(OctTree<T> *nodes, int numDivisions);
        void Merge(OctTree<T> *node);
        OctTree<T>* FindSector(const Vec3&,  OctTree<T>*);
        bool isNodeEmpty();
        bool CheckInBounds(Vec3);
    
};

// Constructors

template<class T>
inline OctTree<T>::OctTree() : OctTree(Vec3::globalMinimum, Vec3::globalMaximum, 0,2){
}

template<class T>
inline OctTree<T>::OctTree(Vec3 _lowerBounds, Vec3 _upperBounds, int numDivisions, int _capacity)
{
    // Define the Boundaries of the OctTree Sector
    lowerBounds = _lowerBounds;
    upperBounds = _upperBounds;
    capacity = _capacity;
    nodes = nullptr;

    if (numDivisions > 0)
    {
        nodes = new OctTree<T>[8];

        numDivisions--;
    
        printf("\nCreating Oct Tree\n");
        Subdivide(nodes,numDivisions);

    }
}

template<class T>
void OctTree<T>::Subdivide(OctTree<T>* nodes, int numDivisions) {
    // #if DEBUG
    printf("\nSubdivide!\n");
    // #endif
    for(int z = 0; z < 2; z++)
            for (int y = 0; y < 2; y++)
                for (int x = 0; x < 2; x++) {

                    // Converts from index 0,1 to -1,+1
                    auto convertIndexToAxis = [&](float _axis) {
                        return (_axis - .5f) * 2.0f;
                        };

                    // Calculate Midpoint
                    auto calcMidPoint = [&](const Vec3& _a, const Vec3& _b) /* -> Vec3 */ {
                        return (lowerBounds + upperBounds) / 2.0f;
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

                    printf("Nodes: \t lower: %s \t upper: %s \n",
                        _childLowerBounds.to_string().c_str(),
                        _childUpperBounds.to_string().c_str());



                    nodes[x + y * 2 + z * 4] =
                        OctTree(_childLowerBounds, _childUpperBounds, numDivisions, capacity);
                }
}

template<class T>
void OctTree<T>::Merge(OctTree<T>* node) {

#if DEBUG
    printf("\nMerge!\n");
#endif
    for(int i=0;i<8;i++) {
        auto subNode = node[i];
        if(subNode.isNodeEmpty()) {
            for (auto child: subNode.children) {
                AddChild(child);
            }
            delete subNode;
        }
    }
}

template<class T>
inline OctTree<T>::~OctTree()
{
    delete[] nodes;
}


template <class T>
void OctTree<T>::AddChild(const Vec3& position, T child)
{
    OctTreeNode<T> nodeChild;
    nodeChild.data = child;
    nodeChild.position = position;

    // Find node/sector to put this into
    auto sector = FindSector(position,nodes);
    if(sector->numChildren >= capacity) {
        sector->Subdivide(sector,1);
        sector->UpdateChildren();
    }

#if DEBUG
    printf("added child: %s to %s\n",position.to_string().c_str(),sector->to_string().c_str());
#endif

    // Add the child to the collection in that sector
    sector->children.push_back(nodeChild);
    numChildren++;
}

template<class T>
void OctTree<T>::RemoveChild(const Vec3& position, T child)
{
    bool foundChild = false;
    auto sector = FindSector(position,nodes);
    auto &sectorChildren = sector->children;
    for (auto iter = sectorChildren.begin();iter != sectorChildren.end();++iter) {
        if(iter->data == child) {
            foundChild = true;
#if DEBUG
            printf("remove child: %s\n",position.to_string().c_str());
#endif
            sectorChildren.erase(iter);
            numChildren--;
            break;
        }
    }
    if(!foundChild) {
        // uh oh
        printf("[octTree.h] Did not find child in octTree!\n");
    }

}

template<class T>
inline OctTree<T>* OctTree<T>::FindSector(const Vec3 &position,  OctTree<T> *node)
{
    // Found the lowest possible level
    if(node->isNodeEmpty()) {
        // Check that the position is in bounds
        if(CheckInBounds(position)) {
#if DEBUG
            printf("\nFound sector: %s\t",node->to_string().c_str());
#endif
            return node;
        }
        else {
            printf("[octTree.h] FindSector: position is not in bounds in octTree\n");
            throw out_of_range("[octTree.h] FindSector: position is not in bounds in octTree\n");
            return nullptr;
        }
    }
    // Still looking for a lower node
    else {
        // Calculate Mid point
        Vec3 sectorCenter = (lowerBounds - upperBounds)/2.0f;
        // Get Position relative to midpoint of Current Sector
        Vec3 sectorDiff = position - sectorCenter;
        // Convert relative position to sector Octant
        Vec3 normalised = sectorDiff.normalize();
        // Axis Clamp - rounds each axis to the nearest whole
        // Convert from -1 1 to 0 1
        Vec3 axisClamp = Vec3( roundf(normalised.x)/2.0f+.5f,
            roundf(normalised.y)/2.0f+.5f, roundf(normalised.z)/2.0f+.5f);

        // Sector index - x 01 y
        int sectorIndex = axisClamp.x + axisClamp.y * 2 + axisClamp.z * 4;
#if DEBUG
        printf("\nLooking in sector: %s\n", node[sectorIndex].to_string().c_str());
#endif
        return FindSector(position, &node[sectorIndex]);
    }

}

template<class T>
inline void OctTree<T>::UpdateChild(Vec3& position, T child)
{
    RemoveChild(position,child);
    AddChild(position,child);
}

template<class T>
inline void OctTree<T>::UpdateChildren()
{
    for(OctTreeNode<T> currentChild : children) {
        UpdateChild(currentChild.position,currentChild.data);
    }
}
template<class T>
inline std::string OctTree<T>::to_string() const {
    return "lowerBounds: " + lowerBounds.to_string()
    + " upperBounds: " + upperBounds.to_string()
    + " numChildren: " + std::to_string(numChildren) + "\n";
}

template<class T>
inline bool OctTree<T>::isNodeEmpty()
{
    return nodes == nullptr;
}

template<class T>
inline bool OctTree<T>::CheckInBounds(Vec3 position)
{
    return position.AABBCheck(position, lowerBounds, upperBounds);
}

