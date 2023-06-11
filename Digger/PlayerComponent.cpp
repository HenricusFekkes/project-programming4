#include "PlayerComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "Events.h"
#include "ScoreComponent.h"

using namespace dae;


PlayerComponent::PlayerComponent(GameObject& gameObject)
	: IComponent{gameObject}
{
	gameObject.AddComponent<CollisionComponent>()->AttachObserver(this);
}

void PlayerComponent::Update(float deltaTime)
{}

void PlayerComponent::FixedUpdate(float fixedStep)
{}

void PlayerComponent::Render()
{}

void PlayerComponent::Notify(GameObject* pGameObject, int eventID)
{
	if (eventID != Event::Collision)
	{
		return;
	}

	auto pScoreComponent = pGameObject->GetComponent<ScoreComponent>();
	if (pScoreComponent)
	{
		m_Score += pScoreComponent->GetValue();
		std::cout << "I hit emerald";
	}
}