#pragma once

//forward declarations
namespace sf {
	class RenderWindow;
}

class Game
{
public:
	Game();
	~Game();
	void io();
	void draw(sf::RenderWindow& window);
};

