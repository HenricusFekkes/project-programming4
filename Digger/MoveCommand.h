#pragma once
#include <glm/vec3.hpp>

#include "ICommand.h"


namespace dae
{
	class MoveCommand final : public ICommand
	{
	public:
		MoveCommand(glm::vec3 direction, float speed, GameObject& gameObject);
		bool Execute() override;
	private:
		glm::vec3 m_Direction{};
		float m_Speed{};
		GameObject& m_GameObject;
	};

}

