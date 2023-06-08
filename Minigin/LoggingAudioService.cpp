#include "LoggingAudioService.h"
#include <iostream>

using namespace dae;

LoggingAudioService::LoggingAudioService(IAudioService* ss) : m_pUnderlyingSS(ss)
{}

LoggingAudioService::~LoggingAudioService()
{
	delete m_pUnderlyingSS;
}

void LoggingAudioService::Play(sound_id id, int volume)
{
	std::cout << "Playing " << id << " at volume " << volume << std::endl;
	m_pUnderlyingSS->Play(id, volume);
}


sound_id LoggingAudioService::Load(const std::string& filename)
{
	std::cout << "Loaded " << filename << std::endl;
	return m_pUnderlyingSS->Load(filename);
}