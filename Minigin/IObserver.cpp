#include "IObserver.h"
#include "ISubject.h"

using namespace dae;

IObserver::~IObserver()
{
	for (ISubject* pSubject : m_pSubjects)
	{
		pSubject->DetachObserver(this);
	}
}


const std::vector<ISubject*>& IObserver::GetSubjects()
{
	return m_pSubjects;
}