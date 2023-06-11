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

void MinerComponent::Update(float deltaTime)
{
	
}

void MinerComponent::FixedUpdate(float fixedStep)
{
	auto pGridComponent = m_pLevel->GetComponent<GroundComponent>();
	auto position = GetGameObject().GetComponent<TransformComponent>()->GetLocalPosition();
	pGridComponent->RemoveCircle(position.x, position.y, m_Radius);
}

void MinerComponent::Render()
{}

void MinerComponent::SetRadius(int radius)
{
	m_Radius = radius;
}

void MinerComponent::SetLevel(GameObject* pLevel)
{
	m_pLevel = pLevel;
}