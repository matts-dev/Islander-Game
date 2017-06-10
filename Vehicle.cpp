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
		//subclass sets criteria for boarding
		if (actorValidForBoard(boardingActor)) {
			auto iter = occupants.find(boardingActor.get());
			if (iter != occupants.end() && iter->second.lock()) {
				//actor already exists for address and is still valid
				return false;
			}
			else {
				occupants[boardingActor.get()] = boardingActor;
			}
		}
		return false;
	}

	bool Vehicle::attemptActorRemove(std::shared_ptr<Actor> leavingActor)
	{
		//prevent compiler warnings associated with casts
		return 0 != occupants.erase(leavingActor.get());
	}
}
