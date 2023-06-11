#include "CollisionComponent.h"

#include "Events.h"

using namespace dae;

CollisionComponent::CollisionComponent(GameObject& gameObject) : IComponent(gameObject)
{}

void CollisionComponent::Update(float)
{}

void CollisionComponent::FixedUpdate(float)
{}

void CollisionComponent::Render()
{}


void CollisionComponent::CollidedWith(GameObject* gameObject)
{
	NotifyObservers(gameObject, Event::Collision);
}

void CollisionComponent::SetRadius(float radius)
{
	m_Radius = radius;
}

float CollisionComponent::GetRadius() const
{
	return m_Radius;
}