#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;

TransformComponent::TransformComponent(GameObject& gameObject) : Component(gameObject)
{}

void TransformComponent::Update(float)
{}

void TransformComponent::FixedUpdate(float)
{}

void TransformComponent::Render()
{}

void TransformComponent::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_IsDirty = true;
}

void TransformComponent::SetLocalPosition(const glm::vec3& localPosition) {
	m_LocalPosition = localPosition;
	m_IsDirty = true;
}

const glm::vec3& TransformComponent::GetLocalPosition() const {
	return m_LocalPosition; 
}

const glm::vec3& TransformComponent::GetWorldPosition() { 
	if (m_IsDirty) {
		UpdateWorldPosition();
	}
	return m_WorldPosition; 
}

void TransformComponent::UpdateWorldPosition() {
	if (m_IsDirty) {
		GameObject* pParent = GetGameObject().GetParent();
		if (not pParent) {
			m_WorldPosition = m_LocalPosition;
		}
		else {
			m_WorldPosition = pParent->GetComponent<TransformComponent>()->GetWorldPosition() + m_LocalPosition;
		}
		m_IsDirty = false;
	}
}

void TransformComponent::SetDirty() {
	m_IsDirty = true;
}