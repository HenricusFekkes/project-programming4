#pragma once
#include "Component.h"

namespace dae
{
	class ScoreComponent final : public Component
	{
	public:

		ScoreComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetScore(float score);
		float GetScore();

	private:
		float m_Score{0};
	};
}


