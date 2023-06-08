#pragma once

#include "IComponent.h"
#include <memory>
#include <string>

namespace dae {
	class Font;
	class Texture2D;
	class TransformComponent;
	class RenderComponent final: public IComponent {
	public:
		RenderComponent(GameObject& pGameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetTexture(const std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& filename);


	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}