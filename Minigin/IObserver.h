#pragma once
#include <vector>

namespace dae
{
	class ISubject;
	class GameObject;
	class IObserver
	{
		friend ISubject;
	public:
		virtual ~IObserver();

		virtual void Notify(GameObject* pGameObject, int eventID) = 0;

	protected:
		virtual void OnDetach(ISubject*) {}
		virtual void OnAttach(ISubject*) {}
		virtual const std::vector<ISubject*>& GetSubjects();

	private:

		std::vector<ISubject*> m_pSubjects{};
	};
}
