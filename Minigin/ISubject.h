#pragma once
#include <vector>

namespace dae
{
	class IObserver;
	class GameObject;
	class ISubject
	{
	public:
		virtual ~ISubject();

		virtual void AttachObserver(IObserver* pObserver) final;

		virtual void DetachObserver(IObserver* pObserver) final;

		virtual void NotifyObservers(GameObject* pGameObject, int eventID) final;

	protected:
		ISubject() = default;
		
		virtual void OnDetach(IObserver*) {};
		virtual void OnAttach(IObserver*) {};

	private:
		std::vector<IObserver*> m_pObservers{};
	};
}