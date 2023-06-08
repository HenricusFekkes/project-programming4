#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name), m_pRoot{ new GameObject(nullptr) }
{}

Scene::~Scene()
{
	delete m_pRoot;
}


void Scene::Update(float deltaTime)
{
	m_pRoot->Update(deltaTime);
}

void Scene::FixedUpdate(float fixedStep)
{
	m_pRoot->FixedUpdate(fixedStep);
}

void Scene::Render() const
{
	m_pRoot->Render();
}

void Scene::Cleanup()
{
	m_pRoot->Cleanup();
}

GameObject* Scene::GetRoot()
{
	return m_pRoot;
}

GameObject* Scene::AddGameObject()
{
	return m_pRoot->AddChild();
}