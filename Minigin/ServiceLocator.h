#pragma once
#include "NullAudioService.h"
#include "IAudioService.h"
#include "Singleton.h"

namespace dae {
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		void Initialize();
		void Shutdown();

		~ServiceLocator();

		IAudioService& GetSoundService();
		void RegisterAudioService(IAudioService* pAudioService);
		
	private:
		NullAudioService m_DefaultAudioService{};
		IAudioService* m_pCurrentAudioService{};

		// TODO: Other instances ...
	};
}
