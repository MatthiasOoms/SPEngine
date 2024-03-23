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
		UpdateLivesText(obj);
		UpdateScoreText(obj);
		break;
	case dae::Event::LivesChange:
		UpdateLivesText(obj);
		break;
	case dae::Event::ScoreChange:
		UpdateScoreText(obj);
		break;
	default:
		break;
	}
}

void dae::CounterObserverComponent::UpdateLivesText(GameObject* obj)
{
	// Get lives of obj and put in text
	if (obj->HasComponent<CounterComponent>())
	{
		auto temp = obj->GetAllComponentsOfType<CounterComponent>();
		for (auto counter : temp)
		{
			if (counter->GetName() == "Lives")
			{
				m_CountText = m_Prefix + std::to_string(counter->GetCount()) + m_Suffix;
			}
		}
	}

	// Give text to TxtDisplay of Owner
	if (GetOwner()->HasComponent<TextComponent>())
	{
		GetOwner()->GetComponent<TextComponent>()->SetText(m_CountText);
	}
}

void dae::CounterObserverComponent::UpdateScoreText(GameObject* obj)
{
	// Get lives of obj and put in text
	if (obj->HasComponent<CounterComponent>())
	{
		auto temp = obj->GetAllComponentsOfType<CounterComponent>();
		for (auto counter : temp)
		{
			if (counter->GetName() == "Score")
			{
				m_CountText = m_Prefix + std::to_string(counter->GetCount()) + m_Suffix;
			}
		}
	}

	// Give text to TxtDisplay of Owner
	if (GetOwner()->HasComponent<TextComponent>())
	{
		GetOwner()->GetComponent<TextComponent>()->SetText(m_CountText);
	}
}
