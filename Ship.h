#pragma once
#include"Actor.h"
#include<memory>
#include<SFML\Graphics.hpp>

using std::shared_ptr;

namespace ee {
	class Ship : public Actor
	{
		shared_ptr<sf::Sprite> temporarySprite;
	public:
		Ship();
		~Ship();

		// Inherited via Actor
		virtual void draw(sf::RenderWindow & window) const override;
	};
};

