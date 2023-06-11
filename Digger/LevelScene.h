#pragma once
#include <vector>

#include "Scene.h"

namespace dae
{
	class CollisionManagerComponent;
	class LevelScene final : public Scene
	{
	public:
		LevelScene(const std::string& name);

		void Initialize() override;

		void AddRock(int x, int y);
		void AddEmeralds(int x, int y);

		GameObject* GetPlayer();
		GameObject* GetGround();
		GameObject* GetSpawner();

	private:
		void InitializePlayer();
		void InitializeGround();
		void InitializeSpawner();

		GameObject* m_pPlayer{};
		GameObject* m_pGround{};
		GameObject* m_pSpawner{};
		std::vector<GameObject*> m_pRocks{};
		std::vector<GameObject*> m_pEmeralds{};
		CollisionManagerComponent* m_pCollisionManager{};
	};
}

