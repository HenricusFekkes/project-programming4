#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name), m_Root{ new GameObject(this)}
{}

Scene::~Scene()
{
	delete m_Root;
	for (GameObject* gameObject : m_GameObjects)
	{
		delete gameObject;
	}
}


void Scene::Update(float deltaTime)
{
	for(auto object : m_GameObjects)
	{
		object->Update(deltaTime);
	}

	std::erase_if(m_GameObjects,
	[](const auto* go) 
		{
			return not go->IsAlive();
		}
	);
}

void Scene::FixedUpdate(float fixedStep)
{
	for (auto object : m_GameObjects)
	{
		object->FixedUpdate(fixedStep);
	}
}

void Scene::Render() const
{
	for (const auto object : m_GameObjects)
	{
		object->Render();
	}
}

GameObject* Scene::GetRoot()
{
	return m_Root;
}
GameObject* Scene::AddChild(GameObject* pParent)
{
	if(pParent->m_pScene == this)
	{
		auto child = new GameObject(this, pParent);
		m_GameObjects.push_back(child);
		pParent->m_Children.push_back(child);
		return child;
	}
	return nullptr;
}

GameObject* Scene::AddChild(GameObject* pParent, GameObject* pChild, bool keepWorldPosition)
{
	if(pParent->m_pScene != this or pChild->m_pScene != this)
	{
		return nullptr;
	}

	TransformComponent* pChildTransform = pChild->m_TransformComponent.get();
	TransformComponent* pParentTransform = pParent->m_TransformComponent.get();
	if (keepWorldPosition) {
		pChildTransform->SetLocalPosition(pChildTransform->GetWorldPosition() - pParentTransform->GetWorldPosition());
	}
	pChild->m_TransformComponent->SetDirty();

	GameObject* pOldParent = pChild->GetParent();
	if (pOldParent)
	{
		std::erase(pOldParent->m_Children, pChild);
	}
	pChild->m_pParent = pParent;
	pParent->m_Children.push_back(pChild);
	return pChild;
}