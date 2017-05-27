#pragma once
#include<SFML/Graphics.hpp>

namespace ee {
	/*
	Abstract class that all game world objects should inherit from.
	*/
	class Actor
	{
	protected:
		float moveSpeed;
	public:
		Actor(float moveSpeed);
		virtual ~Actor();

		//pure virtual function that must be overriden.
		virtual void draw(sf::RenderWindow& window) const = 0;
		virtual void setScale(float scaleFactor) = 0;
		virtual float getScale() = 0;

		//Movement Functions
		virtual void moveUp() = 0 ;
		virtual void moveDown() = 0;
		virtual void moveLeft() = 0;
		virtual void moveRight() = 0;
		virtual void moveUpLeft() = 0;
		virtual void moveUpRight() = 0;
		virtual void moveDownLeft() = 0;
		virtual void moveDownRight() = 0;

		//Getters
		virtual float getX() = 0;
		virtual float getY() = 0;
	};
};

