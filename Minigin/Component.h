#pragma once

namespace dae {

	class Event;
	class GameObject;
	class Component {
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float fixedStep) = 0;

	protected:
		explicit Component(GameObject* pGameObject) : m_pGameObject(pGameObject) {}
		GameObject* GetGameObject() const { return m_pGameObject; }
		GameObject* const m_pGameObject{};
	};
}
