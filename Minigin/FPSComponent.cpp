#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_pTextComponent{ nullptr }
{
	if (m_pOwner->HasComponent<dae::TextComponent>())
	{
		m_pTextComponent = m_pOwner->GetComponent<dae::TextComponent>();
	}
	else
	{
		m_pTextComponent = m_pOwner->AddComponent<dae::TextComponent>();
	}
}

void dae::FPSComponent::Update(float elapsedSec)
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText(std::to_string(int(1.f / elapsedSec)));
	}
}
