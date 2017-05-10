#include "Player.h"
#include<SFML/Graphics.hpp>

using std::shared_ptr;
using std::make_shared;

void ee::Player::initSpriteSheet()
{
	//initialize sprite sheet only once
	if (Player::playerSpriteSheet.size() == 0) {

	}
}

ee::Player::Player(const sf::Texture& texture, int widthPixels, int heightPixels) : Actor(), playerSpriteSheet()
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
