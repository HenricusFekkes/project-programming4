#pragma once
#include <functional>
#include <vector>
#include "Singleton.h"

namespace dae
{
	template<typename TEvent>
	class EventManager final : public Singleton<EventManager<TEvent>>
	{
		using Callback = std::function<void(const TEvent&)>;

	public:
		void Subscribe(Callback callback)
		{
			m_Callbacks.push_back(callback);
		}

		void Unsubscribe(Callback callback)
		{
			m_Callbacks.erase(std::remove(m_Callbacks.begin(), m_Callbacks.end(), callback), m_Callbacks.end());
		}

		void Dispatch(const TEvent& event)
		{
			for(const auto& callback : m_Callbacks)
			{
				callback(event);
			}
		}

	private:
		std::vector<Callback> m_Callbacks{};
	};
}
