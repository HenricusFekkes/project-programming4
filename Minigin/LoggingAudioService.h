#pragma once
#include "IAudioService.h"


namespace dae {
	class LoggingAudioService final : public IAudioService
	{
	public:
		LoggingAudioService(IAudioService* ss);
		~LoggingAudioService() override;

		void Play(sound_id id, int volume) override;
		sound_id Load(const std::string& filename) override;

	private:
		IAudioService* m_pUnderlyingSS;
	};
}
