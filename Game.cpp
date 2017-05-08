#include "Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>

#include"Actor.h"
#include"Player.h"
#include"Ship.h"
#include"Textures.h"

using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

ee::Game::Game()
{
	textures = Textures::getInstance();
	shared_ptr<sf::Texture const> actorTexture = textures->getActorSheet();
	auto player1 = make_shared<Player>(*actorTexture);
	players.push_back(player1);

	auto ship = make_shared<Ship>();
	nonPlayerActors.push_back(ship);
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
	//THIS METHOD SHOULD BE CHANGED TO HEAP STRUCTURE USING ACTORS PRIORTY FOR DRAW ORDER

	//draw ship before player
	for (auto actorPtr : nonPlayerActors) {
		actorPtr->draw(window);
	}

	//draw players until heap is used
	for (auto playerPtr : players) {
		playerPtr->draw(window);
	}
}
