#include "Ship.h"
#include "Textures.h"



ee::Ship::Ship() : Actor()
{
	auto textureHolder = Textures::getInstance();
	auto texture = textureHolder->getPlankSheet();
	this->temporarySprite = std::make_shared<sf::Sprite>(*texture);
}


ee::Ship::~Ship()
{
}

void ee::Ship::draw(sf::RenderWindow & window) const
{
	if (temporarySprite) {
		window.draw(*temporarySprite);
	}
}
