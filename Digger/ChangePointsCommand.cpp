#include "ChangePointsCommand.h"
#include "Timer.h"
#include "GameObject.h"
#include "ScoreComponent.h"

using namespace dae;

ChangePointsCommand::ChangePointsCommand(GameObject* pGameObject, float scorePerSecond)
	: pScoreComponent{pGameObject->GetComponent<ScoreComponent>()}, m_ScorePerSecond{scorePerSecond}
{}

bool ChangePointsCommand::Execute()
{
	pScoreComponent->SetScore(pScoreComponent->GetScore() + m_ScorePerSecond*Timer::GetInstance().GetDeltaTime());
	return true;
}