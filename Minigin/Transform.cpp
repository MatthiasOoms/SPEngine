#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* pOwner)
	: m_pOwner{ pOwner }
	, m_LocalPosition{}
	, m_WorldPosition{}
{
	if (m_pOwner->GetParent())
	{
		m_WorldPosition = m_pOwner->GetParent()->GetTransform().GetWorldPosition();
	}
}

dae::Transform::~Transform()
{
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	if (m_pOwner->GetParent())
	{
		auto buffer{ m_pOwner->GetParent()->GetTransform().GetWorldPosition() };
		SetWorldPosition(buffer.x + x, buffer.y + y, buffer.z + z);
	}
	else
	{
		SetWorldPosition(x, y, z);
	}
}

void dae::Transform::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}
