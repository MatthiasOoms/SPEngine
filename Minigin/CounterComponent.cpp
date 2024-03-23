#include "CounterComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::CounterComponent::CounterComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_Count{ 0 }
{
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
	m_pSubject->OnNotify(GetOwner(), Event::ObserverAdd);
}

int dae::CounterComponent::GetCount() const
{
	return m_Count;
}

std::string dae::CounterComponent::GetName() const
{
	return m_Name;
}

void dae::CounterComponent::IncrementCount(int amount)
{
	m_Count += amount;
	m_pSubject->OnNotify(GetOwner(), Event::LivesChange);
}

void dae::CounterComponent::SetCount(int lives)
{
	m_Count = lives;
	m_pSubject->OnNotify(GetOwner(), Event::LivesChange);
}

void dae::CounterComponent::SetName(std::string name)
{
	m_Name = name;
}
