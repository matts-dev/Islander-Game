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
	return platformDependentModification(standardPath);
}

std::string ee::ResourcePathHandler::getPlankSheetLocation()
{
	std::string plankPath = "assets//textures//plankSheet32.png";
	return platformDependentModification(plankPath);
}

std::string ee::ResourcePathHandler::platformDependentModification(std::string& transform)
{
#if defined(_WIN32)
	return transform;
#elif defined(__APPLE__)
	return resourcePath() + "//" + transform;
#endif
}
