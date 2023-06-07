#pragma once

#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class GameObject;
	class MoveCommand final: public Command
	{
	public:
		MoveCommand(GameObject* target, glm::vec3 velocity);
		bool Execute() override;

	private:
		TransformComponent* m_pTransform{};
		glm::vec3 m_Velocity{};
	};
}
