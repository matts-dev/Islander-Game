#pragma once

#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>
#include"Actor.h"

using std::shared_ptr;
using std::vector;

namespace ee {
	class Player : public Actor
	{
		vector<sf::Sprite> playerSpriteSheet;
		void initSpriteSheet();
		shared_ptr<sf::Sprite> sprite;
	public:
		Player(const sf::Texture& texture, int widthPixels, int heightPixels);
		virtual ~Player();

		void draw(sf::RenderWindow& window) const override;
	};
};

