#pragma once

namespace dae {

	class Event;
	class GameObject;
	class IComponent {
	public:
		virtual ~IComponent() = default;
		IComponent(const IComponent& other) = delete;
		IComponent(IComponent&& other) = delete;
		IComponent& operator=(const IComponent& other) = delete;
		IComponent& operator=(IComponent&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float fixedStep) = 0;
		virtual void Render() = 0;

	protected:
		IComponent(GameObject& gameObject) : m_GameObject(gameObject) {}
		GameObject& GetGameObject() const { return m_GameObject; }

	private:
		GameObject& m_GameObject;
	};
}
