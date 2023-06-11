#pragma once

namespace dae {
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

		GameObject& GetGameObject() const { return m_GameObject; }

	protected:
		explicit IComponent(GameObject& gameObject) : m_GameObject(gameObject) {}

	private:
		GameObject& m_GameObject;
	};
}
