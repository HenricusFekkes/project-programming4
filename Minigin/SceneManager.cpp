#include "SceneManager.h"

#include <iostream>

#include "Scene.h"

using namespace dae;

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

