#include "Directions.h"


bool dae::SameOrientation(Direction a, Direction b)
{
	if((a == Left or a == Right) and (b == Left or b == Right))
		return true;
	return (a == Up or a == Down) and (b == Up or b == Down);
}


const glm::vec3 dae::Dir2Vector(Direction dir)
{
	switch (dir)
	{
	case Up: return UP;
	case Down: return DOWN;
	case Left: return LEFT;
	case Right: return RIGHT;
	}
	return glm::vec3{};
}