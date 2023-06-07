#include "ServiceLocator.h"
#include "SoundService.h"

using namespace dae;

void ServiceLocator::Initialize()
{
	m_pCurrentSoundService = &m_DefaultSoundService;
}

void ServiceLocator::Shutdown()
{
	if (m_pCurrentSoundService != &m_DefaultSoundService)
	{
		delete m_pCurrentSoundService;
		m_pCurrentSoundService = &m_DefaultSoundService;
	}
};

SoundService& ServiceLocator::GetSoundService()
{
	return *m_pCurrentSoundService;
}

void ServiceLocator::RegisterSoundService(SoundService* ss)
{
	m_pCurrentSoundService = (ss) ? ss : &m_DefaultSoundService;
}