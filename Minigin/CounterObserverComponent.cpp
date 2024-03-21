#include "CounterObserverComponent.h"
#include "CounterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::CounterObserverComponent::CounterObserverComponent(GameObject* pObj)
	: Component(pObj)
{
}

dae::CounterObserverComponent::~CounterObserverComponent()
{
}

void dae::CounterObserverComponent::OnNotify(GameObject* obj, Event event)
{
	switch (event)
	{
	case dae::Event::ObserverAdd:
		UpdateText(obj);
		break;
	case dae::Event::CountChange:
		UpdateText(obj);
		break;
	default:
		break;
	}
}

void dae::CounterObserverComponent::UpdateText(GameObject* obj)
{
	// Get lives of obj and put in text
	if (obj->HasComponent<CounterComponent>())
	{
		m_CountText = m_Prefix + std::to_string(obj->GetComponent<CounterComponent>()->GetCount()) + m_Suffix;
	}

	// Give text to TxtDisplay of Owner
	if (GetOwner()->HasComponent<TextComponent>())
	{
		GetOwner()->GetComponent<TextComponent>()->SetText(m_CountText);
	}
}