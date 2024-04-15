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

void dae::ScoreComponent::IncreaseScore(int amount)
{
	m_Score += amount;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;
	m_pSubject->OnNotify(GetOwner(), Event::EnemyDeath);
}

void dae::ScoreComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}