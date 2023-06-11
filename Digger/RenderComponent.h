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
		void SetSize(float width, float height);
		void SetOffset(float width, float height);
		void EnableScale(bool enable);


	private:
		std::shared_ptr<Texture2D> m_Texture{};
		bool m_EnableScale{false};
		float m_Width{};
		float m_Height{};
		float m_OffsetX{};
		float m_OffsetY{};
	};
}