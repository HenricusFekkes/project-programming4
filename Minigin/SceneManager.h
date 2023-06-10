#pragma once
#include "Singleton.h"
#include <string>
#include <map>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* AddScene(std::unique_ptr<Scene>&& scene);
		Scene* CreateScene(const std::string& name);
		void SetActive(const std::string& name);

		Scene* GetActiveScene();

	private:
		std::map<const std::string, std::unique_ptr<Scene>> m_Scenes{};
		Scene* m_ActiveScene{};
	};
}


