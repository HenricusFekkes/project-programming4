#pragma once
#include <string>
#include "ICommand.h"
#include "ServiceLocator.h"

namespace dae
{
	class PlayAudioCommand final : public dae::ICommand
	{
	public:
		PlayAudioCommand(std::shared_ptr<Sound>& sound, int volume);
		bool Execute() override;

	private:
		std::shared_ptr<Sound> m_Sound;
		int m_Volume;
	};
}


