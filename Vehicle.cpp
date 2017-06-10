#include "Vehicle.h"

namespace ee {


Vehicle::Vehicle(float movementSpeed) : Actor(movementSpeed)
{
}


Vehicle::~Vehicle()
{
}

bool Vehicle::attemptActorLoad(std::shared_ptr<Actor> boardingActor)
{
	//TODO IMPLEMENT
	return false;
}

bool Vehicle::attemptActorRemove(std::shared_ptr<Actor> leavingActor)
{
	//TODO IMPLEMENT
	return false;
}


}
