#include "Player.h"
#include<SFML/Graphics.hpp>
#include"SpatialHash.h"
#include<cmath>
#include"Ship.h"
#include<iostream>
#include<string>

using std::shared_ptr;
using std::make_shared;

void ee::Player::initSpriteSheet(const sf::Texture& texture, int widthPixels, int heightPixels)
{
	playerSpriteSheet.clear();

	//the following is based specifically on the spriteSheet.png used
	int cols = 4;
	int rows = 2;

	//create a linear sprite sheet where every 2 images represent a character facing a different direction
	//down:{0, 1} left:{2, 3} up:{4, 5} right{6, 7}
	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < rows; ++j) {
			//locations in texture calcuated via position
			int left = i * widthPixels;
			int top = j * heightPixels;

			auto currPtr = make_shared<sf::Sprite>(texture, sf::IntRect(left, top, widthPixels, heightPixels));
			currPtr->setOrigin(static_cast<float>(widthPixels) / 2.f, static_cast<float>(heightPixels) / 2.f);
			//currPtr->setPosition(0.f, 0.f);
			playerSpriteSheet.emplace_back(currPtr);
		}
	}
}

ee::Player::Player(const sf::Texture& texture, int widthPixels, int heightPixels) : 
	Actor(5.0f), 
	playerSpriteSheet(),
	unscaledSize(widthPixels, heightPixels)
{
	initSpriteSheet(texture, widthPixels, heightPixels);
	spriteIndex = 0;
	currentSprite = playerSpriteSheet[spriteIndex];

	//set move speed based on size of sprite image
	updateMoveSpeedBasedOnSize();

	//movement related fields
	updateSwapDistance();
	verticalWalkDistance = 0;
	horrizontalWalkDistance = 0;

	spatialHash_insertSelf();

	prepareCollisionBoxes();
}


ee::Player::~Player()
{
	spatialhash_removeSelf();
}

void ee::Player::draw(sf::RenderWindow & window) const
{
	window.draw(*currentSprite);

}

void ee::Player::setScale(float scaleFactor)
{
	//change scale for every image in the sprite sheet (this will update current sprite)
	for (auto currentSprite : playerSpriteSheet) {
		//do not differentiate between x and y
		currentSprite->setScale(scaleFactor, scaleFactor);
	}
	updateMoveSpeedBasedOnSize();
	updateSwapDistance();
}

float ee::Player::getScale()
{
	//seting scale does requires both x and y are same, so returning either does the job.
	return currentSprite->getScale().x;
}

void ee::Player::moveUp()
{
	genericMove(2, 0, -moveSpeed, verticalWalkDistance);
}

void ee::Player::moveDown()
{
	genericMove(0, 0, moveSpeed, verticalWalkDistance);
}

void ee::Player::moveLeft()
{
	genericMove(1, -moveSpeed, 0, horrizontalWalkDistance);
}

void ee::Player::moveRight()
{
	genericMove(3, moveSpeed, 0, horrizontalWalkDistance);
}

void ee::Player::moveUpLeft()
{
	float angularSpeed = getAngularSpeed();
	genericMove(2, -angularSpeed, -angularSpeed, verticalWalkDistance);
}

void ee::Player::moveUpRight()
{
	float angularSpeed = getAngularSpeed();
	genericMove(2, angularSpeed, -angularSpeed, verticalWalkDistance);
}

void ee::Player::moveDownLeft()
{
	float angularSpeed = getAngularSpeed();
	genericMove(0, -angularSpeed, angularSpeed, horrizontalWalkDistance);
}

void ee::Player::moveDownRight()
{
	float angularSpeed = getAngularSpeed();
	genericMove(0, angularSpeed, angularSpeed, horrizontalWalkDistance);
}

/**
Moves current sprite by deltaX and deltaY.

@param correctColumn - the column in sprite sheet for current direction
@param deltaX - the change in horrizontal distance to apply to sprite.
@param deltaY - the change in vertical distance to apply to sprite.
@param primaryWalkDirectionDistance - the distance walked to determine if image should be swapped.
this will either be verticalDistanceWalked or horrizontalDistanceWalked.
*/
void ee::Player::genericMove(int correctColumn, float deltaX, float deltaY, const float primaryWalkDirectionDistance)
{
	if (validMoveDelta(deltaX, deltaY)) {
		updateHashFromTo(deltaX, deltaY);
		currentSprite->move(deltaX, deltaY);
		horrizontalWalkDistance += deltaX;
		verticalWalkDistance += deltaY;
		updateSpriteImage(correctColumn);
		updateImageBasedOnWalkDistance(correctColumn, primaryWalkDirectionDistance);
	}
}


void ee::Player::updateSpriteImage(int correctColumn)
{
	//for every image column, there are two images. 
	//thus, dividing the sprite index by 2 determines the column
	if (spriteIndex / 2 != correctColumn) {

		//Since there are two images for every column, the correct column is calculated by multiplying by 2
		//since there are two images per column, you can determine if the first image or second image is loaded by modding by 
		spriteIndex = correctColumn * 2 + spriteIndex % 2;

		swapImagesToNewIndex();
	}

}


/**
Updates the image based on a distance walked. correctColumn determines the direction
the sprite is currently facing. The current image of the direction is determined using
modulus and the distance the sprite has walked in the direction.

@usage: Simply provide the correct column number (this determines direction) and
provide a value that represent the distance walked in the direction.

@param correctColumn - the column representing the sprites direction (look at spritesheet file)
@param walkDistance - the distance walked in the direction (either horrizontal or vertical); for
upward and downward movements, provide vertical distance walked; for left or right movements,
provide horrizontal distance walked.
*/
void ee::Player::updateImageBasedOnWalkDistance(int correctColumn, float walkDistance)
{
	//round float towards zero
	int dist = static_cast<int>(std::abs(walkDistance));
	int walkOffset = (dist / swapDistance) % 2;

	//2 * column since each column contains two images (and sheet has been linearized
	int newIndex = 2 * correctColumn + walkOffset;
	if (playerSpriteSheet[newIndex] != currentSprite) {
		spriteIndex = newIndex;
		swapImagesToNewIndex();
	}
}

void ee::Player::swapImagesToNewIndex()
{
	playerSpriteSheet[spriteIndex]->setPosition(currentSprite->getPosition());
	currentSprite = playerSpriteSheet[spriteIndex];
}

void ee::Player::updateMoveSpeedBasedOnSize()
{
	float scale = getScale();
	moveSpeed = currentSprite->getTextureRect().width / 5.f;
	moveSpeed *= scale;
}

void ee::Player::updateSwapDistance()
{
	int widthPixels = currentSprite->getTextureRect().width;
	int heightPixels = currentSprite->getTextureRect().height;
	swapDistance = widthPixels < heightPixels ? widthPixels : heightPixels;
	swapDistance = static_cast<int>(swapDistance * getScale());
}

float ee::Player::getAngularSpeed()
{
	//calculate movement speed using pythagorean's theorm and the fact
	//that angular speed is a 45 degree triangle (thus a & b are same magnitude)
	//thus: c^2 = a^2 + b^2; which is: c^2 = 2a^2
	//by algrebraic manipulation: ((c^2)/2)^(1/2) = a
	float result = std::powf(moveSpeed, 2);
	result /= 2;
	return std::powf(result, 0.5000f);
}

bool ee::Player::validMoveDelta(const float deltaX, const float deltaY)
{
	//check for collisions by getting neighbors from spatial hash map
	if (currentSprite && Actor::spatialHash && !smartThis.expired()) {
		auto currPos = currentSprite->getPosition();
		Actor::spatialHash->getNearby(currPos.x + deltaX, currPos.y + deltaY, this->nearbyActors);

		//check for collision with nearby actors
		for (auto iter : nearbyActors) {
			if (auto otherActor = iter.lock()) {
				// needs to consider new value
				const auto smartThisShared = smartThis.lock();
				if (otherActor->collides(smartThisShared, deltaX, deltaY)) {
					return false;
				}
			}
		}
	}
	return true;
}

bool ee::Player::collides(const std::shared_ptr<const Actor>& otherActor, const float deltaX, const float deltaY) const
{
	return false;
}

void ee::Player::prepareCollisionBoxes() const
{
	//create a single rectangle to be maintained by the player 
	collisionBoxes.resize(1);
}

void ee::Player::updateHashFromTo(const float deltaX, const float deltaY)
{
	//if all conditions for spatial hash are met, and there is a current sprite
	if (smartThis.lock() && Actor::spatialHash && currentSprite) {
		auto curPos = currentSprite->getPosition();
		Actor::spatialHash->updateFromTo(curPos.x, curPos.y, smartThis, curPos.x + deltaX, curPos.y + deltaY);
	}
}


void ee::Player::spatialHash_insertSelf()
{
	auto shrThis = smartThis.lock();
	if (shrThis && Actor::spatialHash && currentSprite) {
		auto pos = currentSprite->getPosition();
		spatialHash->add(pos.x, pos.y, smartThis);
	}
}

void ee::Player::spatialhash_removeSelf()
{
}

float ee::Player::getX() const
{
	if (currentSprite) {
		return currentSprite->getPosition().x;
	}
	return 0.f;
}

float ee::Player::getY() const
{
	if (currentSprite) {
		return currentSprite->getPosition().y;
	}
	return 0.0f;
}

void ee::Player::getInNearbyVehicle()
{
	//check if player already occupies a vehicle

	//Use spatial hashing or spatial mapping to determine nearby cells with vehicles?
	if (Actor::spatialHash && !smartThis.expired() && currentSprite) {
		auto pos = currentSprite->getPosition();
		Actor::spatialHash->getNearby(pos.x, pos.y, this->nearbyActors);
		for (auto nearbyActor : nearbyActors) {
			if (auto vehicle = std::dynamic_pointer_cast<ee::Vehicle>(nearbyActor.lock())) {
				std::cout << "You're next to a vehicle!" << std::endl;
				std::string str = (vehicle->actorValidForBoard(smartThis.lock())) ? "true" : "false";
				std::cout << "close enough to board: " << str << std::endl;
			}
		}
	}
}

void ee::Player::updateCollisionBoxes(const float deltaX, const float deltaY) const
{
	if (currentSprite) {
		if (const sf::Texture* texture = currentSprite->getTexture()) {
			//float scaleX = currentSprite->getScale().x;
			//float scaleY = currentSprite->getScale().y;

			////sprite doesn't use entire size of texture, therefore cannot simply scale based on texture size
			//float scaledWidth = unscaledSize.x * scaleX; 
			//float scaledHeight = unscaledSize.y * scaleY;

			//TODO move the definitions inside of the constructor and elimiate previous variables when they're no longer needed
			sf::Vector2f unscaledSize(static_cast<float>(unscaledSize.x), static_cast<float>(unscaledSize.y));
			sf::Vector2f deltaXY(deltaX, deltaY);

			rectFromCenteredTransform(collisionBoxes[0], *currentSprite, deltaXY, unscaledSize);

			////sf::Vector2f futurePnt = currentSprite->getPosition();
			//sf::Vector2f futurePnt(deltaX, deltaY);
			////futurePnt.x += deltaX; TODO: remove; transform should calculate the current position?
			////futurePnt.y += deltaY;

			////deltaX is used to calculate the future position of the move, topLeft would be 0 , 0 but instead is 0+ deltaX, 0 + deltaY
			//sf::Vector2f topLeft = currentSprite->getTransform().transformPoint(sf::Vector2f(futurePnt.x, futurePnt.y));
			//sf::Vector2f topRight = currentSprite->getTransform().transformPoint(sf::Vector2f(scaledWidth + futurePnt.x, futurePnt.y));
			//sf::Vector2f bottomLeft = currentSprite->getTransform().transformPoint(sf::Vector2f(futurePnt.x, scaledHeight + futurePnt.y));
			//sf::Vector2f bottomRight = currentSprite->getTransform().transformPoint(sf::Vector2f(scaledWidth + futurePnt.x, scaledHeight + futurePnt.y));

			//vector2fToPnt(topLeft, collisionBoxes[0].pntTopLeft);
			//vector2fToPnt(topRight, collisionBoxes[0].pntTopRight);
			//vector2fToPnt(bottomLeft, collisionBoxes[0].pntBottomLeft);
			//vector2fToPnt(bottomRight, collisionBoxes[0].pntBottomRight);
		}
	}
}
