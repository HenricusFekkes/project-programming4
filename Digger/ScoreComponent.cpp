#include "ScoreComponent.h"

#include "EventManager.h"
#include "Events.h"
#include "GameObject.h"

using namespace dae;

ScoreComponent::ScoreComponent(GameObject* pGameObject) : Component(pGameObject)
{}

void ScoreComponent::Update(float)
{}

void ScoreComponent::FixedUpdate(float)
{}

void ScoreComponent::SetScore(float score)
{
	if(score < 0)
	{
		score = 0;
	} else
	{
		m_Score = score;
	}
	
	EventManager<ScoreChangedEvent>::GetInstance().Dispatch(ScoreChangedEvent{ m_pGameObject, m_Score });
}

float ScoreComponent::GetScore()
{
	return m_Score;
}