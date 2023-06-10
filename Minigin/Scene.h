#pragma once
#include <string>

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;
		void Cleanup();

		GameObject* GetRoot();
		GameObject* AddGameObject();

		const std::string& getName() const
		{
			return m_Name;
		}

	private:
		const std::string m_Name;
		GameObject* m_pRoot{};
	};
}
