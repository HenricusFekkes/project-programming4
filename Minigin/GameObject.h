#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Component.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class Event;
	class CannotRemoveThisComponentException {};
	class Scene;
	class GameObject final
	{
		friend class Scene;

	public:
		GameObject(Scene* pScene, GameObject* pParent);

		GameObject(const GameObject&& other) = delete;
		GameObject& operator=(const GameObject&& other) = delete;
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;
		void Destroy();

		GameObject* GetParent();
		const std::vector<GameObject*>& GetChildren();
		bool IsAlive() const;

		GameObject* AddChild();
		GameObject* AddChild(GameObject* pChild, bool keepWorldPosition = false);


	private:
		GameObject(Scene* pScene);

		std::vector<std::unique_ptr<Component>> m_Components{};
		std::unique_ptr<RenderComponent>	m_RenderComponent;
		std::unique_ptr<TransformComponent> m_TransformComponent;
		bool isAlive{ true };

		Scene * const m_pScene;
		GameObject* m_pParent{};
		std::vector<GameObject*> m_Children{};

#pragma region templates
	public:
		template <typename T>
		void AddComponent() {
			if (!ContainsComponent<T>()) {
				m_Components.emplace_back(std::make_unique<T>(this));
			}
		}

		template <>
		void AddComponent<RenderComponent>() {
			return;
		}

		template <>
		void AddComponent<TransformComponent>() {
			return;
		}

		template <typename T>
		T* GetComponent() const {
			auto it = std::find_if(begin(m_Components), end(m_Components), [](const auto& c) {
				return dynamic_cast<T*>(c.get());
				});
			if (it == end(m_Components)) {
				return nullptr;
			}
			return dynamic_cast<T*>((*it).get());
		}

		template <>
		RenderComponent* GetComponent<RenderComponent>() const {
			return m_RenderComponent.get();
		}

		template <>
		TransformComponent* GetComponent<TransformComponent>() const {
			return m_TransformComponent.get();
		}

		template <typename T>
		void RemoveComponent() {
			std::erase_if(m_Components, [](const auto& c) {
				return dynamic_cast<T*>(c.get());
				});
		}

		template <>
		void RemoveComponent<RenderComponent>() {
			throw CannotRemoveThisComponentException();
		}

		template <>
		void RemoveComponent<TransformComponent>() {
			throw CannotRemoveThisComponentException();
		}

		template <typename T>
		bool ContainsComponent() {
			return end(m_Components) != std::find_if(begin(m_Components), end(m_Components), [](const auto& c) {
				return dynamic_cast<T*>(c.get());
				});
		}

		template <>
		bool ContainsComponent<RenderComponent>() {
			return true;
		}

		template <>
		bool ContainsComponent<TransformComponent>() {
			return true;
		}

#pragma endregion templates
	};
}
