#pragma once
#include "Component.h"

namespace dae
{
	class LivesComponent final : public Component
	{
	public:

		LivesComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;


		int GetLives() const;
		void SetLives(int lives);

	private:
		int m_Lives{ 3 };
	};
}


