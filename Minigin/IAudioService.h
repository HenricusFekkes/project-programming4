#pragma once
#include <string>

#include "Singleton.h"

namespace dae {
	using sound_id = unsigned int;

	class IAudioService : public Singleton<IAudioService>
	{
	public:
		virtual void Play(sound_id id, int volume) = 0;
		virtual sound_id Load(const std::string& filename) = 0;
	};
}