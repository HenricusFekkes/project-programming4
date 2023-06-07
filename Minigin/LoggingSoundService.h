#pragma once
#include "SoundService.h"


namespace dae {
	class LoggingSoundService final : public SoundService
	{
	public:
		LoggingSoundService(SoundService* ss);
		~LoggingSoundService() override;

		void Play(sound_id id, int volume) override;
		sound_id Load(const std::string& filename) override;

	private:
		SoundService* m_pUnderlyingSS;
	};
}
