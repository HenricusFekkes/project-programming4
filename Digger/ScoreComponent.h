#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace dae
{
	class ScoreComponent final : public IComponent, public IObserver
	{
	public:
		ScoreComponent(GameObject& gameObject);
		void Notify(GameObject* pGameObject, int eventID) override;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		void SetValue(int value);
		int GetValue() const;

	private:
		int m_Value{};
	};
}


