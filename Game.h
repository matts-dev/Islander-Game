#pragma once

//forward declarations
namespace sf {
	class RenderWindow;
}

namespace ee {
	class Game
	{
	public:
		Game();
		~Game();
		void io();
		void logic();
		void draw(sf::RenderWindow& window);
	};
};

