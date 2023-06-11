#pragma once
#include "Directions.h"
#include "IComponent.h"

namespace dae
{
	class MoveComponent final : public IComponent
	{
	public:
		MoveComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetSpeed(float speed);
		void SetDirection(Direction direction);

		float GetSpeed() const;
		Direction GetDirection() const;

	private:
		float m_Speed{};
		Direction m_Direction{Right};
	};
}


