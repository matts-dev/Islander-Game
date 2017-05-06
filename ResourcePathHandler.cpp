#include "ResourcePathHandler.h"



ee::ResourcePathHandler::ResourcePathHandler()
{
}


ee::ResourcePathHandler::~ResourcePathHandler()
{
}

//platform dependent implementations
std::string ee::ResourcePathHandler::getActorLocation()
{
	std::string standardPath = "assets//textures//genericActorSprite.png";
#if defined(_WIN32)
	return standardPath;
#elif defined(__APPLE__)
	return resourcePath() + "//" + standardPath;
#endif
}
