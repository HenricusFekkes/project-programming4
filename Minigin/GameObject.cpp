#include "GameObject.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Scene.h"

using namespace dae;

GameObject::GameObject(Scene* pScene, GameObject* pParent) : m_pScene{pScene}
{
	m_TransformComponent = std::make_unique<TransformComponent>(this);
	m_RenderComponent = std::make_unique<RenderComponent>(this);
	m_pScene->AddChild(pParent, this);
}

GameObject::GameObject(Scene* pScene) : m_pScene{pScene}
{
	m_TransformComponent = std::make_unique<TransformComponent>(this);
	m_RenderComponent = std::make_unique<RenderComponent>(this);
}

void GameObject::Update(float deltaTime) {
	for (const auto& component : m_Components) {
		component->Update(deltaTime);
	}
	m_TransformComponent->Update(deltaTime);
	m_RenderComponent->Update(deltaTime);
}

void GameObject::FixedUpdate(float fixedStep)
{
	for (const auto& component : m_Components) {
		component->FixedUpdate(fixedStep);
	}
	m_TransformComponent->FixedUpdate(fixedStep);
	m_RenderComponent->FixedUpdate(fixedStep);
}

void GameObject::Render() const
{
	if (m_RenderComponent) {
		m_RenderComponent->Render();
	}
}

void GameObject::Destroy() {
	for(GameObject* child : m_Children)
	{
		child->Destroy();
	}
	isAlive = false;
}

bool GameObject::IsAlive() const {
	return isAlive;
}

GameObject* GameObject::GetParent() {
	return m_pParent;
}

const std::vector<GameObject*>& GameObject::GetChildren()
{
	return m_Children;
}

GameObject* GameObject::AddChild()
{
	return m_pScene->AddChild(this);
}

GameObject* GameObject::AddChild(GameObject* pChild, bool keepWorldPosition)
{
	return m_pScene->AddChild(this, pChild, keepWorldPosition);
}
