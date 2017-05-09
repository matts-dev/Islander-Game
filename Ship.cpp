#include "Ship.h"
#include "Textures.h"
#include "RNG.h"
#include <vector>

//usings 
using std::vector;
using std::make_shared;
using std::shared_ptr;

//foward declarations
//void createSpriteBlocks(std::vector<sf::Sprite>& container, const sf::Texture& texture, int dimension);

ee::Ship::Ship() : Actor()
{
	initPlankBlocks();
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

	correctShipCorners();
}

ee::Ship::~Ship()
{
}

void ee::Ship::draw(sf::RenderWindow & window) const
{

	//iterate over the entire components and draw, STL gaurantees iterators are O(n)
	for (auto it : this->components) {
		window.draw(*(it.second));
	}


}


//void createSpriteBlocks(std::vector<sf::Sprite>& container, const sf::Texture& texture, int dimension) {
//	container.clear();
//	//create a sprite for every block in the sheet
//	for (int i = 0; i < 12; ++i) {
//		sf::Sprite temp(texture, sf::IntRect(0, i * dimension, dimension, dimension));
//
//		//make a copy into the container
//		container.push_back(temp);
//
//	}
//}

/** puts two characters into a short via bit shifting */
short ee::Ship::getPosKey(char x, char y) {
	short key = x;

	//shift over the size of char (should be half the size of short on most platforms)
	key <<= sizeof(char) * 8;

	//OR in the bottom 8 bits of y value (x should now be displaced enough)
	key |= y;

	return key;
}

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
			plankBlocks.push_back(temp);
		}
	}
}

void ee::Ship::correctShipCorners()
{
	vector<int> leftCornersTop;
	vector<int> rightCornersTop;

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
		leftCornersTop.push_back(leftCornerForRow);
		rightCornersTop.push_back(rightCornerForRow);

	}

	//Assign corner peices
	initPlankBlocks();
	int pixelsDimension = plankBlocks[0].getTextureRect().width;

	//add corner peices
	for (unsigned int i = 0; i < leftCornersTop.size(); ++i) {
		//At the left corner position, set it to a corner sprite
		auto leftCorner = make_shared<sf::Sprite>(plankBlocks[8]);
		leftCorner->setPosition(static_cast<float>(leftCornersTop[i] * pixelsDimension), static_cast<float>(i * pixelsDimension));
		this->components[getPosKey(leftCornersTop[i], i)] = leftCorner;

		//At the right corner position, set it to a corner peice
		auto rightCorner = make_shared<sf::Sprite>(plankBlocks[8]);
		rightCorner->setScale(-1.f, 1.f);
		auto ori = rightCorner->getOrigin();
		ori.x += rightCorner->getTextureRect().width;
		rightCorner->setOrigin(ori);
		rightCorner->setPosition(static_cast<float>(rightCornersTop[i] * pixelsDimension), static_cast<float>(i * pixelsDimension));
		this->components[getPosKey(rightCornersTop[i], i)] = rightCorner;
	}
}
