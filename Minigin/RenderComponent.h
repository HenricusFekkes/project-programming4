#pragma once

#include "Component.h"
#include <memory>
#include <string>

namespace dae {
	class Font;
	class Texture2D;
	class TransformComponent;
	class RenderComponent final: public Component {
	public:
		explicit RenderComponent(GameObject* pGameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() const;

		void SetTexture(const std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& filename);


	private:
		bool m_needsUpdate{};
		std::shared_ptr<Texture2D> m_texture{};

		TransformComponent* m_pTransformComponent{};
	};
}