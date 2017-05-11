#include "Player.h"
#include<SFML/Graphics.hpp>

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

ee::Player::Player(const sf::Texture& texture, int widthPixels, int heightPixels) : Actor(), playerSpriteSheet()
{
	initSpriteSheet(texture, widthPixels, heightPixels);
	//currentSprite = make_shared<sf::Sprite>(texture);
	currentSprite = playerSpriteSheet[0];
}


ee::Player::~Player()
{
}

void ee::Player::draw(sf::RenderWindow & window) const
{
	window.draw(*currentSprite);

}
