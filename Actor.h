#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>
#include"Utility.h"

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
		//spatial hashing stuff
		std::weak_ptr<Actor> smartThis;
		virtual void spatialHash_insertSelf() = 0;
		virtual void spatialhash_removeSelf() = 0;
		virtual void updateHashFromTo(const float deltaX, const float deltaY) = 0;
		std::vector<std::weak_ptr<Actor>> nearbyActors;

	protected:
		float moveSpeed;

		//** simply a container for temporary collision boxes, changing in state isn't important for constness*/ //TODO move to interface 
		mutable std::vector<utility::mxb::Rect> collisionBoxes;

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
		virtual float getX() const = 0;
		virtual float getY() const = 0;

		//TODO: change methods to take references for performance 
		//TODO refactor collision box stuff to an interface to reduce the actor class?
		virtual bool collides(const std::shared_ptr<const Actor>& otherActor, const float deltaX = 0, const float deltaY = 0) const = 0;
		virtual void updateCollisionBoxes(const float deltaX, const float deltaY) const = 0;
		void rectFromTransform(utility::mxb::Rect& buffer, const sf::Transform& transform, const sf::Vector2f& deltaXY, sf::Vector2f& scaledSizeXY) const;
		virtual const std::vector<utility::mxb::Rect>& getCollisionRect(const float deltaX = 0, const float deltaY = 0) const;
		virtual void prepareCollisionBoxes() const = 0;
	};
};

