#include "ISubject.h"
#include "IObserver.h"

using namespace dae;

ISubject::~ISubject()
{
	for (IObserver* pObserver : m_pObservers)
	{
		std::erase(pObserver->m_pSubjects, this);
	}
}

void ISubject::AttachObserver(IObserver* pObserver)
{
	pObserver->m_pSubjects.emplace_back(this);
	m_pObservers.emplace_back(pObserver);

	pObserver->OnAttach(this);
	OnAttach(pObserver);
}

void ISubject::DetachObserver(IObserver* pObserver)
{
	std::erase(pObserver->m_pSubjects, this);
	std::erase(m_pObservers, pObserver);

	pObserver->OnDetach(this);
	OnDetach(pObserver);
}

void ISubject::NotifyObservers(GameObject* pGameObject, int eventID)
{
	for (IObserver* pObserver : m_pObservers)
	{
		pObserver->Notify(pGameObject, eventID);
	}
}