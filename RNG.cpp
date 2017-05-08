#include "RNG.h"
#include<ctime>
#include<cstdlib>

using std::shared_ptr;

ee::RNG::RNG()
{
	//set up the random number generator 
	srand(static_cast<unsigned int>(time(nullptr)));
}


ee::RNG::~RNG()
{
}

/** thread safe retreival of random number*/
int ee::RNG::nextRandomInt()
{
	//will be unlocked when scope is left (dtor in lock_guard releases mutex)
	std::lock_guard<std::mutex> lockGaurd(randMutex);
	return rand();
}


shared_ptr<ee::RNG> ee::RNG::singleton = nullptr;
shared_ptr<ee::RNG> ee::RNG::getInstance()
{
	//nullptr check
	if (!singleton) {
		singleton = shared_ptr<RNG>(new RNG());
	}
	return singleton;
}

