#pragma once
#include "Component.h"

namespace dae
{
	class HealthComponent final : public Component
	{
	public:

		HealthComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		float GetHealth() const;
		float GetMaxHealth() const;
		void SetHealth(float health);

	private:
		float m_MaxHealth{100};
		float m_Health{m_MaxHealth};
	};
}


