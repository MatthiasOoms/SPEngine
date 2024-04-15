#pragma once

namespace dae
{
	class GameObject;
	class Subject;

	enum class Event
	{
		PlayerDeath,
		EnemyDeath	
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void AddSubject(Subject* pSubject);
		virtual void OnNotify(GameObject* obj, Event event) = 0;

	private:
		std::vector<Subject*> m_pSubjects;
	};
}