#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;

RenderComponent::RenderComponent(GameObject& pGameObject)
	: IComponent(pGameObject)
{
	GetGameObject().AddComponent<TransformComponent>();
}

void RenderComponent::Update(float)
{}

void RenderComponent::FixedUpdate(float)
{}

void RenderComponent::Render()
{
	if (m_Texture) {
		const auto& pos = GetGameObject().GetComponent<TransformComponent>()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(const std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}