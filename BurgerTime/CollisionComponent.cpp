#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_Width{ 0 }
	, m_Height{ 0 }
{}

void dae::CollisionComponent::Update(float)
{}

void dae::CollisionComponent::SetWidth(int width)
{
	m_Width = width;
}

void dae::CollisionComponent::SetHeight(int height)
{
	m_Height = height;
}

int dae::CollisionComponent::GetWidth() const
{
	return m_Width;
}

int dae::CollisionComponent::GetHeight() const
{
	return m_Height;
}
