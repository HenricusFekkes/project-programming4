#pragma once
#include <SDL_mixer.h>


namespace dae
{
	class Sound
	{
	public:
		Sound(Mix_Chunk* pSoundChunk);
		~Sound();

		Sound(const Sound&) = delete;
		Sound(Sound&&) = delete;
		Sound& operator= (const Sound&) = delete;
		Sound& operator= (const Sound&&) = delete;

		Mix_Chunk* GetSDLChunk() const;

	private:
		Mix_Chunk* m_pSoundChunk;
	};
}


