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

void ee::Actor::rectFromTransform(utility::mxb::Rect & buffer, const sf::Transform & transform, const sf::Vector2f & deltaXY, sf::Vector2f & scaledSizeXY) const
{
	//point before transform
	const sf::Vector2f& futurePnt = deltaXY;

	//convert all 4 corners to game world coordinates 
	sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(futurePnt.x, futurePnt.y));
	sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(scaledSizeXY.x + futurePnt.x, futurePnt.y));
	sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(futurePnt.x, scaledSizeXY.y + futurePnt.y));
	sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(scaledSizeXY.x + futurePnt.x, scaledSizeXY.y + futurePnt.y));

	//store those corners in the appropriate buffer for calculations
	vector2fToPnt(topLeft, buffer.pntTopLeft);
	vector2fToPnt(topRight, buffer.pntTopRight);
	vector2fToPnt(bottomLeft, buffer.pntBottomLeft);
	vector2fToPnt(bottomRight, buffer.pntBottomRight);
}

const std::vector<ee::utility::mxb::Rect>& ee::Actor::getCollisionRect(const float deltaX, const float deltaY) const
{
	updateCollisionBoxes(deltaX, deltaY);
	return collisionBoxes;
}
