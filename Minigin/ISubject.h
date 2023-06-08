#pragma once
#include <vector>

#include "IObserver.h"

namespace dae
{
	class IObserver;
	class GameObject;
	class ISubject
	{
	public:
		virtual ~ISubject()
		{
			for(IObserver* pObserver : m_pObservers)
			{
				pObserver->NotifySubjectDeleted(this);
			}
		}

		virtual void AttachObserver(IObserver* pObserver)
		{
			pObserver->m_pSubjects.push_back(this);
			m_pObservers.push_back(pObserver);
		}

		virtual void DetachObserver(IObserver* pObserver)
		{
			std::erase(pObserver->m_pSubjects, this);
			std::erase(m_pObservers, pObserver);
		}

		virtual void NotifyObservers(GameObject* pGameObject, int eventID)
		{
			for(IObserver* pObserver : m_pObservers)
			{
				pObserver->Notify(pGameObject, eventID);
			}
		}

	private:
		std::vector<IObserver*> m_pObservers{};
	};
}
