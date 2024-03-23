#include "ScoreObserverComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::ScoreObserverComponent::ScoreObserverComponent(GameObject* pObj)
	: Component(pObj)
{
}

dae::ScoreObserverComponent::~ScoreObserverComponent()
{
}

void dae::ScoreObserverComponent::OnNotify(GameObject* obj, Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDeath:
		break;
	case dae::Event::EnemyDeath:
		break;
	case dae::Event::ScoreChange:
		UpdateText(obj);
		break;
	default:
		break;
	}
}

void dae::ScoreObserverComponent::UpdateText(GameObject* obj)
{
	// Get score and put in text
	if (obj->HasComponent<ScoreComponent>())
	{
		m_ScoreText = "Score: " + std::to_string(obj->GetComponent<ScoreComponent>()->GetScore());
	}

	// Give text to TxtDisplay
	if (GetOwner()->HasComponent<TextComponent>() && m_ScoreText.size() > 0)
	{
		GetOwner()->GetComponent<TextComponent>()->SetText(m_ScoreText);
	}
}