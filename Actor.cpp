#include "Actor.h"
#include"SpatialHash.h"

std::unique_ptr<ee::SpatialHash> ee::Actor::spatialHash = nullptr;
void ee::Actor::initSpatialHash(const int gridSize, const int tableSize)
{
	//make_unique not currently supported in xcode environment
	Actor::spatialHash = std::unique_ptr<SpatialHash>(new SpatialHash(gridSize, tableSize));
}

void ee::Actor::enableSpatialHashing(std::weak_ptr<Actor> smartPointerToSelf)
{
	this->smartThis = smartPointerToSelf;
	spatialHash_insertSelf();
}

ee::Actor::Actor(float moveSpeed) : moveSpeed(moveSpeed), smartThis()
{
}


ee::Actor::~Actor()
{
	
}

