#include "Ship.h"
#include "Textures.h"
#include "RNG.h"
#include <vector>

//usings 
using std::vector;
using std::make_shared;
using std::shared_ptr;

ee::Ship::Ship() : Actor()
{
	initPlankBlocks();
	createRectangleOfPlankSprites();
	handleShipCorners();
	calculateCenterLocation();

}

ee::Ship::~Ship()
{
}

void ee::Ship::setRotation(float rotationInDegrees)
{
	//update the rotation for every component.
	for (auto it : components) {
		(it.second)->setRotation(rotationInDegrees);
	}
}

/** Get rotation in degrees */
float ee::Ship::getRotation()
{
	//get first component of map
	auto it = components.begin();
	
	//get rotation (should be updated in all components)
	return (*it).second->getRotation();
}

void ee::Ship::setPosition(float x, float y)
{
	for (auto it : components) {
		(it.second)->setPosition(x, y);
	}
}


void ee::Ship::draw(sf::RenderWindow & window) const
{

	//iterate over the entire components and draw, STL gaurantees iterators are O(n)
	for (auto it : this->components) {
		window.draw(*(it.second));
	}


}

void ee::Ship::setScale(float scaleFactor)
{
	for (auto aComponent : components) {
		aComponent.second->setScale(scaleFactor, scaleFactor);
	}
}

float ee::Ship::getScale()
{
	auto aComponent = (components.begin())->second;

	//scale should be same for x and y, so returning either will be accurate for scale.
	return aComponent->getScale().x;


}

/** puts two characters into a short via bit shifting */
short ee::Ship::getPosKey(char x, char y) {
	short key = x;

	//shift over the size of char (should be half the size of short on most platforms)
	key <<= sizeof(char) * 8;

	//OR in the bottom 8 bits of y value (x should now be displaced enough)
	key |= y;

	return key;
}

std::vector<sf::Sprite> ee::Ship::plankBlocks;

void ee::Ship::initPlankBlocks()
{
	//one time init
	if (plankBlocks.size() == 0) {

		auto textureHolder = Textures::getInstance();
		auto texture = textureHolder->getPlankSheet();
		int pixelDimension = 32;

		//create a sprite for every block in the sheet
		for (int i = 0; i < 12; ++i) {
			sf::Sprite temp(*texture, sf::IntRect(0, i * pixelDimension, pixelDimension, pixelDimension));

			//make a copy into the container
			plankBlocks.emplace_back(temp);
		}
	}
}

void ee::Ship::createRectangleOfPlankSprites()
{
	int pixelsDimension = plankBlocks[0].getTextureRect().width;

	//there are 4 valid textures that have corner peices, they happen to be textures 0,1,2,3
	auto rng = RNG::getInstance();
	int rInt = rng->nextRandomInt() % 4;

	//create the components of the ship
	for (char i = 0; i < widthBlocks; ++i) {
		for (char j = 0; j < heightBlocks; ++j) {
			sf::Sprite block = plankBlocks[rInt];

			//set sprites position to correct position in thread, also adjust for number of pixels in block
			block.setPosition(static_cast<float>(i * pixelsDimension), static_cast<float>(j * pixelsDimension));

			//insert a copied sprite based on the block used
			this->components[getPosKey(i, j)] = make_shared<sf::Sprite>(block);
		}
	}
}

void ee::Ship::handleShipCorners()
{
	calculateCornerPositions();
	positionCornerPeices();
	trimEdgeBlocksAway();
}

void ee::Ship::calculateCornerPositions()
{
	//Calculate positions
	for (int i = 0; i < this->widthBlocks / 2; ++i) {
		//for every row, move corner left by i (integer division just works for left with odd)
		int leftCornerForRow = (this->widthBlocks / 2) - i;
		leftCornerForRow -= 1;	//indexing starts at zero, this corrects for that.

		//calculate the mirrow index
		int rightCornerForRow = (this->widthBlocks / 2) + i;

		//if width is odd, then move right one more block to right 
		if (this->widthBlocks % 2 == 1) {
			rightCornerForRow += 1;
		}

		//the index for this vectors represents the row in the ship that will change.
		//ie row 0 in ship will have have its corner column numbers at vector index 0
		topLeftCorners.emplace_back(leftCornerForRow);
		topRightCorners.emplace_back(rightCornerForRow);

	}
}

void ee::Ship::positionCornerPeices()
{
	//Assign corner peices
	initPlankBlocks();
	int pixelsDimension = plankBlocks[0].getTextureRect().width;

	//add top corner peices
	for (unsigned int i = 0; i < topLeftCorners.size(); ++i) {
		//At the left corner position, set it to a corner sprite
		auto leftCorner = make_shared<sf::Sprite>(plankBlocks[8]);
		leftCorner->setPosition(static_cast<float>(topLeftCorners[i] * pixelsDimension), static_cast<float>(i * pixelsDimension));
		this->components[getPosKey(topLeftCorners[i], i)] = leftCorner;

		//At the right corner position, set it to a corner peice
		auto rightCorner = make_shared<sf::Sprite>(plankBlocks[8]);
		auto rect = rightCorner->getTextureRect();
		//flip the texture
		//use a negative width - left + width because we're capturing a negative width, which means we need to offset by the width to capture the original texture
		rightCorner->setTextureRect(sf::IntRect(rect.left + rect.width, rect.top, -rect.width, rect.height));
		rightCorner->setPosition(static_cast<float>(topRightCorners[i] * pixelsDimension), static_cast<float>(i * pixelsDimension));
		this->components[getPosKey(topRightCorners[i], i)] = rightCorner;
	}

	//BOTTOM CORNERS
	//only place a single bottom corner peice
	auto bottomLeftCorner = make_shared<sf::Sprite>(plankBlocks[8]);
	auto bottomRightCorner = make_shared<sf::Sprite>(plankBlocks[8]);

	//calculate positions
	int lastRow = heightBlocks - 1;		//last row
	int leftIndex = 0;					//first column
	int rightIndex = widthBlocks - 1;	//last column

	bottomLeftCorner->setPosition(static_cast<float>(leftIndex * pixelsDimension), static_cast<float>(lastRow * pixelsDimension));
	bottomRightCorner->setPosition(static_cast<float>(rightIndex * pixelsDimension), static_cast<float>(lastRow * pixelsDimension));

	//flip left corner block vertically
	auto lRect = bottomLeftCorner->getTextureRect();
	bottomLeftCorner->setTextureRect(sf::IntRect(lRect.left, lRect.top + lRect.height, lRect.width, -lRect.height));
	
	//flip right corner block vertically and horrizontally
	auto rRect = bottomRightCorner->getTextureRect();
	bottomRightCorner->setTextureRect(sf::IntRect(rRect.left + rRect.width, rRect.top + rRect.height, -rRect.width, -rRect.height));

	this->components[getPosKey(leftIndex, lastRow)] = bottomLeftCorner;
	this->components[getPosKey(rightIndex, lastRow)] = bottomRightCorner;


}

void ee::Ship::trimEdgeBlocksAway()
{
	// for every row in the ship
	for (unsigned int i = 0; i < topLeftCorners.size(); ++i) {
		int colIndex = topLeftCorners[i];
		// for every block until you reach the corner (angled block) (columns)
		for (int j = 0; j < colIndex; ++j) {
			//trim component on left
			components.erase(getPosKey(i, j));

			//trim component on right (-1 to correct for starting at 0)
			int rightIndex = widthBlocks - i - 1;
			components.erase(getPosKey(rightIndex, j));
		}
	}
}

void ee::Ship::calculateCenterLocation()
{
	//find the center position
	int blockSize = plankBlocks[0].getTextureRect().width;
	float centerX = widthBlocks / 2.0f * blockSize;
	float centerY = heightBlocks / 2.0f * blockSize;

	//change the origin for every sprite component
	for (auto it : components) {
		auto pos = (it.second)->getPosition();

		(it.second)->setOrigin(centerX - pos.x, centerY - pos.y);
		(it.second)->setPosition(0, 0);
	}
}
