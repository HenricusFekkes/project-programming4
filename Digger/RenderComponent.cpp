#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;

RenderComponent::RenderComponent(GameObject& pGameObject)
	: IComponent(pGameObject)
{}

void RenderComponent::Update(float)
{}

void RenderComponent::FixedUpdate(float)
{}

void RenderComponent::Render()
{
	if (m_Texture) {
		const auto& pos = GetGameObject().GetComponent<TransformComponent>()->GetWorldPosition();
		if(m_EnableScale)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x+m_OffsetX, pos.y+m_OffsetY, m_Width, m_Height);
		} else
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_OffsetX, pos.y + m_OffsetY);
		}
	}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	auto dimensions = m_Texture->GetSize();
	m_Width = static_cast<float>(dimensions.x);
	m_Height = static_cast<float>(dimensions.y);
}


void RenderComponent::EnableScale(bool enable)
{
	m_EnableScale = enable;
}

void RenderComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
	m_EnableScale = true;
}

void RenderComponent::SetOffset(float x, float y)
{
	m_OffsetX = x;
	m_OffsetY = y;
}

void RenderComponent::SetTexture(const std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}