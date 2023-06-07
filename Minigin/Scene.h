#pragma once
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class GameObject;
	class SceneManager;
	class Scene final
	{
		friend class SceneManager;

	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;
		GameObject* GetRoot();

		GameObject* AddChild(GameObject* pParent);
		GameObject* AddChild(GameObject* pParent, GameObject* pChild, bool keepWorldPosition = false);

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_GameObjects;
		GameObject * const m_Root;
	};
}
