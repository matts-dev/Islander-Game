#pragma once
#include"Actor.h"
#include"Vehicle.h"
#include<memory>
#include<vector>
#include<unordered_map>
#include<SFML/Graphics.hpp>



namespace ee {
	class Ship : public Vehicle
	{
		//Texture blocks to use for copying
		static std::vector<sf::Sprite> plankBlocks;
		static void initPlankBlocks();

		//Actual components that make up the ship (blocks you see)
		std::unordered_map<short, std::shared_ptr<sf::Sprite>> components;
		sf::RectangleShape boundingBox;
		
		//set to greater than 1.0f to make the bounding box larger than the ship
		float bBoxAdtlScaleFactor = 1.0f;

		char const widthBlocks = 7;
		char const heightBlocks = 15;

		//index = row, value = col; ie vector[row] returns col, 
		std::vector<int> topLeftCorners;
		std::vector<int> topRightCorners;

		//constructor helper functions
		void createRectangleOfPlankSprites();
		void handleShipCorners();
		void calculateCornerPositions();
		void positionCornerPeices();
		void trimEdgeBlocksAway();
		void calculateCenterLocation();
		void setupBoundingBox();

		/**convert x and y coordinate into a single short for indexing*/
		short getPosKey(char x, char y);
	public:
		Ship();
		virtual ~Ship();

		void setRotation(float rotationInDegrees);
		float getRotation();

		void setPosition(float x, float y);

		// Inherited via Actor
		virtual void draw(sf::RenderWindow & window) const override;
		
		// Inherited via Actor
		virtual void setScale(float scaleFactor) override;
		virtual float getScale() override;
		virtual void moveUp() override;
		virtual void moveDown() override;
		virtual void moveLeft() override;
		virtual void moveRight() override;
		virtual void moveUpLeft() override;
		virtual void moveUpRight() override;
		virtual void moveDownLeft() override;
		virtual void moveDownRight() override;
		virtual float getX() const override;
		virtual float getY() const override;

		virtual bool collides(std::shared_ptr<const Actor> otherActor) const override;

		// TODO: clean up ship and player headers to make more readable 
		// spatial hashing (called automatically in actor constructor) 
		virtual void spatialHash_insertSelf() override;
		virtual void spatialhash_removeSelf() override;
		virtual void updateHashFromTo(const float deltaX, const float deltaY) override;

	private:
		sf::Vector2f getPosition();

		// Inherited via Vehicle
		virtual bool actorValidForBoard(std::shared_ptr<Actor> boardRequestingActor) override;

	};
};

