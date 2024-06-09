#include "ScoreComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pSubject = new Subject{};
	SetScore(0);
}

dae::ScoreComponent::~ScoreComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::ScoreComponent::HotdogDeath()
{
	m_Score += 100;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::EggDeath()
{
	m_Score += 200;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::PickleDeath()
{
	m_Score += 300;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::BurgerDrop()
{
	m_Score += 50;
	m_pSubject->OnNotify(GetOwner(), Event::BurgerDrop);
}

void dae::ScoreComponent::BurgerDrop(int enemyCount)
{
	int baseScore = 500;
	for (int i = 1; i < enemyCount; i++)
	{
		// 1 = 500, 2 = 1000, 3 = 2000, 4 = 4000, 5 = 8000, 6 = 16000
		baseScore *= 2;
	}
	m_Score += baseScore;
	m_pSubject->OnNotify(GetOwner(), Event::BurgerDrop);
}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
	pObserver->OnNotify(GetOwner(), Event::ObserverAdded);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}