#pragma once
#include "NullSoundService.h"
#include "SoundService.h"

namespace dae {
	class ServiceLocator final
	{
	public:
		static void Initialize();
		static void Shutdown();

		static SoundService& GetSoundService();
		static void RegisterSoundService(SoundService* ss);
		
	private:
		inline static NullSoundService m_DefaultSoundService{};
		inline static SoundService* m_pCurrentSoundService{};

		// TODO: Other instances ...
	};
}
