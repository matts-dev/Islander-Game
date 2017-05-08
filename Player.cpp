#include "Player.h"
#include<SFML/Graphics.hpp>

using std::shared_ptr;
using std::make_shared;

ee::Player::Player(const sf::Texture& texture) : Actor()
{
	sprite = make_shared<sf::Sprite>(texture);
}


ee::Player::~Player()
{
}

void ee::Player::draw(sf::RenderWindow & window) const
{
	window.draw(*sprite);

}
