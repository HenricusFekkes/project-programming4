#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "sound.h"

using namespace dae;

void ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

std::shared_ptr<Sound> ResourceManager::LoadSound(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto chunk = Mix_LoadWAV(fullPath.c_str());
	if (chunk == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load sound: ") + SDL_GetError());
	}
	return std::make_shared<Sound>(chunk);
}
