#include "ScoreComponent.h"

#include "CollisionComponent.h"
#include "Events.h"
#include "GameObject.h"
#include "PlayerComponent.h"

using namespace dae;

ScoreComponent::ScoreComponent(GameObject& gameObject)
	: IComponent(gameObject)
{
	gameObject.AddComponent<CollisionComponent>()->AttachObserver(this);
}

void ScoreComponent::Update(float deltaTime)
{}

void ScoreComponent::FixedUpdate(float fixedStep)
{}

void ScoreComponent::Render()
{}

void ScoreComponent::SetValue(int value)
{
	m_Value = value;
}

int ScoreComponent::GetValue() const
{
	return m_Value;
}


void ScoreComponent::Notify(GameObject* pGameObject, int eventID)
{
	if(eventID != Event::Collision)
	{
		return;
	}

	auto pPlayerComponent = pGameObject->GetComponent<PlayerComponent>();
	if(pPlayerComponent)
	{
		GetGameObject().Destroy();
	}
}