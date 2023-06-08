#pragma once
#include "IAudioService.h"


namespace dae {
	class NullAudioService final : public IAudioService
	{
		void Play(sound_id, int) override;
		sound_id Load(const std::string& ) override;
	};
}