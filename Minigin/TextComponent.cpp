#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "GameObject.h"

using namespace dae;

TextComponent::TextComponent(GameObject* pGameObject)
	: Component(pGameObject), m_pRenderComponent(pGameObject->GetComponent<RenderComponent>())
{
	assert(pGameObject->ContainsComponent<RenderComponent>());
}

void TextComponent::Update(float)
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void TextComponent::FixedUpdate(float)
{}

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_font = font;
	m_needsUpdate = true;
}