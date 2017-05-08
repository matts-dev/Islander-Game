#pragma once
#include"Actor.h"
#include<memory>
#include<unordered_map>
#include<SFML/Graphics.hpp>

using std::shared_ptr;
using std::unordered_map;

namespace ee {
	class Ship : public Actor
	{
		unordered_map<short, shared_ptr<sf::Sprite>> components;
		shared_ptr<sf::Sprite> temporarySprite;
		char const widthBlocks = 5;
		char const heightBlocks = 10;
	public:
		Ship();
		~Ship();

		// Inherited via Actor
		virtual void draw(sf::RenderWindow & window) const override;
	};
};

