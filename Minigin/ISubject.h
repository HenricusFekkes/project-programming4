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
			for (IObserver* pObserver : m_pObservers)
			{
				std::erase(pObserver->m_pSubjects, this);
			}
		}

		virtual void AttachObserver(IObserver* pObserver) final
		{
			pObserver->m_pSubjects.emplace_back(this);
			m_pObservers.emplace_back(pObserver);
		}

		virtual void DetachObserver(IObserver* pObserver) final
		{
			std::erase(pObserver->m_pSubjects, this);
			std::erase(m_pObservers, pObserver);
		}

		virtual void NotifyObservers(GameObject* pGameObject, int eventID) final
		{
			for (IObserver* pObserver : m_pObservers)
			{
				pObserver->Notify(pGameObject, eventID);
			}
		}

	protected:
		ISubject() = default;

	private:
		std::vector<IObserver*> m_pObservers{};
	};
}