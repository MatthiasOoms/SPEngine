#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::GameObject()
	: m_IsPositionDirty{ false }
{
	m_pTransform = std::make_unique<Transform>(this);
}

dae::GameObject::~GameObject()
{
	for (size_t idx{}; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx].reset();
	}
}

void dae::GameObject::Update(const float deltaTime)
{
	for (size_t idx{}; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Update(deltaTime);
	}
}

void dae::GameObject::Render(const float deltaTime) const
{
	for (size_t idx{}; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Render(deltaTime);
	}
}

dae::Transform& dae::GameObject::GetTransform() const
{
	return *m_pTransform;
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_pTransform->GetLocalPosition();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	//UpdateWorldPosition();
	return m_pTransform->GetWorldPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_pTransform->SetLocalPosition(pos.x, pos.y, pos.z);
	//SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const float x, const float y, const float z)
{
	m_pTransform->SetLocalPosition(x, y, z);
	//SetPositionDirty();
}
