#include "PlayAudioCommand.h"

using namespace dae;

PlayAudioCommand::PlayAudioCommand(const std::string& filename, int volume) : m_AudioId{ServiceLocator::GetSoundService().Load(filename)}, m_Volume{volume}
{}

bool PlayAudioCommand::Execute()
{
	ServiceLocator::GetSoundService().Play(m_AudioId, m_Volume);
	return true;
}