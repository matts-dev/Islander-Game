#pragma once

#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>
#include"Actor.h"

namespace ee {
	class Player : public Actor
	{
	private:
		//transformations to player sprite must be applied to every sprite in the container
		std::vector<std::shared_ptr<sf::Sprite>> playerSpriteSheet;
		std::shared_ptr<sf::Sprite> currentSprite;
		int spriteIndex;

		//construtor helper functions
		void initSpriteSheet(const sf::Texture& texture, int widthPixels, int heightPixels);
	public:
		Player(const sf::Texture& texture, int widthPixels, int heightPixels);
		virtual ~Player();

		void draw(sf::RenderWindow& window) const override;

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
		virtual float getX() override;
		virtual float getY() override;

		virtual void getInNearbyVehicle();

	private:
		// Spatial Hashing Functions
		virtual void spatialHash_insertSelf() override;
		virtual void spatialhash_removeSelf() override;
		virtual void updateHashFromTo(const float & deltaX, const float & deltaY) override;

	private:
		void genericMove(int correctColumn, float deltaX, float deltaY, const float& primaryWalkDirectionDistance);
		//helper functions
		/** the distance walked before an image swap is warrented*/
		int swapDistance; 
		/** the distance walked horrizontally*/
		float horrizontalWalkDistance;
		/** the distance walked vertically */
		float verticalWalkDistance;
		void updateSpriteImage(int correctColumn);
		void updateImageBasedOnWalkDistance(int correctColumn, float walkDistance);
		void swapImagesToNewIndex();
		void updateMoveSpeedBasedOnSize();
		void updateSwapDistance();
		float getAngularSpeed();

		/** Helper function that returns true if the player can be moved by the parameter delta values */
		bool validMoveDelta(const float& deltaX, const float& deltaY);

		virtual bool collides(const sf::IntRect & rectToTest) const override;





	};
};

