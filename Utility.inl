//#include "Utility.h"

template<typename T>
inline bool ee::utility::valueInRange(const T value, const T min, const T max) {
	T trueMin = min < max ? min : max;
	T trueMax = max > min ? max : min;
	return value >= trueMin && value <= trueMax;
}