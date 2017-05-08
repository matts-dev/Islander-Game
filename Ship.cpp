#include "Ship.h"
#include "Textures.h"
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
	populateComponents(blocksToUse, *texture, 32);

	//create the components of the ship
	for (char i = 0; i < widthBlocks; ++i) {
		for (char j = 0; j < heightBlocks; ++j) {
			//TODO randomly pick a plank texture (currently only using 3rd)
			sf::Sprite block = blocksToUse[3];

			block.setPosition(i * 32, j * 32);

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