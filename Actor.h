#pragma once

#include<SFML/Graphics.hpp>
#include<memory>

using std::shared_ptr;

namespace ee {
	/*
	Abstract class that all game world objects should inherit from.
	*/
	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		//pure virtual function that must be overriden.
		virtual void draw(sf::RenderWindow& window) const = 0;
	};
};

