#pragma once
#include "Singleton.h"
#include <string>
#include <map>
#include <memory>
#include "Scene.h"

namespace dae
{
	class SceneManager final : public dae::Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		void SetActive(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;

	private:
		std::map<const std::string, std::unique_ptr<Scene>> m_Scenes{};
		Scene* m_ActiveScene{};
	};
}


