#include "ServiceLocator.h"
#include "IAudioService.h"

using namespace dae;

void ServiceLocator::Initialize()
{
	m_pCurrentAudioService = &m_DefaultAudioService;
}

void ServiceLocator::Shutdown()
{
	if (m_pCurrentAudioService != &m_DefaultAudioService)
	{
		delete m_pCurrentAudioService;
		m_pCurrentAudioService = &m_DefaultAudioService;
	}
};

IAudioService& ServiceLocator::GetSoundService()
{
	return *m_pCurrentAudioService;
}

void ServiceLocator::RegisterSoundService(IAudioService* ss)
{
	m_pCurrentAudioService = (ss) ? ss : &m_DefaultAudioService;
}