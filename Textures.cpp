#include "Textures.h"
#include "ResourcePathHandler.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<exception>
#include<string>

using std::make_shared;
using std::weak_ptr;
using std::string;
ee::Textures::Textures()
{

	//Creat actor texture
	this->actorSheet = make_shared<sf::Texture>();
	string actorPath = ResourcePathHandler::getActorLocation();
	if (!this->actorSheet->loadFromFile(actorPath)) {
        string exceptMsg = "couldn't load texture:" + actorPath;
        std::cout<<exceptMsg<<std::endl;
        throw exceptMsg;
	}

	//create plank texture
	this->plankSheet = make_shared<sf::Texture>();
	string plankPath = ResourcePathHandler::getPlankSheetLocation();
	if (!this->plankSheet->loadFromFile(plankPath)) {
		string exceptMsg = "couldn't load texture:" + plankPath;
		std::cout << exceptMsg << std::endl;
		throw exceptMsg;
	}

//	this->grassSheet = make_shared<sf::Texture>();
//	string grassPath = "assets\\textures\\grass2.png";
//	if (!this->grassSheet->loadFromFile(grassPath)) {
//        string exceptMsg = "couldn't load texture:" + grassPath;
//        std::cout<<exceptMsg<<std::endl;
//        throw exceptMsg;
//    }
//
//	this->waterSheet = make_shared<sf::Texture>();
//	string waterPath = "assets\\textures\\grass2.png";
//	if (!this->grassSheet->loadFromFile(waterPath)) {
//        string exceptMsg = "couldn't load texture:" + waterPath;
//        std::cout<<exceptMsg<<std::endl;
//        throw exceptMsg;
//	}

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

shared_ptr<sf::Texture const> ee::Textures::getPlankSheet() const
{
	return plankSheet;
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


