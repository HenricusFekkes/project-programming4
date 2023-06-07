#include "MoveCommand.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "Timer.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* target, glm::vec3 velocity)
	: m_pTransform{target->GetComponent<TransformComponent>()}, m_Velocity{velocity}
{}


bool MoveCommand::Execute()
{
	m_pTransform->SetLocalPosition(m_pTransform->GetLocalPosition() + m_Velocity*Timer::GetInstance().GetDeltaTime());
	return true;
}