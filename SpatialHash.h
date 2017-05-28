#pragma once
#include<memory>
#include<SFML/System.hpp>
#include"HashNode.h"
namespace ee {
	//forward declarations
	class Actor;

	class SpatialHash final
	{
		//table (array) of pointers to chains: nodes<(x,y), actor>
		std::unique_ptr<HashNode<sf::Vector2i, std::weak_ptr<Actor>>*[]> hashMap;
		int gridSize;
		int tableSize;
		int hornerNumber;
		int hash(const float& x, const float& y);
	public:
		SpatialHash(int gridSize, int tableSize);
		~SpatialHash();

		//add an actor to the spatial map
		void add(const float& x, const float& y, std::weak_ptr<Actor> actor);

		//removes an actor from the spatial map
		void remove(const float& x, const float& y, std::weak_ptr<Actor> actor);

		void updateFromTo(const float& oldX, const float& oldY, std::weak_ptr<Actor> actor, const float& newX, const float& newY);

		//get a vector of actors in the grid and all neighboring grids
		std::vector<std::weak_ptr<Actor>> get(const float& x, const float& y);
	};
}
