#pragma once

#include "Component.h"

namespace dae {
	class FpsComponent final : public Component {
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
