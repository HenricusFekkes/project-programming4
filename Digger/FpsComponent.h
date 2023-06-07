#pragma once

#include "Component.h"

namespace dae {
	class TextComponent;
	class FpsComponent final : public Component {
	public:
		explicit FpsComponent(GameObject* pGameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;

	private:
		float passedTime{};
		int frameCounter{};
		TextComponent* m_pTextComponent{};
	};
}
