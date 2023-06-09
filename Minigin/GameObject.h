#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "IComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class CannotRemoveThisComponentException {};
	class Scene;
	class GameObject final
	{
	public:
		explicit GameObject(GameObject* pParent);
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
		std::vector<std::unique_ptr<IComponent>> m_Components{};
		std::unique_ptr<TransformComponent> m_TransformComponent{};
		bool m_IsAlive{ true };
		
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

#pragma region templates
	public:
		template <typename T>
		T* AddComponent() {
			T* pComponent = GetComponent<T>();
			if (pComponent) {
				return pComponent;
			}
			m_Components.emplace_back(std::make_unique<T>(*this));
			return dynamic_cast<T*>(m_Components.back().get());
		}

		template <>
		TransformComponent* AddComponent<TransformComponent>() {
			return m_TransformComponent.get();
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
