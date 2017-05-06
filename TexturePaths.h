//CURRENTLY UNTESTED ON APPLE
#if defined(_WIN32)

#elif defined(__APPLE__)
#include<resoures.mm> //update spelling when testing on apple for resource management
#endif

#include<string>
namespace ee {
	class ResourcePathLookup {
#if defined(_WIN32)
		std::string getActorPath() {
			return "assets//genericActorSprite.png";
		}
#elif defined(__APPLE__)
		std::string getActorPath() {
			return "assets//genericActorSprite.png";
		}
#endif
	};
}