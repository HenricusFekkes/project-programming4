#pragma once
#include <string>

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;
		void Cleanup();

		virtual void Initialize();

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
