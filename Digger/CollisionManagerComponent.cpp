#include "CollisionManagerComponent.h"

#include <stdexcept>

#include "CollisionComponent.h"
#include "Events.h"
#include "GameObject.h"

using namespace dae;


CollisionManagerComponent::CollisionManagerComponent(GameObject& gameObject)
	: IComponent{gameObject}
{}

void CollisionManagerComponent::Update(float)
{
	auto colliders = GetSubjects();

	if (colliders.empty())
	{
		return;
	}

	for (auto it1{ colliders.begin() }; it1 != colliders.end() - 1; ++it1)
	{
		for (auto it2{ it1 + 1 }; it2 != colliders.end(); ++it2)
		{
			auto& pObject1 = static_cast<CollisionComponent&>(**it1);
			auto& pObject2 = static_cast<CollisionComponent&>(**it2);
			if (Collides(pObject1, pObject2))
			{
				pObject1.CollidedWith(&pObject2.GetGameObject());
				pObject2.CollidedWith(&pObject1.GetGameObject());
			}
		}
	}
}

void CollisionManagerComponent::FixedUpdate(float)
{}

void CollisionManagerComponent::Render()
{}


bool CollisionManagerComponent::Collides(CollisionComponent& pColliderA, CollisionComponent& pColliderB) const
{
	glm::vec3 posA = pColliderA.GetGameObject().GetComponent<TransformComponent>()->GetWorldPosition();
	auto& a = pColliderB.GetGameObject();
	auto b = a.GetComponent<TransformComponent>();
	glm::vec3 posB = b->GetWorldPosition();
	//glm::vec3 posB = pColliderB->GetGameObject().GetComponent<TransformComponent>()->GetWorldPosition();
	return glm::distance(posA, posB) <= pColliderA.GetRadius() + pColliderB.GetRadius();
}


void CollisionManagerComponent::OnAttach(ISubject* pObserver)
{
	// TODO
	if(!dynamic_cast<CollisionComponent*>(pObserver))
	{
		std::runtime_error("Tried attaching non-collider component to CollisionManagerComponent.");
	}
}