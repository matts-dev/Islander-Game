#include "Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>

#include"Actor.h"
#include"Textures.h"

using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

ee::Game::Game()
{
	textures = Textures::getInstance();
	shared_ptr<sf::Texture const> actorTexture = textures->getActorSheet();
	auto player1 = make_shared<Actor>(*actorTexture);
	players.push_back(player1);
}

ee::Game::~Game()
{
}

void ee::Game::io()
{
}

void ee::Game::logic()
{
}

void ee::Game::draw(sf::RenderWindow & window)
{
	for (auto playerPtr : players) {
		playerPtr->draw(window);
	}
}
