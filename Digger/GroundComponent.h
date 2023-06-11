#pragma once
#include <memory>
#include <SDL_stdinc.h>
#include "IComponent.h"

namespace dae {
	class Font;
	class Texture2D;
	class TransformComponent;

	class GroundComponent final : public IComponent {
	public:
		GroundComponent(GameObject& gameObject);
		~GroundComponent() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetDimensions(int width, int height);
		void RemovePixel(int x, int y);
		void RemoveRectangle(int x, int y, int width, int height);
		void RemoveCircle(int x, int y, int radius);

	private:
		int m_Width{};
		int m_Height{};
		Uint32* m_Pixels{};
		std::unique_ptr<Texture2D> m_Texture{};
		bool m_IsDirty{};
	};
}