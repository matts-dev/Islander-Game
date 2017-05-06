#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

#include"Game.h"

int main() {
	bool dev = true;
	ee::Game game;

    //round towards zero
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(1920*.65), static_cast<int>(1080*.65)), "Islander!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//LOGIC
		game.io();
		game.logic();

		// RENDER
		window.clear();
		game.draw(window);
		window.display();

		if (dev && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			break;
		}

	}

	return 0;
}


