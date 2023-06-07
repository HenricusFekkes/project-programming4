#pragma once

#include <glm/glm.hpp>
#include "Component.h"


namespace dae {
	class TransformComponent final : public Component {
	public:
		explicit TransformComponent(GameObject* pGameObject);
		~TransformComponent() = default;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const float x, const float y, const float z = 0);
		void SetLocalPosition(const glm::vec3& localPosition);
		void UpdateWorldPosition();

		void SetDirty();

	private:
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

		bool m_IsDirty{true};
	};
}