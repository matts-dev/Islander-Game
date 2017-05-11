#pragma once
#include"Actor.h"
#include<memory>
#include<vector>
#include<unordered_map>
#include<SFML/Graphics.hpp>

using std::shared_ptr;
using std::unordered_map;
using std::vector;

namespace ee {
	class Ship : public Actor
	{
		//Texture blocks to use for copying
		static vector<sf::Sprite> plankBlocks;
		static void initPlankBlocks();

		//Actual components that make up the ship (blocks you see)
		unordered_map<short, shared_ptr<sf::Sprite>> components;

		//width should be event
		char const widthBlocks = 7;
		char const heightBlocks = 15;

		//index = row, value = col; ie vector[row] returns col, 
		vector<int> topLeftCorners;
		vector<int> topRightCorners;

		//constructor helper functions
		void createRectangleOfPlankSprites();
		void handleShipCorners();
		void calculateCornerPositions();
		void positionCornerPeices();
		void trimEdgeBlocksAway();
		void calculateCenterLocation();

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
	};
};

