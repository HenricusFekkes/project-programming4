#include "MoveComponent.h"

using namespace dae;

MoveComponent::MoveComponent(GameObject& gameObject)
	: IComponent(gameObject)
{}

void MoveComponent::Update(float)
{}

void MoveComponent::FixedUpdate(float)
{}

void MoveComponent::Render()
{}

void MoveComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void MoveComponent::SetDirection(Direction direction)
{
	m_Direction = direction;
}

float MoveComponent::GetSpeed() const
{
	return m_Speed;
}
Direction MoveComponent::GetDirection() const
{
	return m_Direction;
}