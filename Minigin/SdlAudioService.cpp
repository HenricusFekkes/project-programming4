#include "SdlAudioService.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace dae;


SdlAudioService::SdlAudioService()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL2 mixer initialization failed: " << Mix_GetError() << std::endl;
		throw std::runtime_error("SDL2 mixer initialization failed");
	}
}

SdlAudioService::~SdlAudioService()
{
	for (auto& pair : m_Audioclips) {
		Mix_FreeChunk(pair.second);
	}
	Mix_CloseAudio();
}

void SdlAudioService::Play(sound_id id, int volume)
{
	Mix_VolumeChunk(m_Audioclips[id], volume);
	Mix_PlayChannel(-1, m_Audioclips[id], 0);
}


sound_id SdlAudioService::Load(const std::string& filename)
{
	sound_id id = m_NextId;
	m_Audioclips[id] = Mix_LoadWAV(filename.c_str());
	if (m_Audioclips[id] == NULL)
	{
		// TODO
		std::cout << "Unable to load SDL::SOUNDSERVICE::LOAD";
	}
	++m_NextId;
	return id;
}