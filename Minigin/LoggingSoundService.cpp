#include "LoggingSoundService.h"
#include <iostream>

using namespace dae;

LoggingSoundService::LoggingSoundService(SoundService* ss) : m_pUnderlyingSS(ss)
{}

LoggingSoundService::~LoggingSoundService()
{
	delete m_pUnderlyingSS;
}

void LoggingSoundService::Play(sound_id id, int volume)
{
	std::cout << "Playing " << id << " at volume " << volume << std::endl;
	m_pUnderlyingSS->Play(id, volume);
}


sound_id LoggingSoundService::Load(const std::string& filename)
{
	std::cout << "Loaded " << filename << std::endl;
	return m_pUnderlyingSS->Load(filename);
}