#include "SceneManager.h"

#include <iostream>

#include "Scene.h"

using namespace dae;

Scene* SceneManager::CreateScene(const std::string& name)
{
	m_Scenes[name] = std::unique_ptr<Scene>(new Scene(name));
	if (m_ActiveScene == nullptr)
	{
		m_ActiveScene = m_Scenes[name].get();
	}
	return m_Scenes[name].get();
}

void SceneManager::SetActive(const std::string& name)
{
	m_ActiveScene = m_Scenes[name].get();
	std::cout << "Active scene: " << m_ActiveScene->m_Name << std::endl;
}

void SceneManager::Update(float deltaTime)
{
	m_ActiveScene->Update(deltaTime);
}

void SceneManager::FixedUpdate(float fixedStep)
{
	m_ActiveScene->FixedUpdate(fixedStep);
}

void SceneManager::Render() const
{
	m_ActiveScene->Render();
}
