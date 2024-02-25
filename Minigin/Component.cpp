#include "Component.h"

dae::Component::Component(std::weak_ptr<GameObject> pOwner)
	: m_pOwner{ pOwner }
{
}

dae::UpdateComponent::UpdateComponent(std::weak_ptr<GameObject> pOwner)
	: Component(pOwner)
{
}

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pOwner)
	: Component(pOwner)
{
}
