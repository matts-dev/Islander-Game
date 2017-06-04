#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include"Factory.h"

namespace ee {
	/*
	Abstract class that all game world objects should inherit from.
	*/
	class Actor 
	{
	public:
		//statics related to spatial hashing tracking
		static std::unique_ptr<class SpatialHash> spatialHash;
		static void initSpatialHash(const int gridSize, const int tableSize);
		void enableSpatialHashing(std::weak_ptr<Actor> smartPointerToSelf);

	protected:
		std::weak_ptr<Actor> smartThis;
		virtual void spatialHash_insertSelf() = 0;
		virtual void spatialhash_removeSelf() = 0;
		virtual void updateHashFromTo(const float& deltaX, const float& deltaY) = 0;

	protected:
		float moveSpeed;

		Actor(float moveSpeed);
	public:
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

		virtual bool collides(const sf::IntRect& rectToTest) const = 0;
	};
};

