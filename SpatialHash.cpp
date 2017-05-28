#include <cmath>
#include "Actor.h"
#include "SpatialHash.h"

using std::weak_ptr;

ee::SpatialHash::SpatialHash(int gridSize, int tableSize)
	: gridSize(gridSize),
	tableSize(tableSize),
	hashMap(std::make_unique<HashNode<sf::Vector2i, weak_ptr<Actor>>*[]>(tableSize)),
	hornerNumber(17)
{
	//initial table to nullptr
	for (int i = 0; i < tableSize; ++i) {
		hashMap[i] = nullptr;
	}
}

ee::SpatialHash::~SpatialHash()
{
}

/**
Simply loads bit patterns of float into a 64 bit carrier that is gauranteed to be unique.
The output is intended to be used in a balanced binary tree rather than a hashmap.

Hash is special in that it can be reversed to determine the origonal x and y of the coordinate. 
*/
int ee::SpatialHash::hash(const float & x, const float & y)
{
	//first subdivide into grids, then use horner's version of universal hash function on components
	int horrizontalGrid = static_cast<int>(x / gridSize);
	int verticalGrid = static_cast<int>(y / gridSize);

	//make a single vector that contains bits for both the horrizontal and vertical grids
	int64_t vector = horrizontalGrid;
	vector <<= 32;	//make room for the vertical grid
	vector |= verticalGrid; //OR in the vertical grid into bottom 32 bits
	vector = std::abs(vector);

	//run hash function per byte
	uint8_t byteMask = -1;
	int hash = 0;
	for (int i = 0; i < 8; ++i) {
		int val = vector & byteMask;
		val = std::abs(val);
		vector >>= 8;

		hash = ((hash * hornerNumber) + val) % tableSize;
	}
	hash %= tableSize;
	hash = std::abs(hash);
	return hash;
}
