#include "ChangeHealthCommand.h"
#include "Timer.h"
#include "GameObject.h"
#include "HealthComponent.h"

using namespace dae;

ChangeHealthCommand::ChangeHealthCommand(GameObject* pGameObject, float healthPerSecond)
	: pHealthComponent{ pGameObject->GetComponent<HealthComponent>() }, m_HealthPerSecond{ healthPerSecond }
{}

bool ChangeHealthCommand::Execute()
{
	pHealthComponent->SetHealth(pHealthComponent->GetHealth() + m_HealthPerSecond * Timer::GetInstance().GetDeltaTime());
	return true;
}