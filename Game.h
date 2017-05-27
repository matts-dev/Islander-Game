#pragma once
#include<vector>
#include<memory>

//non ee forward declarations
namespace sf {
	class RenderWindow;
	class View;
}


namespace ee {

	class Actor;
	class Textures;

	class Game
	{
	private:
		std::vector<std::shared_ptr<Actor>> players;
		std::vector<std::shared_ptr<Actor>> nonPlayerActors;
		std::shared_ptr<Actor> player;
		std::shared_ptr<Actor> controlTarget;
		std::shared_ptr<Textures const> textures;
		std::shared_ptr<sf::View> camera;
		bool moveCamera;

		bool developerMode;

	public:
		Game();
		~Game();
		void io();
		void logic();
		void draw(sf::RenderWindow& window);

		//helper functions
	private:
		void ioMovement();
		void updateViewToControlled(sf::RenderWindow& window);
	};
};

