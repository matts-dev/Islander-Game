
template<typename T>
inline bool ee::utility::valueInRange(const T value, const T min, const T max) {
	//TODO add tolerated error delta
	T trueMin = min < max ? min : max;
	T trueMax = max > min ? max : min;

	//return value >= (trueMin - delta) && value <= (trueMax + delta)
	return value >= trueMin && value <= trueMax;
}