#pragma once
#include <vector>

#include "IComponent.h"
#include "IObserver.h"

namespace dae
{
	class CollisionComponent;
	class CollisionManagerComponent final : public IComponent, public IObserver
	{
	public:
		CollisionManagerComponent(GameObject& gameObject);

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedStep) override;
		void Render() override;

		virtual void Notify(GameObject*, int) override {}

	protected:
		void OnAttach(ISubject* pObserver) override;

	private:
		bool Collides(CollisionComponent& pColliderA, CollisionComponent& pColliderB) const;
	};
}


