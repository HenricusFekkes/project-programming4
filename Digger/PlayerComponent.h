#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace dae
{
	class PlayerComponent final : public IComponent, public IObserver
	{
	public:
		PlayerComponent(GameObject& gameObject);
		void Notify(GameObject* pGameObject, int eventID) override;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

	private:
		int m_Score{};
	};
}


