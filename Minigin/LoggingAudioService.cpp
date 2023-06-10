#include "LoggingAudioService.h"
#include <iostream>

using namespace dae;

LoggingAudioService::LoggingAudioService(IAudioService* ss) : m_pUnderlyingSoundService(ss)
{}

LoggingAudioService::~LoggingAudioService()
{
	delete m_pUnderlyingSoundService;
}

void LoggingAudioService::Play(std::shared_ptr<Sound>& sound, int volume)
{
	std::cout << "Playing sound at volume " << volume << std::endl;
	m_pUnderlyingSoundService->Play(sound, volume);
}
