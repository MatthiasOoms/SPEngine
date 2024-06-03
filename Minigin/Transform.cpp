#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* pOwner)
	: m_pOwner{ pOwner }
	, m_LocalPosition{}
	, m_WorldPosition{}
	, m_Dimensions{}
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

	// If parent, parent world position + own local position
	if (m_pOwner->GetParent() != nullptr)
	{
		auto buffer{ m_pOwner->GetParent()->GetTransform().GetWorldPosition() };
		SetWorldPosition(buffer.x + x, buffer.y + y, buffer.z + z);
	}
	else
	{
		// If no parent, world = local position
		SetWorldPosition(x, y, z);
	}
}

void dae::Transform::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::Transform::SetWidth(int width)
{
	m_Dimensions.x = width;
}

void dae::Transform::SetHeight(int height)
{
	m_Dimensions.y = height;
}

glm::ivec2 dae::Transform::GetDimensions() const
{
	return m_Dimensions;
}

void dae::Transform::SetDimensions(glm::ivec2 dimensions)
{
	m_Dimensions = dimensions;
}

int dae::Transform::GetWidth() const
{
	return m_Dimensions.x;
}

int dae::Transform::GetHeight() const
{
	return m_Dimensions.y;
}
