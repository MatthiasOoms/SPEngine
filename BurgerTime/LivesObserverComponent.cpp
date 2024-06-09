#include "LivesObserverComponent.h"
#include "SoundServiceLocator.h"
#include "LivesComponent.h"
#include "TextComponent.h"
#include <SoundSystem.h>
#include "GameObject.h"
#include "Subject.h"
#include "GameCommands.h"

dae::LivesObserverComponent::LivesObserverComponent(GameObject* pObj)
	: Component(pObj)
{
}

dae::LivesObserverComponent::~LivesObserverComponent()
{
	for (auto pSubject : m_pSubjects)
	{
		pSubject->RemoveObserver(this);
	}
}

void dae::LivesObserverComponent::OnNotify(GameObject* obj, Event event)
{
	auto& soundSystem = SoundServiceLocator::GetSoundSystem();
	Sound temp = { "../Data/Death.mp3", "Death", 0 };

	switch (event)
	{
	case dae::Event::PlayerDeath:
		UpdateText(obj);
		soundSystem.PushOnQueue(temp);
		break;
	case dae::Event::EnemyDeath:
		break;
	case dae::Event::ObserverAdded:
		UpdateText(obj);
		break;
	case dae::Event::SceneSwap:
		UpdateText(obj);
		break;
	case dae::Event::BurgerDrop:
		break;
	case dae::Event::GameOver:
	{
		// Load HighScoreScene
		SceneSwapCommand swapCommand{ "HighScore", "" };
		swapCommand.Execute(0);
		break;
	}
	default:
		break;
	}
}

void dae::LivesObserverComponent::OnSubjectRemoved(GameObject*)
{
}

void dae::LivesObserverComponent::UpdateText(GameObject* obj)
{
	// Get lives and put in text
	if (obj->HasComponent<LivesComponent>())
	{
		LivesComponent* pLivesComponent = obj->GetComponent<LivesComponent>();
		m_ScoreText = std::to_string(pLivesComponent->GetLives());
		if (pLivesComponent->GetLives() == 1)
		{
			m_ScoreText += " life";
		}
		else
		{
			m_ScoreText += " lives";
		}
	}

	// Give text to TxtDisplay
	if (GetOwner()->HasComponent<TextComponent>() && m_ScoreText.size() > 0)
	{
		GetOwner()->GetComponent<TextComponent>()->SetText(m_ScoreText);
	}
}