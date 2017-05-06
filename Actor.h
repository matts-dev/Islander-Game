#pragma once

#include<SFML/Graphics.hpp>
#include<memory>

using std::shared_ptr;

namespace ee {
	class Actor
	{
		shared_ptr<sf::Sprite> sprite;
	public:
		Actor(const sf::Texture& texture);
		~Actor();

		void draw(sf::RenderWindow& window);
	};
};

