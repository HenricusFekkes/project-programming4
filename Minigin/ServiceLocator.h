#pragma once
#include "NullAudioService.h"
#include "IAudioService.h"

namespace dae {
	class ServiceLocator final
	{
	public:
		static void Initialize();
		static void Shutdown();

		static IAudioService& GetSoundService();
		static void RegisterSoundService(IAudioService* ss);
		
	private:
		inline static NullAudioService m_DefaultAudioService{};
		inline static IAudioService* m_pCurrentAudioService{};

		// TODO: Other instances ...
	};
}
