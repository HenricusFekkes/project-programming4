#include "ScoreComponent.h"

#include "EventManager.h"
#include "Events.h"
#include "GameObject.h"

using namespace dae;

ScoreComponent::ScoreComponent(GameObject& gameObject) : Component(gameObject)
{}

void ScoreComponent::Update(float)
{}

void ScoreComponent::FixedUpdate(float)
{}

void  ScoreComponent::Render()
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
	
	EventManager<ScoreChangedEvent>::GetInstance().Dispatch(ScoreChangedEvent{ &GetGameObject(), m_Score });
}

float ScoreComponent::GetScore()
{
	return m_Score;
}