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

		void SetRadius(int radius);
		void SetLevel(GameObject* pLevel);

	private:
		int m_Radius{};
		GameObject* m_pLevel{};
	};
}

