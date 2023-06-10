#pragma once
#include "IAudioService.h"


namespace dae {
	class LoggingAudioService final : public IAudioService
	{
	public:
		LoggingAudioService(IAudioService* ss);
		~LoggingAudioService() override;

		void Play(std::shared_ptr<Sound>& sound, int volume) override;

	private:
		IAudioService* m_pUnderlyingSoundService;
	};
}
