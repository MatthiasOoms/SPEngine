#include "LivesComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	: Component(pOwner)
{
	SetLives(3);
	m_pSubject = new Subject{};
}

dae::LivesComponent::~LivesComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::LivesComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
}

int dae::LivesComponent::GetLives() const
{
	return m_CurrentLives;
}

void dae::LivesComponent::LowerLives()
{
	if (m_CurrentLives > 0)
	{
		--m_CurrentLives;
		m_pSubject->OnNotify(GetOwner(), Event::PlayerDeath);
	}
}

void dae::LivesComponent::LowerLives(int amount)
{
	if (m_CurrentLives > 0)
	{
		m_CurrentLives -= amount;
		m_pSubject->OnNotify(GetOwner(), Event::PlayerDeath);
	}
}

void dae::LivesComponent::SetLives(int lives)
{
	if (lives > 0)
	{
		m_CurrentLives = lives;
	}
	else
	{
		m_CurrentLives = 1;
	}
}