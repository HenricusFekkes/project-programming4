#pragma once
#include "IAudioService.h"

struct Mix_Chunk;
namespace dae {
	class AudioService final : public IAudioService
	{
	public:
		AudioService();
		~AudioService() override;
		void Play(std::shared_ptr<Sound>& sound, int volume) override;

	private:
		class AudioServiceImpl;
		AudioServiceImpl* pImpl{};
	};
}

