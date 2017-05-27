#pragma once
#include<memory>


//forward declarations
namespace sf {
	class Texture;
};

namespace ee {
	class Textures final
	{
		Textures();

		//----------- TEXTURES -----------
		std::shared_ptr<sf::Texture> actorSheet;
		std::shared_ptr<sf::Texture> plankSheet;
		std::shared_ptr<sf::Texture> grassSheet;
		std::shared_ptr<sf::Texture> waterSheet;

	public:
		~Textures();

		// ----------- TEXTURE ACCESS -----------
		std::shared_ptr<sf::Texture const> getActorSheet() const;
		std::shared_ptr<sf::Texture const> getPlankSheet() const;

		// ----------- SINGLETON -----------
		static std::shared_ptr<Textures const> singleton;
		static std::shared_ptr<Textures const> getInstance();
	};
}

