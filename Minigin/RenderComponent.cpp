#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;

RenderComponent::RenderComponent(GameObject* pGameObject)
	: Component(pGameObject), m_pTransformComponent(pGameObject->GetComponent<TransformComponent>())
{
	assert(pGameObject->ContainsComponent<TransformComponent>());
}

void RenderComponent::Update(float)
{}

void RenderComponent::FixedUpdate(float)
{}

void RenderComponent::Render() const
{
	const auto& pos = m_pTransformComponent->GetWorldPosition();
	if (m_texture) {
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(const std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}