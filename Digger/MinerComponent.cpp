#include "MinerComponent.h"

#include "GameObject.h"
#include "GroundComponent.h"

using namespace dae;

MinerComponent::MinerComponent(GameObject& gameObject)
	: IComponent {gameObject}
{}

MinerComponent::~MinerComponent()
{
	
}

void MinerComponent::Update(float)
{
	auto pGridComponent = m_pLevel->GetComponent<GroundComponent>();
	auto position = GetGameObject().GetComponent<TransformComponent>()->GetLocalPosition();
	pGridComponent->RemoveCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(m_Radius));
}

void MinerComponent::FixedUpdate(float)
{}

void MinerComponent::Render()
{}

void MinerComponent::SetRadius(float radius)
{
	m_Radius = radius;
}

void MinerComponent::SetLevel(GameObject* pLevel)
{
	m_pLevel = pLevel;
}