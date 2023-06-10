#pragma once
#include "IAudioService.h"


namespace dae {
	class NullAudioService final : public IAudioService
	{
	public:
		void Play(std::shared_ptr<Sound>&, int) override;
	};
}