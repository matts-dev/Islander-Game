#pragma once

#if defined(_WIN32)

#elif defined(__APPLE__)
#include<ResourcePath.hpp>
#endif

#include<string>
namespace ee {
	class ResourcePathHandler {
		//utility class that cannot be instantiated
		ResourcePathHandler();
		~ResourcePathHandler();
	public:
		//return correct paths regardless of platform
		static std::string getActorLocation();
        static std::string getGrassLocation();
	};
}
