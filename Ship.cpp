#include "Ship.h"
#include "Textures.h"
#include "RNG.h"
#include <vector>

//usings 
using std::vector;
using std::make_shared;
using std::shared_ptr;

//foward declarations
void populateComponents(std::vector<sf::Sprite>& container, const sf::Texture& texture, int dimension);
short getPosKey(char x, char y);

ee::Ship::Ship() : Actor()
{
	auto textureHolder = Textures::getInstance();
	auto texture = textureHolder->getPlankSheet();
	this->temporarySprite = std::make_shared<sf::Sprite>(*texture);

	vector<sf::Sprite> blocksToUse;
	int pixelsDimension = 32;
	populateComponents(blocksToUse, *texture, pixelsDimension);

	//there are 4 valid textures that have corner peices, they happen to be textures 0,1,2,3
	auto rng = RNG::getInstance();
	int rInt = rng->nextRandomInt() % 4;

	//create the components of the ship
	for (char i = 0; i < widthBlocks; ++i) {
		for (char j = 0; j < heightBlocks; ++j) {
			sf::Sprite block = blocksToUse[rInt];

			//set sprites position to correct position in thread, also adjust for number of pixels in block
			block.setPosition(static_cast<float>(i * pixelsDimension), static_cast<float>(j * pixelsDimension));

			//insert a copied sprite based on the block used
			this->components[getPosKey(i, j)] = make_shared<sf::Sprite>(block);
		}
	}
}

ee::Ship::~Ship()
{
}

void ee::Ship::draw(sf::RenderWindow & window) const
{
	//for debugging
	if (temporarySprite) {
		//window.draw(*temporarySprite);
	}

	//iterate over the entire components and draw, STL gaurantees iterators are O(n)
	for (auto it : this->components) {
		window.draw(*(it.second));
	}


}


void populateComponents(std::vector<sf::Sprite>& container, const sf::Texture& texture, int dimension) {
	//create a sprite for every block in the sheet
	for (int i = 0; i < 12; ++i) {
		sf::Sprite temp(texture, sf::IntRect(0, i * dimension, dimension, dimension));

		//make a copy into the container
		container.push_back(temp);

	}
}

/** puts two characters into a short via bit shifting */
short getPosKey(char x, char y) {
	short key = x;

	//shift over the size of char (should be half the size of short on most platforms)
	key <<= sizeof(char) * 8;

	//OR in the bottom 8 bits of y value (x should now be displaced enough)
	key |= y;

	return key;
}