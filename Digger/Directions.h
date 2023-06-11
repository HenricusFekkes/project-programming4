#pragma once
#include <glm/vec3.hpp>

namespace dae
{
	enum Direction
	{
		Up,
		Down,
		Right,
		Left
	};

	bool SameOrientation(Direction a, Direction b);

	const glm::vec3 UP   { 0,-1,0 };
	const glm::vec3 DOWN {0, 1,0 };
	const glm::vec3 LEFT {-1,0,0 };
	const glm::vec3 RIGHT{1,0,0 };

	const glm::vec3 Dir2Vector(Direction);
}
