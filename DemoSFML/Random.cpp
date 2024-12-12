#include "Random.hpp"

int RandomInt(int _min, int _max)
{
	return rand() % (_max - _min + 1) + _min;
}