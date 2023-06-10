#include "Sound.h"

using namespace dae;


Sound::Sound(Mix_Chunk* pSoundChunk) : m_pSoundChunk{pSoundChunk}
{}

Sound::~Sound()
{
	Mix_FreeChunk(m_pSoundChunk);
}

Mix_Chunk* Sound::GetSDLChunk() const
{
	return m_pSoundChunk;
}

