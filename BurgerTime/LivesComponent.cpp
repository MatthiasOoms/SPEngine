#include "LivesComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pSubject{ new Subject{} }
{
	SetLives(3);
}

dae::LivesComponent::~LivesComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::LivesComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
	pObserver->OnNotify(GetOwner(), Event::ObserverAdded);
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
	if (m_CurrentLives <= 0)
	{
		m_pSubject->OnNotify(GetOwner(), Event::GameOver);

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
	m_pSubject->OnNotify(GetOwner(), Event::SceneSwap);
}