#pragma once
#include "SoundService.h"


namespace dae {
	class NullSoundService final : public SoundService
	{
		void Play(sound_id, int) override;
		sound_id Load(const std::string& ) override;
	};
}