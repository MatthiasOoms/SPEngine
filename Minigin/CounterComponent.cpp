#include "CounterComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::CounterComponent::CounterComponent(GameObject* pOwner)
	: Component(pOwner)
{
	SetCount(3);
	m_pSubject = new Subject{};
}

dae::CounterComponent::~CounterComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::CounterComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
	m_pSubject->OnNotify(GetOwner(), Event::AddObserver);
}

int dae::CounterComponent::GetCount() const
{
	return m_Count;
}

void dae::CounterComponent::IncrementCount(int amount)
{
	m_Count += amount;
	m_pSubject->OnNotify(GetOwner(), Event::PlayerDeath);
}

void dae::CounterComponent::SetCount(int lives)
{
	m_Count = lives;
}