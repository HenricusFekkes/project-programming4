#include "MoveCommand.h"

#include "GameObject.h"

using namespace dae;

MoveCommand::MoveCommand(glm::vec3 direction, float speed, GameObject& gameObject)
	: m_Direction{direction}, m_Speed{speed}, m_GameObject(gameObject)
{}

bool MoveCommand::Execute()
{
	auto pTransformComponent = m_GameObject.GetComponent<TransformComponent>();
	auto position = pTransformComponent->GetLocalPosition();
	pTransformComponent->SetLocalPosition(position + m_Direction * m_Speed);
	return true;
}