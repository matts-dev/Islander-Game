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
		unordered_map<short, shared_ptr<sf::Sprite>> components;
		vector<sf::Sprite> plankBlocks;
		void initPlankBlocks();


		//width should be event
		char const widthBlocks = 6;
		char const heightBlocks = 10;

		//helper functions
		void correctShipCorners();
		/**convert x and y coordinate into a single short for indexing*/
		short getPosKey(char x, char y);
	public:
		Ship();
		~Ship();

		// Inherited via Actor
		virtual void draw(sf::RenderWindow & window) const override;
	};
};

