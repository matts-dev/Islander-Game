#include "Actor.h"
#include"SpatialHash.h"
#include "Defs.h"

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

bool ee::Actor::rectFromCenteredTransform(utility::mxb::Rect & buffer, const sf::Transformable & transformable, const sf::Vector2f & deltaXY, sf::Vector2f & unscaledSizeXY) const
{
	sf::Vector2f futurePnt = deltaXY;
	
	//SCALE CORRECTION: Since transform takes scale into account, the delta should be scaled down
	const sf::Vector2f& scale = transformable.getScale();
	//make sure scale isn't zero in either x or y 
	if (std::abs(scale.x) > SMALL_NUM && std::abs(scale.y) > SMALL_NUM) { //change precision to a small number macro
		futurePnt.x /= scale.x;
		futurePnt.y /= scale.y;
	}
	else {
		return false;
	}

	//ORIGIN CORRECTION (origin must be used in transformation calculation)
	futurePnt.x += transformable.getOrigin().x;
	futurePnt.y += transformable.getOrigin().y;

	//transform CONTAINS scale information
	const sf::Transform & transform = transformable.getTransform();

	//convert all 4 corners to game world coordinates  
	sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(-unscaledSizeXY.x / 2 + futurePnt.x, -unscaledSizeXY.y / 2 + futurePnt.y));
	sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(unscaledSizeXY.x / 2 + futurePnt.x, -unscaledSizeXY.y / 2 + futurePnt.y));
	sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(-unscaledSizeXY.x / 2 + futurePnt.x, unscaledSizeXY.y / 2+ futurePnt.y));
	sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(unscaledSizeXY.x / 2 + futurePnt.x, unscaledSizeXY.y / 2 + futurePnt.y));
	//sf::Vector2f center = transform.transformPoint(sf::Vector2f(futurePnt.x, futurePnt.y)); 

	//store those corners in the appropriate buffer for calculations
	vector2fToPnt(topLeft, buffer.pntTopLeft);
	vector2fToPnt(topRight, buffer.pntTopRight);
	vector2fToPnt(bottomLeft, buffer.pntBottomLeft);
	vector2fToPnt(bottomRight, buffer.pntBottomRight); //TODO add collision logic to rotation logic in vehicles!

	return true;
}

const std::vector<ee::utility::mxb::Rect>& ee::Actor::getCollisionRect(const float deltaX, const float deltaY) const
{
	updateCollisionBoxes(deltaX, deltaY);
	return collisionBoxes;
}
