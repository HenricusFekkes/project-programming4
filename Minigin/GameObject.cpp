#include "GameObject.h"
#include "TransformComponent.h"
#include "Scene.h"

using namespace dae;

GameObject::GameObject(GameObject* pParent) :
	m_TransformComponent{ std::make_unique<TransformComponent>(*this) }
{

	if (pParent)
	{
		pParent->AddChild(this);
	}
	m_pParent = pParent;
}

GameObject::~GameObject()
{
	for(GameObject* pChild : m_pChildren)
	{
		delete pChild;
	}
}

void GameObject::Update(float deltaTime) {
	for (auto& component : m_Components) {
		component->Update(deltaTime);
	}
	m_TransformComponent->Update(deltaTime);

	for (GameObject* pChild : m_pChildren) {
		pChild->Update(deltaTime);
	}
}

void GameObject::FixedUpdate(float fixedStep)
{
	for (const auto& component : m_Components) {
		component->FixedUpdate(fixedStep);
	}
	m_TransformComponent->FixedUpdate(fixedStep);

	for (GameObject* pChild : m_pChildren) {
		pChild->FixedUpdate(fixedStep);
	}
}

void GameObject::Render() const
{
	for (const auto& component : m_Components) {
		component->Render();
	}
	m_TransformComponent->Render();

	for (const GameObject* pChild : m_pChildren) {
		pChild->Render();
	}
}

void GameObject::Destroy()
{
	for(GameObject* pChild : m_pChildren)
	{
		pChild->Destroy();
	}
	m_IsAlive = false;
}

void GameObject::Cleanup()
{
	for (GameObject* pChild : m_pChildren)
	{
		if(pChild->m_IsAlive)
		{
			pChild->Cleanup();
		}
		else
		{
			std::erase(m_pChildren, pChild);
			delete pChild;
		}
	}
}

bool GameObject::IsAlive() const {
	return m_IsAlive;
}

GameObject* GameObject::GetParent() {
	return m_pParent;
}

const std::vector<GameObject*>& GameObject::GetChildren()
{
	return m_pChildren;
}

GameObject* GameObject::AddChild(GameObject* pChild, bool keepWorldPosition)
{
	if(std::ranges::find(m_pChildren, pChild) != m_pChildren.end())
	{
		return pChild;
	}
	TransformComponent* pChildTransform = pChild->m_TransformComponent.get();

	if (keepWorldPosition) {
		pChildTransform->SetLocalPosition(pChildTransform->GetWorldPosition() - GetComponent<TransformComponent>()->GetWorldPosition());
	}
	pChild->m_TransformComponent->SetDirty();

	GameObject* pOldParent = pChild->GetParent();
	if (pOldParent)
	{
		std::erase(pOldParent->m_pChildren, pChild);
	}
	pChild->m_pParent = this;
	m_pChildren.push_back(pChild);
	return pChild;
}

GameObject* GameObject::AddChild()
{
	return AddChild(new GameObject(nullptr));
}