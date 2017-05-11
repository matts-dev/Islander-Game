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
		//transformations to player sprite must be applied to every sprite in the container
		vector<shared_ptr<sf::Sprite>> playerSpriteSheet;
		shared_ptr<sf::Sprite> currentSprite;

		//construtor helper functions
		void initSpriteSheet(const sf::Texture& texture, int widthPixels, int heightPixels);
	public:
		Player(const sf::Texture& texture, int widthPixels, int heightPixels);
		virtual ~Player();

		void draw(sf::RenderWindow& window) const override;

		// Inherited via Actor
		virtual void setScale(float scaleFactor) override;
		virtual float getScale() override;
	};
};

