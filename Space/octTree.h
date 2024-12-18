#pragma once
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "space.h"
#include <unordered_set>
#include <stdexcept>
#include <string>
#include "../Collections/linkedlist.h"

#define DEBUG_OCTREE 1

using namespace std;

template <class T>
struct OctTreeNode {
public:
	T data;
	Vector3 position;
};

template <class T>
class OctTree {
	// Data    
public:
	OctTree<T>* nodes;
	OctTree<T>();
	OctTree<T>(Vector3, Vector3, int, int);

	~OctTree<T>();
private:

	int numChildren = 0;
	int numSectors = 0;
	int capacity;
	vector<OctTreeNode<T>> children;
	Vector3 lowerBounds, upperBounds;

	// Functions
public:
	void addChild(const Vector3&, T);
	void removeChild(const Vector3&, T);
	void updateChild(Vector3&, T);

private:
	void updateChildren();
	std::string toString() const;
	void subdivide(OctTree<T>* nodes, int numDivisions);
	Vector3 calculateMidPoint(const Vector3& _a, const Vector3& _b);
	void merge(OctTree<T>* node);
	OctTree<T>* findSector(const Vector3&);
	bool isNodeEmpty();
	bool checkInBounds(const Vector3&);

};

// Constructors

template<class T>
inline OctTree<T>::OctTree() : OctTree(Vector3::globalMinimum, Vector3::globalMaximum, 0, 2) {
}

template<class T>
inline OctTree<T>::OctTree(Vector3 _lowerBounds, Vector3 _upperBounds, int numDivisions, int _capacity)
{
	// Define the Boundaries of the OctTree Sector
	lowerBounds = _lowerBounds;
	upperBounds = _upperBounds;
	capacity = _capacity;
	nodes = nullptr;
	numSectors = 0;

	if (numDivisions > 0)
	{
		nodes = new OctTree<T>[8];
		
		numDivisions--;
		numSectors = numDivisions;
		printf("\nCreating Oct Tree\n");
		subdivide(nodes, numDivisions);

	}
}

// Functions

// Converts from index 0,1 to -1,+1
float convertIndexToAxis(float _axis) {
	return (_axis - .5f) * 2.0f;
};

template<class T>
void OctTree<T>::subdivide(OctTree<T>* nodes, int numDivisions) {
#if DEBUG_OCTREE
	printf("Subdivide!\n");
#endif
	for (int z = 0; z < 2; z++)
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++) {
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

				Vector3 _childMidPoint = calculateMidPoint(lowerBounds, upperBounds);

				Vector3 _childLowerBounds = Vector3(
					x == 0 ? lowerBounds.x : _childMidPoint.x,
					y == 0 ? lowerBounds.y : _childMidPoint.y,
					z == 0 ? lowerBounds.z : _childMidPoint.z);

				Vector3 _childUpperBounds = Vector3(
					x == 0 ? _childMidPoint.x : upperBounds.x,
					y == 0 ? _childMidPoint.y : upperBounds.y,
					z == 0 ? _childMidPoint.z : upperBounds.z);

				int index = x + y * 2 + z * 4;
				printf("\tIndex: %s Sectors: %s \t lower: %s \t upper: %s \n",
					std::to_string(index).c_str(),
					std::to_string(numSectors).c_str(),
					_childLowerBounds.toString().c_str(),
					_childUpperBounds.toString().c_str());

				nodes[index] =
					OctTree(_childLowerBounds, _childUpperBounds, numDivisions, capacity);
			}
}

template<class T>
Vector3 OctTree<T>::calculateMidPoint(const Vector3& _a, const Vector3& _b) {
	return (lowerBounds + upperBounds) / 2.0f;
}


template<class T>
void OctTree<T>::merge(OctTree<T>* node) {

#if DEBUG_OCTREE
	printf("\nMerge!\n");
#endif
	for (int i = 0;i < 8;i++) {
		auto subNode = node[i];
		if (subNode.isNodeEmpty()) {
			for (auto child : subNode.children) {
				addChild(child);
			}
			delete subNode;
		}
	}
}

template<class T>
inline OctTree<T>::~OctTree()
{
	if (nodes != nullptr)
	{
		delete[] nodes;
	}
}


template <class T>
void OctTree<T>::addChild(const Vector3& position, T child)
{
	OctTreeNode<T> nodeChild;
	nodeChild.data = child;
	nodeChild.position = position;
	// Find node/sector to put this into
	auto sector = findSector(position);
	if (sector->numChildren >= capacity) {
		sector->subdivide(sector, 1);
		sector->updateChildren();
	}
	// Add the child to the collection in that sector
	sector->children.push_back(nodeChild);
	sector->numChildren++;

#if DEBUG_OCTREE
	printf("added child: %s to %s\n", position.toString().c_str(), sector->toString().c_str());
#endif


}

template<class T>
void OctTree<T>::removeChild(const Vector3& position, T child)
{
	bool foundChild = false;
	auto sector = findSector(position);
	auto& sectorChildren = sector->children;
	for (auto iter = sectorChildren.begin();iter != sectorChildren.end();++iter) {
		if (iter->data == child) {
			foundChild = true;
#if DEBUG_OCTREE
			printf("remove child: %s\n", position.toString().c_str());
#endif
			sectorChildren.erase(iter);
			numChildren--;
			break;
		}
	}
	if (!foundChild) {
		// uh oh
		printf("[octTree.h] Did not find child in octTree!\n");
	}

}

template<class T>
inline OctTree<T>* OctTree<T>::findSector(const Vector3& position)
{ 
	bool isEmpty = isNodeEmpty();
	// Found the lowest possible level
	if (isEmpty) {
		// Check that the position is in bounds
		if (checkInBounds(position)) {
#if DEBUG_OCTREE
			printf("\nFound sector: %s\t", toString().c_str());
#endif
			return this;

		}
		else
		{
			assert(false, "fail!");
		}
	}
		// Still looking for a lower node
		// Calculate Mid point
		Vector3 sectorCenter = (lowerBounds + upperBounds) / 2.0f;
		// Get Position relative to midpoint of Current Sector
		Vector3 sectorDiff = position - sectorCenter;
		// Convert relative position to sector Octant
		Vector3 normalised = sectorDiff.normalize();
		// Axis Clamp - rounds each axis to the nearest whole
		// Convert from -1 1 to 0 1
		Vector3 axisClamp = Vector3(
			roundf((normalised.x + 1.0f) / 2.0f),
			roundf((normalised.y + 1.0f) / 2.0f),
			roundf((normalised.z + 1.0f) / 2.0f));

		// Sector index - x 01 y
		int sectorIndex = (int) (axisClamp.x + axisClamp.y * 2 + axisClamp.z * 4);
#if DEBUG_OCTREE
		printf("\nLooking in sector: %s\n", nodes[sectorIndex].toString().c_str());
#endif
		return nodes[sectorIndex].findSector(position);
	

}

template<class T>
inline void OctTree<T>::updateChild(Vector3& position, T child)
{
	removeChild(position, child);
	addChild(position, child);
}

template<class T>
inline void OctTree<T>::updateChildren()
{
	for (OctTreeNode<T> currentChild : children) {
		updateChild(currentChild.position, currentChild.data);
	}
}
template<class T>
inline std::string OctTree<T>::toString() const {
	return "lowerBounds: " + lowerBounds.toString()
		+ " upperBounds: " + upperBounds.toString()
		+ " numChildren: " + std::to_string(numChildren) + "\n";
}

template<class T>
inline bool OctTree<T>::isNodeEmpty()
{
	return numChildren == 0;
}

template<class T>
inline bool OctTree<T>::checkInBounds(const Vector3& position)
{
	return position.checkAABB(position, lowerBounds, upperBounds);
}

