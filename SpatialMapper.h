#pragma once
#include<memory>
#include"HashNode.h"
namespace ee {
	//forward declarations
	class Actor;

	class SpatialMapper final
	{
		std::unique_ptr<Actor*[]> hashMap;
		int gridSize;
		int tableSize;
		int hornerNumber;
	public:
		SpatialMapper(int gridSize, int tableSize);
		~SpatialMapper();
		int hash(const float& x, const float& y);
	};
}
