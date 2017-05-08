#pragma once

#if defined(_WIN32)

#elif defined(__APPLE__)
#include<ResourcePath.hpp>
#endif

#include<string>
namespace ee {
	/*
		A class that handles the creation of paths for textures in a platform-indepedent manner.
		The version of SFML on apple requires a special structure for application bundling. The
		path to resources is determined by a function call that doesn't exist on other platforms.
		This class handles compiling source code differently for those platforms.
	*/
	class ResourcePathHandler {
		//utility class that cannot be instantiated
		ResourcePathHandler();
		~ResourcePathHandler();
	public:
		//return correct paths regardless of platform
		static std::string getActorLocation();
		static std::string getPlankSheetLocation();
		static std::string platformDependentModification(std::string& transform);
	};
}
