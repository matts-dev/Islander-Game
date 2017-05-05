


#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

#include"Game.h"

int main() {
	bool debug = true;
	Game game;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		game.draw(window);
		window.display();

		if (debug && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			break;
		}

	}

	return 0;
}