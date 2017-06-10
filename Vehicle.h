#pragma once
#include "Actor.h"
#include<memory>
#include<map>

namespace ee {

	class Vehicle : public Actor
	{
	private:
		//map container for quick lookup
		std::map<Actor*, std::weak_ptr<Actor>> occupants;

	public:
		Vehicle(float movementSpeed);
		virtual ~Vehicle();

		/**
		Attempt to load an actor onto the vehicle.
		@Returns true if the actor was successfully made a occupant of the vehicle
		*/
		virtual bool attemptActorLoad(std::shared_ptr<Actor> boardingActor);

		/**
		Attempt to remove an actor from the vehicle's occupant list.
		@Returns true if the actor was successfully made a occupant of the vehicle.
		@Returns false if the actor was not an occupant or could not be removed.
		*/
		virtual bool attemptActorRemove(std::shared_ptr<Actor> leavingActor);

		virtual bool actorValidForBoard(std::shared_ptr<Actor> boardRequestingActor) = 0;
	};
}//end namespace ee

