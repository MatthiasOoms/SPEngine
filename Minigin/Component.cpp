#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* pOwner)
	: m_pOwner{ pOwner }
{
}

dae::UpdateComponent::UpdateComponent(GameObject* pOwner)
	: Component(pOwner)
{
}

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	: Component(pOwner)
{
}
