#include "SceneManager.h"

#include <iostream>

#include "Scene.h"

using namespace dae;

Scene* SceneManager::AddScene(std::unique_ptr<Scene>&& scene)
{
	if (!scene)
		return nullptr;

	Scene* pScene = scene.get();
	pScene->Initialize();
	m_Scenes[scene->getName()] = std::move(scene);

	if (m_ActiveScene == nullptr)
	{
		m_ActiveScene = m_Scenes[pScene->getName()].get();
	}

	return pScene;
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	m_Scenes[name] = std::make_unique<Scene>(name);
	if (m_ActiveScene == nullptr)
	{
		m_ActiveScene = m_Scenes[name].get();
	}
	Scene* pScene = m_Scenes[name].get();

	pScene->Initialize();
	return pScene;
}

void SceneManager::SetActive(const std::string& name)
{
	m_ActiveScene = m_Scenes[name].get();
	m_ActiveScene->Initialize();
}


Scene* SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

