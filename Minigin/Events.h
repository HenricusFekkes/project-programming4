#pragma once

namespace dae
{
	class GameObject;
	
	struct HealthChangedEvent final
	{
		GameObject* pCaller;
		float health;
	};

	struct LivesChangedEvent final
	{
		GameObject* pCaller;
		int lives;
	};

	struct ScoreChangedEvent final
	{
		GameObject* pCaller;
		float score;
	};
}

