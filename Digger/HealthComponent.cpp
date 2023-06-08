#include "HealthComponent.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Events.h"
#include "LivesComponent.h"

using namespace dae;

HealthComponent::HealthComponent(GameObject& gameObject)
	: Component(gameObject)
{
	GetGameObject().AddComponent<LivesComponent>();
}

void HealthComponent::Update(float)
{}

void HealthComponent::FixedUpdate(float)
{}

void HealthComponent::Render()
{}

float HealthComponent::GetHealth() const
{
	return m_Health;
}

float HealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

void HealthComponent::SetHealth(float health)
{
	if(GetGameObject().GetComponent<LivesComponent>()->GetLives() == 0)
	{
		return;
	}

	if (health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
	else if(health < 0)
	{
		m_Health = 0;
	}
	else
	{
		m_Health = health;
	}
	EventManager<HealthChangedEvent>::GetInstance().Dispatch(HealthChangedEvent{ &GetGameObject(), m_Health });
}