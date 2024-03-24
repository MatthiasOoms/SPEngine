#pragma once
#include <vector>

namespace dae
{
	class GameObject;
	class Subject;

	enum class Event
	{
		PlayerDeath,
		EnemyDeath,
		ScoreChange
	};

	class Observer
	{
	private:
		std::vector<Subject*> m_pSubjects;

	public:
		virtual ~Observer();
		void AddSubject(Subject* pSubject);
		virtual void OnNotify(GameObject* obj, Event event) = 0;
	};
}