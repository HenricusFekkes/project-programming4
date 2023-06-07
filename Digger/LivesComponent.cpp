#include "LivesComponent.h"

#include "EventManager.h"
#include "Events.h"

using namespace dae;

LivesComponent::LivesComponent(GameObject* pGameObject) : Component(pGameObject)
{}

void LivesComponent::Update(float)
{}

void LivesComponent::FixedUpdate(float)
{}


int LivesComponent::GetLives() const
{
	return m_Lives;
}

void LivesComponent::SetLives(int lives)
{
	if(lives < 0)
	{
		lives = 0;
	}
	else
	{
		m_Lives = lives;
	}
	EventManager<LivesChangedEvent>::GetInstance().Dispatch(LivesChangedEvent{ m_pGameObject, m_Lives });
}