#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_pTextComponent{ nullptr }
{
	if (GetOwner()->HasComponent<dae::TextComponent>())
	{
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
	}
	else
	{
		m_pTextComponent = GetOwner()->AddComponent<dae::TextComponent>();
	}
}

void dae::FPSComponent::Update(const float deltaTime)
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText(std::to_string(static_cast<int>(1.f / deltaTime)));
	}
}
