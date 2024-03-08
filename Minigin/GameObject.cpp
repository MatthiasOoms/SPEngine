#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::GameObject()
	: m_pParent{ nullptr }
	, m_IsPositionDirty{ false }
	, m_IsDead{ false }
{
	m_pTransform = std::make_unique<Transform>(this);
}

dae::GameObject::GameObject(GameObject* pParent)
	: m_IsPositionDirty{ true }
	, m_IsDead{ false }
{
	m_pParent = nullptr;
	m_pTransform = std::make_unique<Transform>(this);
	SetParent(pParent, false);
}

dae::GameObject::~GameObject()
{
	for (size_t idx{}; idx < m_pComponents.size(); ++idx)
	{
		delete m_pComponents[idx];
		m_pComponents[idx] = nullptr;
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

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// If the parent is the same as self or the current parent, do nothing
	if (pParent == this && pParent == m_pParent)
	{
		return;
	}

	// If the parent is a child of self, do nothing
	// TODO: Check if parent is not a grandchild of self!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (size_t i{}; i < m_pChildren.size(); ++i)
	{
		if (pParent == m_pChildren[i])
		{
			return;
		}
	}

	// If it has no parent, it's a root object
	if (m_pParent == nullptr)
	{
		if (m_pTransform)
		{
			SetLocalPosition(GetWorldPosition());
		}
	}
	// If has a parent, remove self from parent
	else 
	{
		m_pParent->RemoveChild(this);
		if (keepWorldPosition)
		{
			// Set local position to world position
			SetLocalPosition(GetWorldPosition() - m_pParent->GetWorldPosition());
		}
	}

	// Set new parent
 	m_pParent = pParent;

	// If the new parent is not null, add self to parent
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

int dae::GameObject::GetChildCount() const
{
	return int(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int idx) const
{
	// If the index is valid, return the child
	if (idx >= 0 && idx < GetChildCount())
	{
		return m_pChildren[idx];
	}

	// If the index is invalid, return nullptr
	return nullptr;
}

void dae::GameObject::Kill()
{
	m_IsDead = true;
}

bool dae::GameObject::IsDead()
{
	return m_IsDead;
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	std::erase(m_pChildren, pChild);
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_pTransform->GetLocalPosition();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_pTransform->GetWorldPosition();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_IsPositionDirty)
	{
		if (m_pParent == nullptr)
		{
			auto buffer{ GetLocalPosition() };
			m_pTransform->SetWorldPosition(buffer.x, buffer.y, buffer.z);
		}
		else
		{
			auto buffer{ m_pParent->GetWorldPosition() + GetLocalPosition() };
			m_pTransform->SetWorldPosition(buffer.x, buffer.y, buffer.z);
		}
	}
	m_IsPositionDirty = false;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_pTransform->SetLocalPosition(pos.x, pos.y, pos.z);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const float x, const float y, const float z)
{
	m_pTransform->SetLocalPosition(x, y, z);
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	for (int idx{}; idx < GetChildCount(); ++idx)
	{
		GetChildAt(idx)->SetPositionDirty();
	}
	m_IsPositionDirty = true;
}
