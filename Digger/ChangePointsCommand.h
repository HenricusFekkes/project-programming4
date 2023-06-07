#pragma once
#include "Command.h"

namespace dae
{
	class ScoreComponent;
	class ChangePointsCommand final : public Command
	{
	public:
		ChangePointsCommand(GameObject* pGameObject, float scorePerSecond);
		bool Execute() override;

	private:
		ScoreComponent* pScoreComponent{};
		float m_ScorePerSecond{};
	};
}


