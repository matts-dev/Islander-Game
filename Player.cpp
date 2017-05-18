#include "Player.h"
#include<SFML/Graphics.hpp>
#include<cmath>

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
			playerSpriteSheet.emplace_back(currPtr);
		}
	}
}

ee::Player::Player(const sf::Texture& texture, int widthPixels, int heightPixels) : Actor(5.0f), playerSpriteSheet()
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
}


ee::Player::~Player()
{
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
	currentSprite->move(0, -moveSpeed);
	verticalWalkDistance += -moveSpeed;
	updateSpriteImage(2);
	updateImageBasedOnWalkDistance(2, verticalWalkDistance);

}

void ee::Player::moveDown()
{
	currentSprite->move(0, moveSpeed);
	verticalWalkDistance += moveSpeed;
	updateSpriteImage(0);
	updateImageBasedOnWalkDistance(0, verticalWalkDistance);
}

void ee::Player::moveLeft()
{
	currentSprite->move(-moveSpeed, 0);
	horrizontalWalkDistance += -moveSpeed;
	updateSpriteImage(1);
	//updateHorrizontalImage(1);
	updateImageBasedOnWalkDistance(1, horrizontalWalkDistance);

}

void ee::Player::moveRight()
{
	currentSprite->move(moveSpeed, 0);
	horrizontalWalkDistance += moveSpeed;
	updateSpriteImage(3);
	//updateHorrizontalImage(3);
	updateImageBasedOnWalkDistance(3, horrizontalWalkDistance);


}

void ee::Player::moveUpLeft()
{
}

void ee::Player::moveUpRight()
{
}

void ee::Player::moveDownLeft()
{
}

void ee::Player::moveDownRight()
{
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
