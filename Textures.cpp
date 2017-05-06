#include "Textures.h"
#include "ResourcePathHandler.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include<exception>
#include<string>

using std::make_shared;
using std::weak_ptr;
using std::string;
ee::Textures::Textures()
{
	this->grassSheet = make_shared<sf::Texture>();
	this->actorSheet = make_shared<sf::Texture>();
	this->waterSheet = make_shared<sf::Texture>();

	//string actorPath = "assets\\textures\\GenericActorSprite.png";
	string actorPath = ResourcePathHandler::getActorLocation();
	if (!this->actorSheet->loadFromFile(actorPath)) {
		throw std::exception(("couldn't load texture: " + actorPath).c_str());
	}

	string grassPath = "assets\\textures\\grass2.png";
	if (!this->grassSheet->loadFromFile(grassPath)) {
		throw std::exception(("couldn't load texture: " + grassPath).c_str());
	}

	string waterPath = "assets\\textures\\grass2.png";
	if (!this->grassSheet->loadFromFile(waterPath)) {
		throw std::exception(("couldn't load texture: " + waterPath).c_str());
	}

}


ee::Textures::~Textures()
{
}

/*
Get a weak pointer to the actor texture.

Singleton is constant, therefore methods need to be const safe.

Return type converts texture to constant so method is truely const safe
and that texture cannot be corrupted by usage.
*/
shared_ptr<sf::Texture const> ee::Textures::getActorSheet() const
{
	return actorSheet;
}

//SINGLETON LOGIC
shared_ptr<ee::Textures const> ee::Textures::singleton = nullptr;
shared_ptr<ee::Textures const> ee::Textures::getInstance()
{
	if (!Textures::singleton) {
		singleton = shared_ptr<Textures const>(new Textures());
	}
	return singleton;
}


