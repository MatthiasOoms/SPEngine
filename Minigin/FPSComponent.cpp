#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
	, m_pTextComponent{ nullptr }
{
	if (m_pOwner.lock()->HasComponent<dae::TextComponent>())
	{
		m_pTextComponent = m_pOwner.lock()->GetComponent<dae::TextComponent>();
	}
	else
	{
		m_pTextComponent = m_pOwner.lock()->AddComponent<dae::TextComponent>();
	}
}

void dae::FPSComponent::Update(const float deltaTime)
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText(std::to_string(int(1.f / deltaTime)));
	}
}
