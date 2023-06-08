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
	public:
		GameObject(GameObject* pParent);
		~GameObject();

		GameObject(const GameObject&& other) = delete;
		GameObject& operator=(const GameObject&& other) = delete;
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;

		void Destroy();
		void Cleanup();

		GameObject* GetParent();
		const std::vector<GameObject*>& GetChildren();
		bool IsAlive() const;
		
		GameObject* AddChild(GameObject* pChild, bool keepWorldPosition = false);
		GameObject* AddChild();


	private:
		std::vector<std::unique_ptr<Component>> m_Components{};
		std::unique_ptr<TransformComponent> m_TransformComponent;
		bool m_IsAlive{ true };
		
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

#pragma region templates
	public:
		template <typename T>
		void AddComponent() {
			if (not ContainsComponent<T>()) {
				m_Components.emplace_back(std::make_unique<T>(*this));
			}
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
				assert(false and "Doesn't contain requested component.");
				return nullptr;
			}
			return dynamic_cast<T*>((*it).get());
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
		bool ContainsComponent<TransformComponent>() {
			return true;
		}
#pragma endregion templates
	};
}
