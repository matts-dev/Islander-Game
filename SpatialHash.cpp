#include <cmath>
#include "Actor.h"
#include "SpatialHash.h"

using std::weak_ptr;
using std::shared_ptr;
using std::make_shared;

ee::SpatialHash::SpatialHash(int gridSize, int tableSize)
	: gridSize(gridSize),
	tableSize(tableSize),
	hashMap(std::make_unique<shared_ptr<HashNode<sf::Vector2i, weak_ptr<Actor>>>[]>(tableSize)),
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

void ee::SpatialHash::add(const float & x, const float & y, std::weak_ptr<Actor> actor)
{
	int index = hash(x, y);
	auto chain = hashMap[index];

	//calculate grids (will be part of key)
	int horrizontalGrid = static_cast<int>(x / gridSize);
	int verticalGrid = static_cast<int>(y / gridSize);
	sf::Vector2i gridXY(horrizontalGrid, verticalGrid);


	//chain of nodes already exists
	if (chain) {
		auto newNode = std::make_shared<HashNode<sf::Vector2i, weak_ptr<Actor>>>(gridXY, actor, nullptr);
		chain->addNode(newNode);
	}
	//no chain exists
	else {
		hashMap[index] = std::make_shared<HashNode<sf::Vector2i, weak_ptr<Actor>>>(gridXY, actor, nullptr);
	}
}


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
