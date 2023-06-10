#pragma once
#include "ISubject.h"

namespace dae
{
	class ISubject;
	class GameObject;
	class IObserver
	{
		friend ISubject;
	public:
		virtual ~IObserver()
		{
			for(ISubject* pSubject : m_pSubjects)
			{
				pSubject->DetachObserver(this);
			}
		}

		virtual void Notify(GameObject* pGameObject, int eventID) = 0;

	private:
		std::vector<ISubject*> m_pSubjects{};
	};
}
