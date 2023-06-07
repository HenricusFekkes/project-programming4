#pragma once
#include "Command.h"

namespace dae
{
	class HealthComponent;
	class ChangeHealthCommand final : public Command
	{
	public:
		ChangeHealthCommand(GameObject* pGameObject, float healthPerSecond);
		bool Execute() override;

	private:
		HealthComponent* pHealthComponent{};
		float m_HealthPerSecond{};
	};
}

