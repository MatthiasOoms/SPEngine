#include "AchievementsObserverComponent.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::AchievementsObserverComponent::AchievementsObserverComponent(GameObject* pObj)
	: Component{ pObj }
	, m_HasAchWinOne{ false }
{
}

void dae::AchievementsObserverComponent::OnNotify(GameObject* obj, Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDeath:
		break;
	case dae::Event::EnemyDeath:
		break;
	case dae::Event::ScoreChange:
		if (!obj->HasComponent<ScoreComponent>())
		{
			break;
		}

		if (obj->GetComponent<ScoreComponent>()->GetScore() >= 500)
		{
			if (!m_HasAchWinOne)
			{
				UnlockAchievement("ACH_WIN_ONE_GAME");
				m_HasAchWinOne = true;
			}
		}
		break;
	default:
		break;
	}
}

void dae::AchievementsObserverComponent::UnlockAchievement(const char* id)
{
	SteamUserStats()->SetAchievement(id);
	SteamUserStats()->StoreStats();
}