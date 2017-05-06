#include "Actor.h"
#include<SFML\Graphics.hpp>

using std::shared_ptr;
using std::make_shared;

ee::Actor::Actor(const sf::Texture& texture)
{
	sprite = make_shared<sf::Sprite>(texture);
}


ee::Actor::~Actor()
{
}

void ee::Actor::draw(sf::RenderWindow & window)
{
	window.draw(*sprite);
	
}
