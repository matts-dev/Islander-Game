#include <cmath>
#include "Actor.h"
#include "SpatialHash.h"

using std::shared_ptr;
using std::make_shared;

ee::SpatialHash::SpatialHash(int gridSize, int tableSize)
	: gridSize(gridSize),
	tableSize(tableSize),
	hashMap(std::unique_ptr<shared_ptr<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>[]>(new shared_ptr<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>[tableSize])),
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
	int index = hashFloat(x, y);
	auto chain = hashMap[index];

	//calculate grids (will be part of key)
	int horrizontalGrid = static_cast<int>(x / gridSize);
	int verticalGrid = static_cast<int>(y / gridSize);
	sf::Vector2i gridXY(horrizontalGrid, verticalGrid);


	//chain of nodes already exists
	if (chain) {
		auto newNode = std::make_shared<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>(gridXY, actor, nullptr);
		chain->addNode(newNode);
	}
	//no chain exists
	else {
		hashMap[index] = std::make_shared<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>(gridXY, actor, nullptr);
	}
}

bool ee::SpatialHash::remove(const float & x, const float & y, std::weak_ptr<Actor> actor)
{
	int index = hashFloat(x, y);
	auto chain = hashMap[index];

	//calculate grids (will be part of key)
	int horrizontalGrid = static_cast<int>(x / gridSize);
	int verticalGrid = static_cast<int>(y / gridSize);
	sf::Vector2i gridXY(horrizontalGrid, verticalGrid);

	//chain of nodes already exists
	if (chain) {
		//CHAIN HEAD TO BE REMOVED
		if (chain->value.lock() == actor.lock()) {
			//get the next child, and remove current node from table
			auto nextInChain = chain->getNextNode();
			hashMap[index] = nextInChain;
			chain->setNextNode(nullptr);
			return true;
		} 
		//CHAIN CHILD TO BE REMOVED
		else if (chain->getNextNode()) {
			auto newNode = std::make_shared<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>(gridXY, actor, nullptr);
			return chain->removeChild(newNode);
		}
	}
	//no chain exists, key value pair must not be in map
	return false;
}

std::vector<std::weak_ptr<ee::Actor>> ee::SpatialHash::getNearby(const float & x, const float & y)
{
	std::vector<std::weak_ptr<ee::Actor>> nearbyActorsContainer;

	//for all 9 grids surrounding the center grid
	int centerHorrGrid = static_cast<int>(x / gridSize);
	int centerVertGrid = static_cast<int>(y / gridSize);

	int leftGrid = centerHorrGrid - 1;
	int topGrid = centerVertGrid - 1;
	for (int i = leftGrid; i < centerHorrGrid + 1; ++i) {
		for (int j = topGrid; j < centerVertGrid + 1; ++j) {
			int index = hashGrid(i, j);
			auto iter = hashMap[index];
			while (iter != nullptr) {
				nearbyActorsContainer.push_back(iter->value);
				iter = iter->getNextNode();
			}
		}
	}

	return nearbyActorsContainer;
}

void ee::SpatialHash::updateFromTo(const float & oldX, const float & oldY, std::weak_ptr<Actor> actor, const float & newX, const float & newY)
{
	remove(oldX, oldY, actor);
	add(newX, newY, actor);
}


int ee::SpatialHash::hashFloat(const float & x, const float & y)
{
	//first subdivide into grids, then use horner's version of universal hash function on components
	int horrizontalGrid = static_cast<int>(x / gridSize);
	int verticalGrid = static_cast<int>(y / gridSize);

	return hashGrid(horrizontalGrid, verticalGrid);
}

int ee::SpatialHash::hashGrid(const int & horrizontalGrid, const int & verticalGrid)
{
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


