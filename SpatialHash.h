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
		std::unique_ptr<std::shared_ptr<HashNode<sf::Vector2i, std::weak_ptr<Actor>>>[]> hashMap;
		int gridSize;
		int tableSize;
		int hornerNumber;
		int hashFloat(const float& x, const float& y);
		int hashGrid(const int& horrizontalGrid, const int& verticalGrid);
	public:
		SpatialHash(int gridSize, int tableSize);
		~SpatialHash();

		//add an actor to the spatial map
		void add(const float& x, const float& y, std::weak_ptr<Actor> actor);

		//removes an actor from the spatial map
		bool remove(const float& x, const float& y, std::weak_ptr<Actor> actor);

		//get a vector of actors in the grid and all neighboring grids
		std::vector<std::weak_ptr<Actor>> getNearby(const float& x, const float& y);

		//removes origional from table, then adds back to table in new position (only if necessary)
		void updateFromTo(const float& oldX, const float& oldY, std::weak_ptr<Actor> actor, const float& newX, const float& newY);
	};
}
