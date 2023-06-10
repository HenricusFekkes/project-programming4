#include "SceneManager.h"

#include <iostream>

#include "Scene.h"

using namespace dae;

Scene* SceneManager::AddScene(std::unique_ptr<Scene>&& scene)
{
	if (!scene)
		return nullptr;

	Scene* pScene = scene.get();
	m_Scenes[scene->getName()] = std::move(scene);

	return pScene;
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	m_Scenes[name] = std::make_unique<Scene>(name);
	if (m_ActiveScene == nullptr)
	{
		m_ActiveScene = m_Scenes[name].get();
	}
	return m_Scenes[name].get();
}

void SceneManager::SetActive(const std::string& name)
{
	m_ActiveScene = m_Scenes[name].get();
}


Scene* SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

