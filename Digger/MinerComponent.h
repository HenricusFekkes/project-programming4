#pragma once
#include "IComponent.h"

namespace dae {

	class MinerComponent final : public IComponent {
	public:
		MinerComponent(GameObject& gameObject);
		~MinerComponent() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetRadius(float radius);
		void SetLevel(GameObject* pLevel);

	private:
		float m_Radius{};
		GameObject* m_pLevel{};
	};
}

