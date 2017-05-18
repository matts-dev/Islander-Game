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
	auto player1 = make_shared<Player>(*actorTexture, 16, 16);
	controlTarget = player1;
	player1->setScale(2.0f);
	players.emplace_back(player1);

	auto ship = make_shared<Ship>();
	nonPlayerActors.emplace_back(ship);
	ship->setPosition(500.f, 500.f);

	developerMode = true;
}

ee::Game::~Game()
{

}

void ee::Game::io()
{
	ioMovement();
	if (developerMode) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			//for now will be the first ship of the game
			auto actorPtr = nonPlayerActors[0];
			auto shipPtr = std::dynamic_pointer_cast<Ship>(actorPtr);
			if (shipPtr) {
				float rot = shipPtr->getRotation();
				shipPtr->setRotation(rot + 3.f);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			//for now will be the first ship of the game
			auto actorPtr = nonPlayerActors[0];
			auto shipPtr = std::dynamic_pointer_cast<Ship>(actorPtr);
			if (shipPtr) {
				float rot = shipPtr->getRotation();
				shipPtr->setRotation(rot - 3.f);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			auto newShip = make_shared<Ship>();
			nonPlayerActors.emplace_back(newShip);
		}
		//change scale to smaller
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			auto ship = nonPlayerActors[0];
			auto player = players[0];
			ship->setScale(ship->getScale() - 0.05f);
			player->setScale(player->getScale() - 0.05f);
		}
		//change scale to larger
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			auto ship = nonPlayerActors[0];
			auto player = players[0];
			ship->setScale(ship->getScale() + 0.05f);
			player->setScale(player->getScale() + 0.05f);
		}
	}
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

void ee::Game::ioMovement()
{
	//Handle W pressed (and potentially W+A and W+D)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			controlTarget->moveUpLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			controlTarget->moveUpRight();
		}
		else {
			controlTarget->moveUp();
		}

	}
	//Handle S pressed (and potentially S+A and S+D
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			controlTarget->moveDownLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			controlTarget->moveDownRight();
		}
		else {
			controlTarget->moveDown();
		}
	}
	//Handle only A pressed
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		controlTarget->moveLeft();
	}
	//Handle only D pressed
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		controlTarget->moveRight();
	}
}
