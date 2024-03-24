#include "Observer.h"
#include "Subject.h"

dae::Observer::~Observer()
{
	for (auto pSubject : m_pSubjects)
	{
		pSubject->RemoveObserver(this);
	}
}

void dae::Observer::AddSubject(Subject* pSubject)
{
	m_pSubjects.push_back(pSubject);
}
