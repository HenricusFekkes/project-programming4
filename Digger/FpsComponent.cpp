#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

FpsComponent::FpsComponent(GameObject* pGameObject) 
	: Component(pGameObject), m_pTextComponent(pGameObject->GetComponent<TextComponent>())
{
	assert(pGameObject->ContainsComponent<TextComponent>());
}

void FpsComponent::Update(float deltaTime)
{
	++frameCounter;
	passedTime += deltaTime;
	if (passedTime >= 1.f) {
		m_pTextComponent->SetText(std::to_string(static_cast<int>(frameCounter/passedTime)));
		frameCounter = 0;
		passedTime = 0;
	}
}

void FpsComponent::FixedUpdate(float)
{} 

