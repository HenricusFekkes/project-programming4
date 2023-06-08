#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

FpsComponent::FpsComponent(GameObject& gameObject)
	: IComponent(gameObject)
{
	GetGameObject().AddComponent<TextComponent>();
}

void FpsComponent::Update(float deltaTime)
{
	++m_FrameCounter;
	m_PassedTime += deltaTime;
	if (m_PassedTime >= 1.f) {
		GetGameObject().GetComponent<TextComponent>()->SetText(std::to_string(static_cast<int>(m_FrameCounter/m_PassedTime)));
		m_FrameCounter = 0;
		m_PassedTime = 0;
	}
}

void FpsComponent::Render()
{}

void FpsComponent::FixedUpdate(float)
{} 

