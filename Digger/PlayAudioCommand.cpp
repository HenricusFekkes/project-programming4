#include "PlayAudioCommand.h"

using namespace dae;

PlayAudioCommand::PlayAudioCommand(std::shared_ptr<Sound>& sound, int volume) : m_Sound{sound}, m_Volume{volume}
{}

bool PlayAudioCommand::Execute()
{
	ServiceLocator::GetInstance().GetSoundService().Play(m_Sound, m_Volume);
	return true;
}