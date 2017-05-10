#pragma once

#include<SFML/Graphics.hpp>
#include<memory>
#include"Actor.h"

using std::shared_ptr;

namespace ee {
	class Player : public Actor
	{
		shared_ptr<sf::Sprite> sprite;
	public:
		Player(const sf::Texture& texture);
		virtual ~Player();

		void draw(sf::RenderWindow& window) const override;
	};
};

