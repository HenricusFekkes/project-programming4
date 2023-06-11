#include "ServiceLocator.h"
#include "IAudioService.h"

using namespace dae;

void ServiceLocator::Initialize()
{
	m_pCurrentAudioService = &m_DefaultAudioService;
}


ServiceLocator::~ServiceLocator()
{
	Shutdown();
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

void ServiceLocator::RegisterAudioService(IAudioService* pAudioService)
{
	if(pAudioService)
	{
		if(m_pCurrentAudioService != &m_DefaultAudioService)
		{
			delete m_pCurrentAudioService;
		}
		m_pCurrentAudioService = pAudioService;
	} else
	{
		m_pCurrentAudioService = &m_DefaultAudioService;
	}
}