#pragma once
#include "IComponent.h"
#include "ISubject.h"

namespace dae
{
	class CollisionComponent final : public IComponent, public ISubject
	{
	public:
		CollisionComponent(GameObject& gameObject);

		void Update(float) override;
		void FixedUpdate(float) override;
		void Render() override;

		void CollidedWith(GameObject* gameObject);
		void SetRadius(float radius);
		float GetRadius() const;

	private:
		float m_Radius{};
	};
}


