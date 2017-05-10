#pragma once
#include<memory>


//forward declarations
namespace sf {
	class Texture;
};

using std::shared_ptr;
using std::weak_ptr;
namespace ee {
	class Textures final
	{
		Textures();

		//----------- TEXTURES -----------
		shared_ptr<sf::Texture> actorSheet;
		shared_ptr<sf::Texture> plankSheet;
		shared_ptr<sf::Texture> grassSheet;
		shared_ptr<sf::Texture> waterSheet;

	public:
		~Textures();

		// ----------- TEXTURE ACCESS -----------
		shared_ptr<sf::Texture const> getActorSheet() const;
		shared_ptr<sf::Texture const> getPlankSheet() const;

		// ----------- SINGLETON -----------
		static shared_ptr<Textures const> singleton;
		static shared_ptr<Textures const> getInstance();
	};
}

