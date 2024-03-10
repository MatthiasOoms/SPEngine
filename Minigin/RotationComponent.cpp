#include "RotationComponent.h"
#include "GameObject.h"
#include <SDL_stdinc.h> // M_PI

dae::RotationComponent::RotationComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_Distance{}
	, m_RotAngle{}
	, m_RotSpeed{ 180 }
{
	float distance{ GetDistance(GetOwner()->GetTransform().GetLocalPosition().x, GetOwner()->GetTransform().GetLocalPosition().y, GetOwner()->GetTransform().GetLocalPosition().z) };
	m_Distance = distance;
}

void dae::RotationComponent::Update(float elapsedSec)
{
	m_RotAngle += m_RotSpeed * elapsedSec * float(M_PI) / 180.f;

	// Prevent undefined behavior due to overflow
	if (m_RotAngle >= 2 * M_PI)
	{
		m_RotAngle -= 2 * float(M_PI);
	}

	glm::vec3 buffer{ cosf(m_RotAngle) * m_Distance, sinf(m_RotAngle) * m_Distance, 0 };
	GetOwner()->SetLocalPosition(buffer.x, buffer.y, buffer.z);
}

void dae::RotationComponent::SetRotationSpeed(float rotSpeed)
{
	m_RotSpeed = rotSpeed;
}

float dae::RotationComponent::GetDistance(float x, float y, float z) const
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

