#include "GroundComponent.h"

#include <iostream>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"

using namespace dae;

GroundComponent::GroundComponent(GameObject& pGameObject)
	: IComponent(pGameObject)
{}

GroundComponent::~GroundComponent()
{
	delete[] m_Pixels;
}

void GroundComponent::Update(float)
{}

void GroundComponent::FixedUpdate(float)
{}

void GroundComponent::Render()

{
	if(m_IsDirty)
	{
		SDL_UpdateTexture(m_Texture->GetSDLTexture(), NULL, m_Pixels, m_Width * sizeof(Uint32));
	}

	if (m_Texture) {
		const auto& pos = GetGameObject().GetComponent<TransformComponent>()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	m_IsDirty = false;
}


void GroundComponent::SetDimensions(int width, int height)
{
	// TODO hide SDL
	delete[] m_Pixels;

	m_Width = width;
	m_Height = height;
	m_Pixels = new Uint32[width * height];
	auto* texture = SDL_CreateTexture(Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, m_Width, m_Height);
	m_Texture.reset(new Texture2D{ texture });

	for(int i{}; i < m_Width*m_Height; ++i)
	{
		m_Pixels[i] = 255;
	}
	
	m_IsDirty = true;
}

void GroundComponent::RemovePixel(int x, int y)
{
	if (x < 0 or x >= m_Width)
		return;
	if (y < 0 or y >= m_Height)
		return;
	m_Pixels[x + y * m_Width] = 0;
	m_IsDirty = true;
}

void GroundComponent::RemoveRectangle(int x, int y, int width, int height)
{
	for(int i{x}; i < x+width; ++i)
	{
		for(int j{ y }; j < y + height; ++j)
		{
			RemovePixel(i, j);
		}
	}
}

void GroundComponent::RemoveCircle(int x, int y, int radius)
{
	int radiusSqr = radius * radius;

	for (int xi{ -radius }; xi < radius; ++xi)
	{
		for(int yi{-radius}; yi < radius; ++yi)
		{
			if(xi*xi+yi*yi < radiusSqr)
			{
				RemovePixel(x+xi, y+yi);
			}
		}
	}
}