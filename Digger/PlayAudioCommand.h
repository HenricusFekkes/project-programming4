#pragma once
#include <string>
#include "ICommand.h"
#include "ServiceLocator.h"

namespace dae
{
	class PlayAudioCommand final : public dae::ICommand
	{
	public:
		PlayAudioCommand(const std::string& filename, int volume);
		bool Execute() override;

	private:
		sound_id m_AudioId;
		int m_Volume;
	};
}


