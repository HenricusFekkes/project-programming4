#pragma once

#include "IComponent.h"

namespace dae {
	class FpsComponent final : public IComponent {
	public:
		FpsComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

	private:
		float m_PassedTime{};
		int m_FrameCounter{};
	};
}
