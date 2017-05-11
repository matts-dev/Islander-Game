#pragma once
#include<vector>
#include<memory>

//non ee forward declarations
namespace sf {
	class RenderWindow;
}

using std::vector;
using std::shared_ptr;


namespace ee {

	class Actor;
	class Textures;

	class Game
	{
	private:
		vector<shared_ptr<Actor>> players;
		vector<shared_ptr<Actor>> nonPlayerActors;
		shared_ptr<Actor> player;
		shared_ptr<Actor> controlTarget;
		shared_ptr<Textures const> textures;

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
	};
};

