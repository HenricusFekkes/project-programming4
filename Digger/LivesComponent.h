#pragma once
#include "Component.h"

namespace dae
{
	class LivesComponent final : public Component
	{
	public:

		LivesComponent(GameObject* pGameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;


		int GetLives() const;
		void SetLives(int lives);

	private:
		int m_Lives{ 3 };
	};
}


