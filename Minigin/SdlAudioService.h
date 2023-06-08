#pragma once
#include <map>
#include <string>

#include "IAudioService.h"

struct Mix_Chunk;
namespace dae {
	class SdlAudioService final : public IAudioService
	{
	public:
		SdlAudioService();
		~SdlAudioService() override;
		void Play(sound_id id, int volume) override;
		sound_id Load(const std::string& filename) override;

	private:
		std::map<sound_id, Mix_Chunk*> m_Audioclips{};
		int m_NextId{};
	};
}

