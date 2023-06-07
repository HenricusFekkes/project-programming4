#pragma once
#include <string>
#include "Command.h"
#include "ServiceLocator.h"

namespace dae
{
	class PlayAudioCommand final : public dae::Command
	{
	public:
		PlayAudioCommand(const std::string& filename, int volume);
		bool Execute() override;

	private:
		sound_id m_AudioId;
		int m_Volume;
	};
}


